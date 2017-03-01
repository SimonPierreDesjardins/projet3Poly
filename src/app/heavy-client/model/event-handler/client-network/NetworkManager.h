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

	inline bool isConnected() const;
	inline void closeConnection();

	void requestConnection(const std::string& hostName, const std::string& port);
	void createProfile(const std::string& profileName);
	void authenticate(const std::string& profileName);

	void handleServerMessage(const std::string& message);

private:
	Connection connection_;
};

inline bool NetworkManager::isConnected() const
{
	return connection_.isConnected();
}

inline void NetworkManager::closeConnection() 
{
	connection_.closeConnection();
}

}

#endif // CLIENT_NETWORK_NETWORK_MANAGER_H