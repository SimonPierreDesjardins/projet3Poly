#ifndef MAP_SESSION_MANAGER
#define MAP_SESSION_MANAGER

#include <memory>

#include "MapSession.h"

class ArbreRendu;

namespace engine {
	class SimulationEngine;
}

namespace client_network
{

class NetworkManager;

class MapSessionManager
{
public:
	MapSessionManager(engine::SimulationEngine* engine, NetworkManager* network);
	~MapSessionManager() = default;

	inline MapSession* getLocalMapSession();
	MapSession* getServerSession(uint32_t mapId);

	MapSession* createServerSession(uint32_t mapId, char mapType, const std::string& mapName);
	void deleteServerSession(uint32_t mapid);

	bool joinMapSession(uint32_t);
	void quitCurrentMapSession();

	inline MapSession* getCurrentMapSession();

private:
	std::unordered_map<uint32_t, MapSession> serverMapSessions_;
	MapSession localMapSession_;

	MapSession* currentMapSession_ = &localMapSession_;

	engine::SimulationEngine* engine_;
	NetworkManager* network_;

	MapSessionManager() = delete;
};

inline MapSession* MapSessionManager::getLocalMapSession()
{
	return &localMapSession_;
}

inline MapSession* MapSessionManager::getCurrentMapSession()
{
	if (currentMapSession_ == nullptr)
	{
		currentMapSession_ = &localMapSession_;
	}
	return currentMapSession_;
}



}

#endif // MAP_SESSION_MANAGER_H
