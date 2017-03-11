#include "FacadeModele.h"

#include "NetworkManager.h"
#include "MapSessionManager.h"
#include "ArbreRendu.h"

#include "EventHandler.h"

namespace event_handler
{

void EventHandler::onEntityCreated(NoeudAbstrait* noeud)
{
	const glm::dvec3& relPos = noeud->obtenirPositionRelative();
	const glm::dvec3& absPos = noeud->obtenirPositionCourante();
}

void EventHandler::requestEntityCreation(uint32_t entityId, uint8_t type, uint32_t parentId,
	const glm::dvec3& absolutePosition, const glm::dvec3& relativePosition)
{
		
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
			FacadeModele::obtenirInstance()->setOnlineMapMode((Mode)(mapSession->info.mapType), mapSession);
		}
	}
}

void EventHandler::onNewMapCreated(char mapType, const std::string& mapId, std::string& name)
{
	// TODO: Remove this and use the ui.
	networkManager_->requestToJoinMapSession(mapId);
}

void EventHandler::onUserAuthentified(const std::string& userId)
{
	// TODO: notify the ui here.
	networkManager_->setUserId(userId);
}

}

