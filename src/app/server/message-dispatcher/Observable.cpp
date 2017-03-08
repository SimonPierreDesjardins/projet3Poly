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
	ObserversContainer::iterator it = observers_.find(message[4]);
	if (it != observers_.end())
	{
		it->second->onReceivedMessage(sender, message);
	}
}

void Observable::notifyDisconnected(User* disconnectedUser)
{
	ObserversContainer::iterator it;
	for (it = observers_.begin(); it != observers_.end(); ++it)
	{
		it->second->onDisconnected(disconnectedUser);
	}
}

void Observable::addSystemObserver(Observer* observer, char observedSystem)
{
	assert(observer != nullptr);
	observers_.insert(std::make_pair(observedSystem, observer));
}

void Observable::removeSystemObserver(char observedSystem) 
{
	observers_.erase(observedSystem);
}

}