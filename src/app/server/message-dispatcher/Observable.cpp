#include <cassert>

#include "Observer.h"

#include "Observable.h"

namespace server
{

Observable::~Observable()
{
}

void Observable::dispatchReceivedMessage(const std::string& message)
{
	std::unordered_map<char, Observer*>::iterator it = observers_.find(message[5]);
	if (it != observers_.end())
	{
		it->second->onReceivedMessage(message);
	}
}

void Observable::notifyDisconnected(int disconnectedId)
{
	std::unordered_map<char, Observer*>::iterator it;
	for (it = observers_.begin(); it != observers_.end(); ++it)
	{
		it->second->onDisconnected(disconnectedId);
	}
}

void Observable::addObserver(Observer* observer)
{
	assert(observer != nullptr);
	observers_.insert(std::pair<int, Observer*>(observer->getSystemType(), observer));
}

void Observable::removeObserver(Observer* observer) 
{
	assert(observer != nullptr);
	observers_.erase(observer->getSystemType());
}

}