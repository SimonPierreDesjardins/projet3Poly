#include "EventHandler.h"


EventHandler::EventHandler()
{
	requestConnection("192.168.1.10", "5000");
}

void EventHandler::requestConnection(const std::string& hostName, const std::string& port)
{
	connection_.requestConnection(hostName, port);
}
