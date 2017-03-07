#include "NetworkManager.h"

#include "EventHandler.h"

namespace event_handler
{

EventHandler::EventHandler(client_network::NetworkManager* networkManager)
	: networkManager_(networkManager)
{
}

void EventHandler::handleLocalEvent(const LocalEvent& localEvent)
{
	networkManager_->sendMessage(localEvent.getMessage());
}

}

