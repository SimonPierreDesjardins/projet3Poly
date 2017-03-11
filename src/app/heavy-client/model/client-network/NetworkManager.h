#ifndef CLIENT_NETWORK_NETWORK_MANAGER_H
#define CLIENT_NETWORK_NETWORK_MANAGER_H

#include "Connection.h"
#include "Observable.h"
#include "Serializer.h"
#include "MessageDispatcher.h"

#include "glm/glm.hpp"

namespace event_handler
{
	class EventHandler;
}

namespace client_network
{

class NetworkManager
{
public:
	NetworkManager(event_handler::EventHandler* eventHandler);
	~NetworkManager() = default;

	inline const std::string& getUserId() const;
	inline void setUserId(const std::string& userId);

	inline bool isConnected() const;
	inline void closeConnection();

	inline bool requestConnection(const std::string& hostName, const std::string& port);

	void createProfile(const std::string& profileName);

	void authenticate(const std::string& profileName);

	void requestMapCreation(const std::string& mapName, uint8_t mapType);
	void requestToJoinMapSession(const std::string& mapId);
	void requestToleaveMapSession();

	void requestEntityCreation(uint8_t type, uint32_t parentId, 
		                       const glm::vec3& relPos, const glm::vec3& absPos,
		                       const glm::vec3& rotation, const glm::vec3& scale);

	inline void sendMessage(const std::string& message);
	void sendSizePrefixedMessage(std::string& message);

	void handleServerMessage(const std::string& message);

private:
	MessageDispatcher dispatcher_;
	Connection connection_;
	Serializer serializer_;
	std::string userId_;

	bool isAuthentified_ = false;

	NetworkManager() = delete;
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

inline void NetworkManager::sendMessage(const std::string& message)
{
	connection_.sendMessage(message);
}

inline const std::string& NetworkManager::getUserId() const
{
	return userId_;
}

inline void NetworkManager::setUserId(const std::string& userId)
{
	userId_ = userId;
}

}

#endif // CLIENT_NETWORK_NETWORK_MANAGER_H