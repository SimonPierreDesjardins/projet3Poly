#include "ArbreRendu.h"
#include "NetworkManager.h"

#include "MapSessionManager.h"

namespace client_network
{

MapSessionManager::MapSessionManager(ArbreRendu* tree, NetworkManager* network)
	: tree_(tree), network_(network), localMapSession_(tree, network)
{
}

MapSession* MapSessionManager::getServerSession(uint32_t mapId)
{
	MapSession* mapSessionFound = nullptr;
	auto it = serverMapSessions_.find(mapId);
	if (it != serverMapSessions_.end())
	{
		mapSessionFound = &it->second;
	}
	return mapSessionFound;
}

MapSession* MapSessionManager::createServerSession(uint32_t mapId, char mapType, const std::string& mapName)
{
	// Build the map inplace because move and copy contructor are deleted.
	auto pair = serverMapSessions_.emplace(std::piecewise_construct,
										   std::forward_as_tuple(mapId),
		                                   std::forward_as_tuple(tree_, network_));

	MapSession* newMapSession = nullptr;
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

}