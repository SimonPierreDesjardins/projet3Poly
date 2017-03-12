#include "EventHandler.h"
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

void MessageDispatcher::handleReceivedMessage(const char* message, int32_t size)
{
	// TODO: Check for total message size here and handle messages bigger than size
	queueLock_.lock();
	messageQueue_.emplace(std::string(message, size));
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

void MessageDispatcher::handleEntityCreationMessage(const std::string& message)
{
	if (message.size() < 83)
	{
		// TODO: Log error here.
		return;
	}

	uint8_t  entityTupe = serializer_.deserializeChar(message[6]);
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
	std::string userId = message.substr(63);
}

void MessageDispatcher::handleMapEditionMessage(const std::string& message)
{
	switch (message[5])
	{
	case 'c':
		handleEntityCreationMessage(message);
		break;
	}
}

void MessageDispatcher::handleMapCreationMessage(const std::string& message)
{
	char type = message[6];
	std::string mapId = message.substr(7, 20);
	std::string name = message.substr(27);
	eventHandler_->onNewMapCreated(type, mapId, name);
}

void MessageDispatcher::handleMapJoinMessage(const std::string& message)
{
	std::string mapId = message.substr(6, 20); 
	std::string userId = message.substr(26);
	eventHandler_->onUserJoinedMap(mapId, userId);
}

void MessageDispatcher::handleMapQuitMessage(const std::string& message)
{

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

	default:
		std::cout << "Unexpected message received" << message << std::endl;
		break;

	}
}

void MessageDispatcher::handleUserAuthentificationConfirmation(const std::string& message)
{
	char authResult = message[6];
	std::string userId = message.substr(7);
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
	std::cout << "Message received: " << message << std::endl;
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

	case 'm':
		handleMapSystemMessage(message);
		break;

	case 'u':
		handleUserSystemMessage(message);
		break;

	case 'c':
		break;

	case 'p':
		break;

	default:
		std::cout << "Unexpected message received" << message << std::endl;
	}
}

}