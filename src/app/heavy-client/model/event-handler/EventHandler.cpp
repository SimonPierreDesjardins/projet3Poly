#include "EventHandler.h"

void EventHandler::requestConnection(const std::string& hostName, const std::string& port)
{
	connection_.requestConnection(hostName, port);
}
