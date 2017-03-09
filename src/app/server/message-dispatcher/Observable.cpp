#include <cassert>

#include "Observer.h"
#include "Observable.h"

#include "User.h"

#include "NetworkStandard.h"

namespace server
{

Observable::~Observable()
{
}

void Observable::dispatchReceivedMessage(User* sender, const std::string& message)
{
	// TODO : Check message validity.
	// The 4 first bytes are for the size, we dispatch according to the 5th byte
	ObserversContainer::iterator it = observers_.find(message[Networking::MessageStandard::SYSTEM]);
	if (it != observers_.end())
	{
		it->second->onUserMessageReceived(sender, message);
	}
}

void Observable::notifyDisconnected(User* disconnectedUser)
{
	ObserversContainer::iterator it;
	for (it = observers_.begin(); it != observers_.end(); ++it)
	{
		it->second->onUserDisconnected(disconnectedUser);
	}
	observers_.clear();
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