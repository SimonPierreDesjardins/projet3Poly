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

class EventHandler : public Observer
{
public:
	EventHandler() = default;
	~EventHandler() = default;

	inline void setNetworkManager(client_network::NetworkManager* networkManager);
	inline void setMapSessionManager(client_network::MapSessionManager* entityTree);
	inline void setEntityTree(ArbreRendu* entityTree);

	virtual void onEntityCreated(NoeudAbstrait* noeud);
	virtual void requestEntityCreation(uint32_t entityId, uint8_t type, uint32_t parentId,
		const glm::dvec3& absolutePosition, const glm::dvec3& relativePosition);

	void onNewMapCreated(char mapType, const std::string& mapId, std::string& name);
	void onUserJoinedMap(const std::string& mapId, const std::string& userId);
	void onUserAuthentified(const std::string& userId);

private:
	client_network::NetworkManager* networkManager_ = nullptr;
	client_network::MapSessionManager* mapSessionManager_ = nullptr;
	client_network::MapSession* currentSession = nullptr;

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