#include "Observer.h"

#include "User.h"

namespace server
{

Observer::Observer(char systemType)
	: systemType_(systemType)
{
}

Observer::~Observer()
{
}

void Observer::onReceivedMessage(User* user, const std::string& message)
{
}

void Observer::onDisconnected(User* user)
{
}

}