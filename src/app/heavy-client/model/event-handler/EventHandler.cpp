#include "FacadeModele.h"

#include "NetworkManager.h"
#include "MapSessionManager.h"
#include "ArbreRendu.h"

#include "EventHandler.h"

namespace event_handler
{

void EventHandler::onEntityCreated()
{
}

void EventHandler::onEntityCreated(uint8_t entityType, uint32_t parentId, 
	const glm::vec3& absPos, const glm::vec3& relPos, 
	const glm::vec3& rotation, const glm::vec3& scale,
	uint32_t entityId, const std::string& userId)
{
	if (currentSession_ != nullptr)
	{
	}
}

void EventHandler::onUserJoinedMap(const std::string& mapId, const std::string& userId)
{
	client_network::MapSession* mapSession = mapSessionManager_->getServerSession(mapId);
	// The map exists on the client.
	if (mapSession != nullptr)
	{
		// If the user that joined the map is me.
		if (userId == networkManager_->getUserId())
		{
			currentSession_ = mapSession;
			FacadeModele::obtenirInstance()->setOnlineMapMode((Mode)(mapSession->info.mapType), mapSession);
		}
	}
}

void EventHandler::onNewMapCreated(char mapType, const std::string& mapId, std::string& name)
{
	mapSessionManager_->createServerSession(mapId, mapType, name);
	// TODO: Remove this and use the ui.
	networkManager_->requestToJoinMapSession(mapId);
}

void EventHandler::onUserAuthentified(const std::string& userId)
{
	// TODO: notify the ui here.
	networkManager_->setUserId(userId);
}

}