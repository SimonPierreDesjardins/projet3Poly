#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "Connection.h"

class EventHandler
{
public:
	EventHandler() = default;
	~EventHandler() = default;

	void requestConnection(const std::string& hostName, const std::string& port);

private:
	client_network::Connection connection_;

};

#endif