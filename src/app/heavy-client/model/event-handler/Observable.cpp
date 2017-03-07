#include <cassert>

#include "Observer.h"

#include "Observable.h"

namespace event_handler
{

Observable::~Observable()
{
}


void Observable::addObserver(Observer* observer)
{
	assert(observer != nullptr);
	observers_.insert(std::pair<int, Observer*>(observer->getId(), observer));
}

void Observable::removeObserver(Observer* observer) 
{
	assert(observer != nullptr);
	observers_.erase(observer->getId());
}

void Observable::notify(const LocalEvent& localEvent)
{
	std::unordered_map<int, Observer*>::iterator it;
	for (it = observers_.begin(); it != observers_.end(); it++)
	{
		it->second->handleLocalEvent(localEvent);
	}
}

}