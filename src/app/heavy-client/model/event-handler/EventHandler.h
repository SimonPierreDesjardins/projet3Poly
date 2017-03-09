#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "Observer.h"

namespace client_network
{
	class NetworkManager;
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
	inline void setEntityTree(ArbreRendu* entityTree);

	virtual void onEntityCreated(NoeudAbstrait* noeud);
	virtual void requestEntityCreation(uint32_t entityId, uint8_t type, uint32_t parentId,
		const glm::dvec3& absolutePosition, const glm::dvec3& relativePosition);

private:
	client_network::NetworkManager* networkManager_ = nullptr;
	ArbreRendu* entityTree_;
	
};

inline void EventHandler::setNetworkManager(client_network::NetworkManager* networkManager)
{
	networkManager_ = networkManager;
}

inline void EventHandler::setEntityTree(ArbreRendu* entityTree)
{
	entityTree_ = entityTree;
}

}

#endif // EVENT_HANDLER_H