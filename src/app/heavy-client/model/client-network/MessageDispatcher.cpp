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

void MessageDispatcher::dispatch(const std::string& message)
{
	// parse the message here.
}

}