#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "Observer.h"

#include <unordered_map>

namespace client_network
{
	class NetworkManager;
	class MapSessionManager;
	class MapSession;
}

class ArbreRendu;

namespace event_handler
{

class EventHandler
{
public:
	EventHandler() = default;
	~EventHandler() = default;

	inline void setNetworkManager(client_network::NetworkManager* networkManager);
	inline void setMapSessionManager(client_network::MapSessionManager* entityTree);
	inline void setEntityTree(ArbreRendu* entityTree);

	virtual void onEntityCreated();

	// Map edition
	void onEntityCreated(uint8_t entityType, uint32_t parentId, const glm::vec3& absPos,
		const glm::vec3& relPos, const glm::vec3& rotation, const glm::vec3& scale, 
		uint32_t entityId, uint32_t userId);

	void onEntityDeleted(uint32_t entityId);
	void onEntitySelected(uint32_t entityId, bool isSelected, uint32_t userId);

	// Map system
	void onNewMapCreated(char mapType, uint32_t mapId, std::string& name, char nUsers = 0);
	void onUserJoinedMap(uint32_t mapId, uint32_t userId);
	void onUserLeftCurrentMapSession(uint32_t userId);
	void onUserAuthentified(uint32_t userId);

	// Entity properties
	void onEntityPropertyUpdated(uint32_t entityId, char propertyType, const glm::vec3& propertyValue);

private:
	client_network::NetworkManager* networkManager_ = nullptr;
	client_network::MapSessionManager* mapSessionManager_ = nullptr;
	client_network::MapSession* currentSession_ = nullptr;

	ArbreRendu* entityTree_ = nullptr;
};

inline void EventHandler::setNetworkManager(client_network::NetworkManager* networkManager)
{
	networkManager_ = networkManager;
}

inline void EventHandler::setMapSessionManager(client_network::MapSessionManager* mapSessionManager)
{
	mapSessionManager_ = mapSessionManager;
}

inline void EventHandler::setEntityTree(ArbreRendu* entityTree)
{
	entityTree_ = entityTree;
}

}

#endif // EVENT_HANDLER_H