#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "NetworkManager.h"

#include "Observer.h"

namespace event_handler
{

class EventHandler : public Observer
{
public:
	EventHandler(client_network::NetworkManager* networkManager);
	~EventHandler() = default;

	virtual void handleLocalEvent(const LocalEvent& localEvent);
private:
	client_network::NetworkManager* networkManager_ = nullptr;
	
};

}

#endif // EVENT_HANDLER_H