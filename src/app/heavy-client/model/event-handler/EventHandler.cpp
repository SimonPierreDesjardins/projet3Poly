#include "EventHandler.h"


EventHandler::EventHandler()
{
}

void EventHandler::requestConnection(const std::string& hostName, const std::string& port)
{
	network_.requestConnection(hostName, port);
}

void EventHandler::createProfile(const std::string& profileName)
{
	network_.createProfile(profileName);
}

void EventHandler::authenticate(const std::string& profileName)
{
	network_.authenticate(profileName);
}
