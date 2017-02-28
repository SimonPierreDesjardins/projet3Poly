#ifndef CLIENT_NETWORK_NETWORK_MANAGER_H
#define CLIENT_NETWORK_NETWORK_MANAGER_H

#include "Connection.h"

namespace client_network
{

class NetworkManager
{
public:
	NetworkManager() = default;
	~NetworkManager() = default;

	void requestConnection(const std::string& hostName, const std::string& port);
	void createProfile(const std::string& profileName);
	void authenticate(const std::string& profileName);

	void handleServerMessage(const std::string& message);

private:
	Connection connection_;
};

}

#endif // CLIENT_NETWORK_NETWORK_MANAGER_H