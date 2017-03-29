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

	inline const uint32_t getUserId() const;
	inline void setUserId(uint32_t userId);

	inline bool isConnected() const;
	inline void closeConnection();

	inline bool requestConnection(const std::string& hostName, const std::string& port);

	void createProfile(const std::string& profileName);
	void authenticate(const std::string& profileName);

	/// upload map at pathto the server. Path is full file path. This method is synchronous
	void uploadMap(const std::string& filePath);
	void requestMapCreation(const std::string& mapName, const std::string& password, uint8_t mapType, uint8_t isPrivate);
	void requestToJoinMapSession(uint32_t mapId);
	void requestToQuitMapSession();

	void requestEntityCreation(uint8_t type, uint32_t parentId, 
		                       const glm::vec3& relPos, const glm::vec3& absPos,
		                       const glm::vec3& rotation, const glm::vec3& scale);
	void requestEntityRemoval(uint32_t entityId);
	void requestEntitySelection(uint32_t entityId, char selectionState);

	void requestEntityPropertyUpdate(uint32_t entityId, char propertyType, const::glm::vec3& propertyValue);

	inline void sendMessage(const std::string& message);
	void sendSizePrefixedMessage(std::string& message);

	void handleServerMessage(const std::string& message);

private:
	MessageDispatcher dispatcher_;
	Connection connection_;
	Serializer serializer_;
	uint32_t userId_;

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

inline const uint32_t NetworkManager::getUserId() const
{
	return userId_;
}

inline void NetworkManager::setUserId(uint32_t userId)
{
	userId_ = userId;
}

}

#endif // CLIENT_NETWORK_NETWORK_MANAGER_H