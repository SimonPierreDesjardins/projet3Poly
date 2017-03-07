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

	virtual void onEntitySelected();
	virtual void onEntityMovedRelative(int entityId, const glm::vec3& position);
	virtual void onEntityMovedAbsolute(int entityId, const glm::vec3& position);
	virtual void onEntityResized();
	virtual void onEntityRotated();

	virtual void onEntityCreated(const std::string& type);
	virtual void onEntityDeleted();

private:
	client_network::NetworkManager* networkManager_ = nullptr;
};

}

#endif // EVENT_HANDLER_H