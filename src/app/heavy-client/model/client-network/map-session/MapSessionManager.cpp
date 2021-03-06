#include "SimulationEngine.h"
#include "NetworkManager.h"

#include "MapSessionManager.h"

namespace client_network
{

MapSessionManager::MapSessionManager(engine::SimulationEngine* engine, NetworkManager* network)
	: engine_(engine), network_(network), localMapSession_(engine, network)
{
	localMapSession_.setIsOnlineSession(false);
}

ClientMapSession* MapSessionManager::getServerSession(uint32_t mapId)
{
	ClientMapSession* mapSessionFound = nullptr;
	auto it = serverMapSessions_.find(mapId);
	if (it != serverMapSessions_.end())
	{
		mapSessionFound = &it->second;
	}
	return mapSessionFound;
}

ClientMapSession* MapSessionManager::createServerSession(uint32_t mapId, char mapType, const std::string& mapName)
{
	// Build the map inplace because move and copy contructor are deleted.
	auto pair = serverMapSessions_.emplace(std::piecewise_construct,
										   std::forward_as_tuple(mapId),
		                                   std::forward_as_tuple(engine_, network_));

	ClientMapSession* newMapSession = nullptr;
	if (pair.second)
	{
		newMapSession = &pair.first->second;
		newMapSession->info.mapId = mapId;
		newMapSession->info.mapType = mapType;
		newMapSession->info.mapName = mapName;
		newMapSession->setIsOnlineSession(true);
	}
	return newMapSession;
}

void MapSessionManager::deleteServerSession(uint32_t mapId)
{
	serverMapSessions_.erase(mapId);
}

bool MapSessionManager::joinMapSession(uint32_t mapId)
{
	auto it = serverMapSessions_.find(mapId);
	bool mapFound = (it != serverMapSessions_.end());
	if (mapFound)
	{
		currentMapSession_ = &it->second;
	}
	return mapFound;
}

void MapSessionManager::quitCurrentMapSession()
{
	currentMapSession_->quitMapSession();
	currentMapSession_ = &localMapSession_;
}

void MapSessionManager::requestToLeaveCurrentMapSession()
{
	if (currentMapSession_->isOnline())
	{
		currentMapSession_->requestToLeaveMapSession();
	}
	else
	{
		quitCurrentMapSession();
	}
}

}