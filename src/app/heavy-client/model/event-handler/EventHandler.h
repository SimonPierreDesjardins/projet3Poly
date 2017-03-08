#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "Observer.h"

namespace client_network
{
	class NetworkManager;
}

namespace event_handler
{

class EventHandler : public Observer
{
public:
	EventHandler() = default;
	~EventHandler() = default;

	inline void setNetworkManager(client_network::NetworkManager* networkManager);

	virtual void onEntityCreated(NoeudAbstrait* noeud);

private:
	client_network::NetworkManager* networkManager_ = nullptr;
	
};

inline void EventHandler::setNetworkManager(client_network::NetworkManager* networkManager)
{
	networkManager_ = networkManager;
}

}

#endif // EVENT_HANDLER_H