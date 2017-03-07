#ifndef CLIENT_NETWORK_NETWORK_MANAGER_H
#define CLIENT_NETWORK_NETWORK_MANAGER_H

#include "Connection.h"
#include "glm/glm.hpp"

namespace client_network
{

class NetworkManager
{
public:
	NetworkManager() = default;
	~NetworkManager() = default;

	inline bool isConnected() const;
	inline void closeConnection();

	inline bool requestConnection(const std::string& hostName, const std::string& port);
	inline void createProfile(const std::string& profileName);
	inline void authenticate(const std::string& profileName);

	void joinRoom(int roomId);

	void requestUpdateRelativePosition(int entityId, const glm::vec3& position);
	void requestUpdateAbsolutePosition(int entityId, const glm::vec3& position);
	void requestUpdateSize(int entityId, const glm::vec3& size);
	void requestUpdateRotation(int entityId, const glm::vec3& rotation);
	void requestUpdateSelected(int entityId, bool isSelected);

	void requestEntityCreation(const std::string& type);

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

inline bool NetworkManager::requestConnection(const std::string& hostName, const std::string& port)
{
	return connection_.openConnection(hostName, port);
}

inline void NetworkManager::createProfile(const std::string& profileName)
{

}

inline void NetworkManager::authenticate(const std::string& profileName)
{

}

}

#endif // CLIENT_NETWORK_NETWORK_MANAGER_H