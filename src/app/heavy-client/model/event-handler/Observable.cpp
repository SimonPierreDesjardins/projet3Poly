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
	// TODO: check if observer exists
	assert(observer != nullptr);
	observers_.insert(std::pair<int, Observer*>(observer->getId(), observer));
}

void Observable::removeObserver(Observer* observer) 
{
	assert(observer != nullptr);
	observers_.erase(observer->getId());
}

void Observable::notifyEntitySelected()
{

}

void Observable::notifyEntityMovedRelative(int entityId, const glm::vec3& position)
{
	std::unordered_map<int, Observer*>::iterator it;
	for (it = observers_.begin(); it != observers_.end(); it++)
	{
		it->second->onEntityMovedRelative(entityId, position);
	}
}

void Observable::notifyEntityMovedAbsolute(int entityId, const glm::vec3& position)
{
	std::unordered_map<int, Observer*>::iterator it;
	for (it = observers_.begin(); it != observers_.end(); it++)
	{
		it->second->onEntityMovedAbsolute(entityId, position);
	}
}

void Observable::notifyEntityResized(int entityId, const glm::vec3& position)
{
	
}

void Observable::notifyEntityRotated(int entityId, const glm::vec3& position)
{

}

void Observable::notifyEntityCreated()
{

}

void Observable::notifyEntityDeleted()
{

}

}