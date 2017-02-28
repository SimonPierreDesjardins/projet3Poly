#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "NetworkManager.h"

class EventHandler
{
public:
	EventHandler();
	~EventHandler() = default;

	void requestConnection(const std::string& hostName, const std::string& port);
	void createProfile(const std::string& profileName);
	void authenticate(const std::string& profileName);

private:
	client_network::NetworkManager network_;
};

#endif