#include "NetworkStandard.h"

#include "EventHandler.h"
#include "FacadeInterfaceNative.h"
#include <iostream>

#include "MessageDispatcher.h"

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

void MessageDispatcher::handleReceivedMessage(const char* buffer, int32_t size)
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
	uint32_t entityId = serializer_.deserializeInteger(message.data() + Networking::MessageStandard::DATA_START);
	char propertyType = message[Networking::MessageStandard::COMMAND];
	glm::vec3 updatedProperty;
	updatedProperty.x = serializer_.deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 4);
	updatedProperty.y = serializer_.deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 8);
	updatedProperty.z = serializer_.deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 12);
	eventHandler_->onEntityPropertyUpdated(entityId, propertyType, updatedProperty);
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
	char selectionState = message[Networking::MessageStandard::DATA_START + 4];
	uint32_t userId = serializer_.deserializeInteger(message.data() + Networking::MessageStandard::DATA_START + 5);
	eventHandler_->onEntitySelected(entityId, (bool)(selectionState), userId);
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
	char type = message[6];
	uint32_t mapId = serializer_.deserializeInteger(&message[7]);
	std::string name = message.substr(11);
	eventHandler_->onNewMapCreated(type, mapId, name);
}

void MessageDispatcher::handleMapJoinMessage(const std::string& message)
{
	uint32_t mapId = serializer_.deserializeInteger(&message[6]);
	uint32_t userId = serializer_.deserializeInteger(&message[10]);
	eventHandler_->onUserJoinedMap(mapId, userId);
}

void MessageDispatcher::handleMapQuitMessage(const std::string& message)
{

}

void MessageDispatcher::handleMapListMessage(const std::string& message)
{
	uint32_t mapId = 0;
	std::string mapName;
	char mapType = 0;
	char nUsers = 0;
	size_t iCurrentEntry = 6;
	bool continueParsing = message.size() >= 12;

	while (continueParsing)
	{
		mapId = serializer_.deserializeInteger(message.data() + iCurrentEntry);
		mapType = message[iCurrentEntry + 4];
		nUsers = message[iCurrentEntry + 5];

		size_t nameBegin = iCurrentEntry + 6;
		size_t nameEnd = message.find(';', nameBegin);
		if (nameEnd == std::string::npos)
		{
			nameEnd = message.size();
			continueParsing = false;
		}
		mapName = message.substr(nameBegin, nameEnd - nameBegin);
		eventHandler_->onNewMapCreated(mapType, mapId, mapName, nUsers);
		iCurrentEntry = nameEnd + 1;
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
		break;

	default:
		std::cout << "user authentification failed." << std::endl;
	}
}

void MessageDispatcher::handleUserSystemMessage(const std::string& message)
{
	switch (message[5])
	{
	case 'a':
		handleUserAuthentificationConfirmation(message);
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