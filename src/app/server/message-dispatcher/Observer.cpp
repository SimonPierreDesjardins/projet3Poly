#include "Observer.h"

namespace server
{

Observer::Observer(char systemType)
	: systemType_(systemType)
{
}

Observer::~Observer()
{
}

void Observer::onReceivedMessage(const std::string& message)
{
}

void Observer::onDisconnected(uint32_t disconnectedUserId)
{
}

}