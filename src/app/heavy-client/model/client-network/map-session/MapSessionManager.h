#ifndef MAP_SESSION_MANAGER
#define MAP_SESSION_MANAGER

#include <unordered_map>
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

	MapSession* getServerSession(const std::string& mapId);
	MapSession* createServerSession(const std::string& mapId, char mapType, const std::string& mapName);
	void deleteServerSession(const std::string& mapid);

private:
	std::unordered_map<std::string, MapSession> serverMapSessions_;
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
