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
	MapSession* newMapSessionPtr = nullptr;
	MapSession newMapSession(tree_, network_);
	newMapSession.info.mapId = mapId;
	newMapSession.info.mapType = mapType;
	newMapSession.info.mapName = mapName;
	auto pair = serverMapSessions_.insert(std::make_pair(mapId, std::move(newMapSession)));
	if (pair.second)
	{
		newMapSessionPtr = &pair.first->second;
	}
	return newMapSessionPtr;
}

void MapSessionManager::deleteServerSession(uint32_t mapId)
{
	serverMapSessions_.erase(mapId);
}

}