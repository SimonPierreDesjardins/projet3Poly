#include <cassert>

#include "Observer.h"
#include "Observable.h"

#include "User.h"

namespace server
{

Observable::~Observable()
{
}

void Observable::dispatchReceivedMessage(User* sender, const std::string& message)
{
	// The 4 first bytes are for the size, we dispatch according to the 5th byte
	std::unordered_map<char, Observer*>::iterator it = observers_.find(message[4]);
	if (it != observers_.end())
	{
		it->second->onReceivedMessage(sender, message);
	}
}

void Observable::notifyDisconnected(User* disconnectedUser)
{
	std::unordered_map<char, Observer*>::iterator it;
	for (it = observers_.begin(); it != observers_.end(); ++it)
	{
		it->second->onDisconnected(disconnectedUser);
	}
}

void Observable::addObserver(Observer* observer)
{
	assert(observer != nullptr);
	observers_.insert(std::pair<char, Observer*>(observer->getSystemType(), observer));
}

void Observable::removeObserver(Observer* observer) 
{
	assert(observer != nullptr);
	observers_.erase(observer->getSystemType());
}

}