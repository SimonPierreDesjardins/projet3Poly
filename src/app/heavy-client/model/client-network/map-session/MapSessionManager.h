#ifndef MAP_SESSION_MANAGER
#define MAP_SESSION_MANAGER

#include <memory>

#include "MapSession.h"

class ArbreRendu;

namespace client_network
{

class NetworkManager;

class MapSessionManager
{
public:
	MapSessionManager(ArbreRendu* arbre, NetworkManager* network);
	~MapSessionManager() = default;

	inline MapSession* getLocalMapSession();
	MapSession* getServerSession(uint32_t mapId);

	MapSession* createServerSession(uint32_t mapId, char mapType, const std::string& mapName);
	void deleteServerSession(uint32_t mapid);

private:
	std::unordered_map<uint32_t, MapSession> serverMapSessions_;
	MapSession localMapSession_;

	ArbreRendu* tree_;
	NetworkManager* network_;

	MapSessionManager() = delete;
};

inline MapSession* MapSessionManager::getLocalMapSession()
{
	return &localMapSession_;
}

}

#endif // MAP_SESSION_MANAGER_H
