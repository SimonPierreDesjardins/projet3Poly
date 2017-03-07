#include "NetworkManager.h"

#include "EventHandler.h"

namespace event_handler
{

EventHandler::EventHandler(client_network::NetworkManager* networkManager)
	: networkManager_(networkManager)
{
}

void EventHandler::onEntitySelected()
{
}

void EventHandler::onEntityMovedAbsolute(int entityId, const glm::vec3& position)
{
	networkManager_->requestUpdateAbsolutePosition(entityId, position);
}

void EventHandler::onEntityMovedRelative(int entityId, const glm::vec3& position)
{
	networkManager_->requestUpdateRelativePosition(entityId, position);
}

void EventHandler::onEntityResized()
{
}

void EventHandler::onEntityRotated()
{
}

void EventHandler::onEntityCreated(const std::string& type)
{
	networkManager_->requestEntityCreation(type);
}

void EventHandler::onEntityDeleted()
{
}

}

