#ifndef MAP_SESSION_MANAGER
#define MAP_SESSION_MANAGER

#include <memory>

#include "ClientMapSession.h"

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

	inline ClientMapSession* getLocalMapSession();
	ClientMapSession* getServerSession(uint32_t mapId);

	ClientMapSession* createServerSession(uint32_t mapId, char mapType, const std::string& mapName);
	void deleteServerSession(uint32_t mapid);

	bool joinMapSession(uint32_t mapSession);

	void quitCurrentMapSession();
	void requestToLeaveCurrentMapSession();

	inline ClientMapSession* getCurrentMapSession();

private:
	std::unordered_map<uint32_t, ClientMapSession> serverMapSessions_;
	ClientMapSession localMapSession_;

	ClientMapSession* currentMapSession_ = &localMapSession_;

	engine::SimulationEngine* engine_;
	NetworkManager* network_;

	MapSessionManager() = delete;
};

inline ClientMapSession* MapSessionManager::getLocalMapSession()
{
	return &localMapSession_;
}

inline ClientMapSession* MapSessionManager::getCurrentMapSession()
{
	if (currentMapSession_ == nullptr)
	{
		currentMapSession_ = &localMapSession_;
	}
	return currentMapSession_;
}



}

#endif // MAP_SESSION_MANAGER_H
