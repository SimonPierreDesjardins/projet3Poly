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
}

void Observable::notifyDisconnected(int observerId)
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
}

}