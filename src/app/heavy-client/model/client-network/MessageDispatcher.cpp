#include "TypeSerializerDeserializer.h"
#include "NetworkStandard.h"

#include "EventHandler.h"
#include "FacadeInterfaceNative.h"
#include <iostream>

#include "MessageDispatcher.h"
#include "Authentification.cs"
#include "MapPermission.cs"

namespace client_network
{

MessageDispatcher::MessageDispatcher(event_handler::EventHandler* eventHandler_)
	: eventHandler_(eventHandler_)
{
}

MessageDispatcher::~MessageDispatcher()
{
	stopDispatching();
}

void MessageDispatcher::handleReceivedMessage(const char* buffer, uint32_t size)
{
	uint32_t iCurrentMessage = 0;
	// Parse the buffer.
	while (iCurrentMessage < size)
	{
		const char* message = buffer + iCurrentMessage;
		uint32_t currentMessageSize = serializer_.deserializeInteger(message);
		pushMessage(std::string(message, currentMessageSize));
		iCurrentMessage += currentMessageSize;
	}
}

void MessageDispatcher::pushMessage(const std::string& message)
{
	queueLock_.lock();
	messageQueue_.push(std::move(message));
	queueLock_.unlock();
	// Notify the queue is not empty.
	lookupcv_.notify_all();
}

void MessageDispatcher::startDispatching()
{
	isDispatching_ = true;
	th_ = std::thread(&MessageDispatcher::lookupMessage, this);
}

void MessageDispatcher::stopDispatching()
{
	isDispatching_ = false;
	lookupcv_.notify_all();
	if (th_.joinable())
	{
		th_.join();
	}
}

void MessageDispatcher::lookupMessage()
{
	std::unique_lock<std::mutex> lck(lookupLock_);
	while (isDispatching_)
	{
		// Wait if the queue is empty and we are still dispatching.
		lookupcv_.wait(lck, [this] { return !messageQueue_.empty() || !isDispatching_; });

		queueLock_.lock();
		if (!messageQueue_.empty())
		{
			dispatch(messageQueue_.front());
			messageQueue_.pop();
		}
		queueLock_.unlock();
	}
}

void MessageDispatcher::handlePhysicMessage(const std::string& message)
{
	if (message[Networking::MessageStandard::COMMAND == 'e'])
	{
		handleStackedPhysicsMessage(message);
	}
	else
	{
		handleSinglePhysicMessage(message);
	}
}

void MessageDispatcher::handleSinglePhysicMessage(const std::string& message)
{
	uint32_t entityId = serializer_.deserializeInteger(message.data() + Networking::MessageStandard::DATA_START);
	char propertyType = message[Networking::MessageStandard::COMMAND];
	glm::vec3 updatedProperty;
	updatedProperty.x = serializer_.deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 4);
	updatedProperty.y = serializer_.deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 8);
	updatedProperty.z = serializer_.deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 12);

	eventHandler_->onEntityPropertyUpdated(entityId, propertyType, updatedProperty);
}

void MessageDispatcher::handleStackedPhysicsMessage(const std::string& message)
{
	uint32_t entityId = serializer_.deserializeInteger(message.data() + Networking::MessageStandard::DATA_START);

	PhysicsComponent update;
		
	char const* data = message.data() + Networking::MessageStandard::DATA_START + 4;
	Networking::deserialize(data, update.relativePosition);

	data += 12;
	Networking::deserialize(data, update.absolutePosition);

	data += 12;
	Networking::deserialize(data, update.rotation);

	data += 12;
	Networking::deserialize(data, update.linearVelocity);

	data += 12;
	Networking::deserialize(data, update.angularVelocity);

	eventHandler_->onStackedPropertiesUpdate(entityId, update);
}

void MessageDispatcher::handleEntityCreationMessage(const std::string& message)
{
	uint8_t  entityType = serializer_.deserializeChar(message[6]);
	uint32_t parentId = serializer_.deserializeInteger(&message[7]);

	glm::vec3 absPos;
	absPos.x = serializer_.deserializeFloat(&message[11]);
	absPos.y = serializer_.deserializeFloat(&message[15]);
	absPos.z = serializer_.deserializeFloat(&message[19]);

	glm::vec3 relPos;
	relPos.x = serializer_.deserializeFloat(&message[23]);
	relPos.y = serializer_.deserializeFloat(&message[27]);
	relPos.z = serializer_.deserializeFloat(&message[31]);

	glm::vec3 rotation;
	rotation.x = serializer_.deserializeFloat(&message[35]);
	rotation.y = serializer_.deserializeFloat(&message[39]);
	rotation.z = serializer_.deserializeFloat(&message[43]);

	glm::vec3 scale;
	scale.x = serializer_.deserializeFloat(&message[47]);
	scale.y = serializer_.deserializeFloat(&message[51]);
	scale.z = serializer_.deserializeFloat(&message[55]);

	uint32_t entityId = serializer_.deserializeInteger(&message[59]);
	uint32_t userId = serializer_.deserializeInteger(&message[63]);

	eventHandler_->onEntityCreated(entityType, parentId, absPos, relPos, rotation, scale, entityId, userId);
}

void MessageDispatcher::handleEntityDeletionMessage(const std::string& message)
{
	uint32_t entityId = serializer_.deserializeInteger(message.data() + Networking::MessageStandard::DATA_START);
	eventHandler_->onEntityDeleted(entityId);
}

void MessageDispatcher::handleEntitySelectionMessage(const std::string& message)
{
	uint32_t entityId = serializer_.deserializeInteger(message.data() + Networking::MessageStandard::DATA_START);
	bool selectionState = message[Networking::MessageStandard::DATA_START + 4] != 0;
	uint32_t userId = serializer_.deserializeInteger(message.data() + Networking::MessageStandard::DATA_START + 5);
	eventHandler_->onEntitySelected(entityId, selectionState, userId);
}

void MessageDispatcher::handleMapEditionMessage(const std::string& message)
{
	switch (message[5])
	{
	case 'c':
		handleEntityCreationMessage(message);
		break;

	case 'd':
		handleEntityDeletionMessage(message);
		break;
		
	case 's':
		handleEntitySelectionMessage(message);
		break;

	default:
		std::cout << "Unexpected message received - " << message << std::endl;
		break;
	}
}

void MessageDispatcher::handleMapCreationMessage(const std::string& message)
{
	uint32_t mapId = serializer_.deserializeInteger(&message[Networking::MessageStandard::DATA_START]);
	char type = message[Networking::MessageStandard::DATA_START + 4];
	char nUsers = message[Networking::MessageStandard::DATA_START + 5];
	char permission = message[Networking::MessageStandard::DATA_START + 6];
	uint32_t adminId = message[Networking::MessageStandard::DATA_START + 7];
	std::string name = message.substr(Networking::MessageStandard::DATA_START + 11);
	eventHandler_->onNewMapCreated(mapId, type, mapId, permission, adminId, name);
}

void MessageDispatcher::handleMapJoinMessage(const std::string& message)
{
	char result = message[Networking::MessageStandard::DATA_START];
	uint32_t mapId = serializer_.deserializeInteger(&message[Networking::MessageStandard::DATA_START + 1]);
	uint32_t userId = serializer_.deserializeInteger(&message[Networking::MessageStandard::DATA_START + 5]);
	eventHandler_->onUserJoinedMap(result, mapId, userId);
}

void MessageDispatcher::handleMapQuitMessage(const std::string& message)
{
	uint32_t userId = serializer_.deserializeInteger(&message[Networking::MessageStandard::DATA_START]);
	eventHandler_->onUserLeftCurrentMapSession(userId);
}

void MessageDispatcher::handleMapListMessage(const std::string& message)
{
	size_t iCurrentEntry = Networking::MessageStandard::DATA_START;
	bool continueParsing = message.size() >= 12;

	while (continueParsing)
	{
		uint32_t mapId = serializer_.deserializeInteger(message.data() + iCurrentEntry);
		char mapType = message[iCurrentEntry + 4];
		char nUsers = message[iCurrentEntry + 5];
		char permission = message[iCurrentEntry + 6];
		uint32_t adminId = serializer_.deserializeInteger(message.data() + iCurrentEntry + 7);

		size_t nameBegin = iCurrentEntry + 11;
		size_t nameEnd = message.find(';', nameBegin);
		if (nameEnd == std::string::npos)
		{
			nameEnd = message.size();
			continueParsing = false;
		}
		std::string mapName = message.substr(nameBegin, nameEnd - nameBegin);
		eventHandler_->onNewMapCreated(mapId, mapType, nUsers, permission, adminId, mapName);
		iCurrentEntry = nameEnd + 1;
	}
}

void MessageDispatcher::handleMapReadyMessage(const std::string& message)
{
	uint32_t mapId = serializer_.deserializeInteger(&message[Networking::MessageStandard::DATA_START]);
	eventHandler_->onMapReady(mapId);
}

void MessageDispatcher::handleMapPermissionMessage(const std::string& message)
{
	uint32_t mapId = serializer_.deserializeInteger(&message[Networking::MessageStandard::DATA_START]);
	char result = message[Networking::MessageStandard::DATA_START + 4];
	switch (result)
	{
	case 'o':
		mapPermission(mapId, CHANGED_PUBLIC);
		break;

	case 'c':
		mapPermission(mapId, CHANGED_PRIVATE);
		break;

	case 'd':
		mapPermission(mapId, CHANGED_DENIED);
		break;

	default:
		std::cout << "Unexpected message received" << message << std::endl;
		break;
	}
}

void MessageDispatcher::handleMapSystemMessage(const std::string& message)
{
	switch (message[5])
	{
	case 'j':
		handleMapJoinMessage(message);
		break;

	case 'q':
		handleMapQuitMessage(message);
		break;

	case 'c':
		handleMapCreationMessage(message);
		break;

	case 'l':
		handleMapListMessage(message);
		break;

	case 'r':
		handleMapReadyMessage(message);
		break;

	case 'p':
		handleMapPermissionMessage(message);
		break;

	default:
		std::cout << "Unexpected message received" << message << std::endl;
		break;

	}
}

void MessageDispatcher::handleUserAuthentificationConfirmation(const std::string& message)
{
	char authResult = message[6];
	uint32_t userId = serializer_.deserializeInteger(&message[7]);
	switch (authResult)
	{
	case 's':
		eventHandler_->onUserAuthentified(userId);
		authentification(AUTEHNTIFICATION_SUCCESS);
		break;

	case 'f':
		authentification(EXISTING_FAIL);
		break;

	case 'c':
		authentification(EXISTING_ALREADY_CONNECTED);
		break;

	default:
		std::cout << "User authentification failed." << std::endl;
	}
}

void MessageDispatcher::handleUserCreationConfirmation(const std::string& message)
{
	char authResult = message[6];
	switch (authResult)
	{
	case 's':
		authentification(CREATION_SUCCESS);
		break;

	case 'e':
		authentification(NEW_ALREADY_EXIST);
		break;

	default:
		std::cout << "user creation failed." << std::endl;
	}
}

void MessageDispatcher::handleUserSystemMessage(const std::string& message)
{
	switch (message[5])
	{
	case 'a':
		handleUserAuthentificationConfirmation(message);
		break;

	case 'c':
		handleUserCreationConfirmation(message);
		break;
	}
}

void MessageDispatcher::dispatch(const std::string& message)
{
	// Check message validity.
	uint32_t messageSize = serializer_.deserializeInteger(message.c_str());
	//std::cout << "Message received: " << message << std::endl;
	if (message.size() <= 5)
	{
		std::cout << "Unexpected message received :" << message << std::endl;
		return;
	}

	switch (message[4])
	{
	case 'e':
		handleMapEditionMessage(message);
		break;

	case 'c':
		TestCallback(message);
		break;

	case 'm':
		handleMapSystemMessage(message);
		break;

	case 'u':
		handleUserSystemMessage(message);
		break;

	case 'p':
		handlePhysicMessage(message);
		break;

	default:
		std::cout << "Unexpected message received" << message << std::endl;
	}
}

}