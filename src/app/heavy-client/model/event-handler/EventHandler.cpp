#include "FacadeModele.h"

#include "NetworkManager.h"
#include "MapSessionManager.h"
#include "ArbreRendu.h"

#include "EventHandler.h"
#include "FacadeInterfaceNative.h"
#include "MapJoin.cs"

namespace event_handler
{

void EventHandler::onUserDisconnected()
{
	GotDisconnected();
}

void EventHandler::onEntityCreated()
{
}

void EventHandler::onEntityCreated(uint8_t entityType, uint32_t parentId, 
	const glm::vec3& absPos, const glm::vec3& relPos, 
	const glm::vec3& rotation, const glm::vec3& scale,
	uint32_t entityId, uint32_t userId)
{
	client_network::ClientMapSession* currentSession = mapSessionManager_->getCurrentMapSession();
	if (currentSession != nullptr)
	{
		currentSession->serverEntityCreated(entityType, parentId, absPos, relPos, rotation, scale, entityId, userId);
	}
}

void EventHandler::onEntityDeleted(uint32_t entityId)
{
	client_network::ClientMapSession* currentSession = mapSessionManager_->getCurrentMapSession();
	if (currentSession != nullptr)
	{
		currentSession->serverEntityDeleted(entityId);
	}
}

void EventHandler::onEntitySelected(uint32_t entityId, bool isSelected, uint32_t userId)
{
	client_network::ClientMapSession* currentSession = mapSessionManager_->getCurrentMapSession();
	if (currentSession != nullptr)
	{
		currentSession->serverEntitySelected(entityId, isSelected, userId);
	}
}

void EventHandler::onNewMapCreated(uint32_t mapId, char mapType, char nUsers, char permissions, uint32_t adminId, std::string& name)
{
	mapSessionManager_->createServerSession(mapId, mapType, name);
	AddMap(name, (int)(permissions), true, mapType, nUsers, adminId == userId_, mapId);
}

void EventHandler::onUserJoinedMap(char result, uint32_t mapId, uint32_t userId)
{
	// On a failed join, do something
	switch (result)
	{
	case 's':
		{
			client_network::ClientMapSession* currentSession = mapSessionManager_->getServerSession(mapId);
			// The map exists on the client.
			if (currentSession)
			{
				currentSession->addUser(userId);
				// If the user that joined the map is me.
				if (userId == networkManager_->getUserId())
				{
					Loading(1);
					mapSessionManager_->joinMapSession(mapId);
					mapConnect(mapId, MAP_JOINED);
				}
			}
			mapConnect(mapId, USER_JOINED);
		}
		break;

	case 'f':
		mapConnect(mapId, MAP_FULL);
		break;

	case 'd':
		mapConnect(mapId, MAP_WRONG_PASSWORD);
		break;

	default:
		break;
	}

}

void EventHandler::onMapReady(uint32_t mapId)
{
	client_network::ClientMapSession* currentSession = mapSessionManager_->getCurrentMapSession();
	if (currentSession && currentSession->info.mapId == mapId)
	{
		FacadeModele::obtenirInstance()->assignerMode((Mode)(currentSession->info.mapType));
		Loading(0);
	}
}

void EventHandler::onUserLeftCurrentMapSession(uint32_t userId)
{
	client_network::ClientMapSession* currentSession = mapSessionManager_->getCurrentMapSession();
	if (currentSession)
	{
		if (userId != networkManager_->getUserId())
		{
			currentSession->serverUserLeftMapSession(userId);
		}
		else
		{
			mapSessionManager_->quitCurrentMapSession();
		}
	}
}

void EventHandler::onUserAuthentified(uint32_t userId)
{
	networkManager_->setUserId(userId);
	userId_ = userId;
}

void EventHandler::onEntityPropertyUpdated(uint32_t entityId, char propertyType, const glm::vec3& propertyValue)
{
	client_network::ClientMapSession* currentSession = mapSessionManager_->getCurrentMapSession();
	if (currentSession)
	{
		currentSession->serverEntityPropertyUpdated(entityId, (Networking::PropertyType)(propertyType), propertyValue);
	}
}

void EventHandler::onStackedPropertiesUpdate(uint32_t entityId, const PhysicsComponent& properties)
{
	client_network::ClientMapSession* currentSession = mapSessionManager_->getCurrentMapSession();
	if (currentSession)
	{
		currentSession->serverEntityPropertyUpdated(entityId, properties);
	}
}

}