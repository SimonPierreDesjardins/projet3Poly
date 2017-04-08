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

void EventHandler::onNewMapCreated(uint32_t mapId, char mapType, char nUsers, char permissions, uint32_t adminId, std::string& name)
{
	mapSessionManager_->createServerSession(mapId, mapType, name);
	bool test = adminId == userId_;
	AddMap(name, (bool)(permissions), true, mapType, nUsers, adminId == userId_, mapId);
}

void EventHandler::onUserJoinedMap(char result, uint32_t mapId, uint32_t userId)
{
	// On a failed join, do something
	switch (result)
	{
	case 's':
		{
			client_network::ClientMapSession* mapSession = mapSessionManager_->getServerSession(mapId);
			// The map exists on the client.
			if (mapSession != nullptr)
			{
				mapSession->addUser(userId);
				// If the user that joined the map is me.
				if (userId == networkManager_->getUserId())
				{
					Loading(1);
					currentSession_ = mapSession;
					mapConnect(mapId, MAP_JOINED);
				}
			}
		}
		break;

	case 'f':
		mapConnect(mapId, MAP_FULL);
		break;

	case 'd':
		mapConnect(mapId, MAP_WRONG_PASSWORD);
		break;

	default:
		//TODO: deal with error here
		break;
	}

}

void EventHandler::onMapReady(uint32_t mapId)
{
	if (currentSession_ && currentSession_->info.mapId == mapId)
	{
		FacadeModele::obtenirInstance()->setOnlineMapMode((Mode)(currentSession_->info.mapType), currentSession_);
		Loading(0);
	}
}

void EventHandler::onUserLeftCurrentMapSession(uint32_t userId)
{
	if (currentSession_)
	{
		currentSession_->serverUserLeftMapSession(userId);
		if (userId == networkManager_->getUserId())
		{
			currentSession_ = nullptr;
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
	if (currentSession_ != nullptr)
	{
		currentSession_->serverEntityPropertyUpdated(entityId, (Networking::PropertyType)(propertyType), propertyValue);
	}
}

}