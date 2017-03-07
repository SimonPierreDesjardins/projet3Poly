#include "Observer.h"

namespace server
{

int Observer::nextObservedId_ = 0;

Observer::~Observer()
{
	id_ = nextObservedId_++;
}

void Observer::onReceivedMessage(const std::string& message)
{
}

void Observer::onDisconnected(int userId)
{
}

}