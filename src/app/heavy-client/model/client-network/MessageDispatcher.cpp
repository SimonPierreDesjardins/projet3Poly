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
	// Message size should always be 39 according to our protocole.
	if (message.size() != 39)
	{
		// TODO: Log error here.
		return;
	}

	uint32_t entityId = serializer_.deserializeInteger(&message[6]);
	uint8_t  entityTupe = serializer_.deserializeChar(message[10]);
	uint32_t parentId = serializer_.deserializeInteger(&message[11]);

	float ax = serializer_.deserializeFloat(&message[15]);
	float ay = serializer_.deserializeFloat(&message[19]);
	float az = serializer_.deserializeFloat(&message[23]);

	float rx = serializer_.deserializeFloat(&message[27]);
	float ry = serializer_.deserializeFloat(&message[31]);
	float rz = serializer_.deserializeFloat(&message[35]);
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

void MessageDispatcher::dispatch(const std::string& message)
{
	// Check message validity.
	uint32_t messageSize = serializer_.deserializeInteger(message.c_str());
	if (message.size() != messageSize + 4)
	{
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
	}
}

}