#include "FacadeModele.h"

#include "NetworkManager.h"
#include "MapSessionManager.h"
#include "ArbreRendu.h"

#include "EventHandler.h"
#include "FacadeInterfaceNative.h"

namespace event_handler
{

void EventHandler::onEntityCreated()
{
}

void EventHandler::onEntityCreated(uint8_t entityType, uint32_t parentId, 
	const glm::vec3& absPos, const glm::vec3& relPos, 
	const glm::vec3& rotation, const glm::vec3& scale,
	uint32_t entityId, uint32_t userId)
{
	if (currentSession_ != nullptr)
	{
		currentSession_->serverEntityCreated(entityType, parentId, absPos, relPos, rotation, scale, entityId, userId);
	}
}

void EventHandler::onEntityDeleted(uint32_t entityId)
{
	if (currentSession_ != nullptr)
	{
		currentSession_->serverEntityDeleted(entityId);
	}
}

void EventHandler::onEntitySelected(uint32_t entityId, bool isSelected, uint32_t userId)
{
	if (currentSession_ != nullptr)
	{
		currentSession_->serverEntitySelected(entityId, isSelected, userId);
	}
}

void EventHandler::onUserJoinedMap(uint32_t mapId, uint32_t userId)
{
	client_network::MapSession* mapSession = mapSessionManager_->getServerSession(mapId);
	// The map exists on the client.
	if (mapSession != nullptr)
	{
		mapSession->addUser(userId);
		// If the user that joined the map is me.
		if (userId == networkManager_->getUserId())
		{
			currentSession_ = mapSession;
			FacadeModele::obtenirInstance()->setOnlineMapMode((Mode)(mapSession->info.mapType), mapSession);
		}
	}
}

void EventHandler::onNewMapCreated(char mapType, uint32_t mapId, std::string& name, char nUsers)
{
	mapSessionManager_->createServerSession(mapId, mapType, name);
	// TODO: Remove this and use the ui.
	//networkManager_->requestToJoinMapSession(mapId);
	AddMap(name, true, mapType, nUsers, mapId);
}

void EventHandler::onUserAuthentified(uint32_t userId)
{
	// TODO: notify the ui here.
	networkManager_->setUserId(userId);
}

void EventHandler::onEntityPropertyUpdated(uint32_t entityId, char propertyType, const glm::vec3& propertyValue)
{
	if (currentSession_ != nullptr)
	{
		currentSession_->serverEntityPropertyUpdated(entityId, (Networking::PropertyType)(propertyType), propertyValue);
	}
}

}