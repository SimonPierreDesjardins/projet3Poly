#ifndef MAP_SESSION
#define MAP_SESSION

#include <unordered_map>
#include <queue>
#include <mutex>
#include "glm/glm.hpp"
#include "NetworkStandard.h"

class ArbreRendu;
class NoeudAbstrait;

namespace client_network
{

class NetworkManager;

class MapSession
{
public:
	struct SessionInfo
	{
		char mapType;
		std::string mapId;
		std::string mapName;
		// TODO handle permissions here.
	};

	SessionInfo info;
	MapSession(ArbreRendu* tree, NetworkManager* network);
	virtual ~MapSession() = default;

	void localEntityCreated(NoeudAbstrait* entity);

	void serverEntityCreated(uint8_t type, uint32_t parentId, 
		const glm::vec3& relPos, const glm::vec3& absPos, 
		const glm::vec3& rotation, const glm::vec3& scale,
		uint32_t entityId, uint32_t userId);

	void serverEntityPropertyUpdated(uint32_t entityId, Networking::PropertyType, const glm::vec3& updatedProperty);
	void localEntityPropertyUpdated(NoeudAbstrait* entity, Networking::PropertyType, const glm::vec3& updatedProperty);

	void setIsOnlineSession(bool isOnline);

private:
	std::mutex pendingQueueLock_;

	ArbreRendu* entityTree_;
	NetworkManager* network_;
	bool isOnline_ = false;

	std::unordered_map<uint32_t, NoeudAbstrait*> confirmedEntities_;
	std::queue<NoeudAbstrait*> pendingEntityCreationRequests_;

	void sendEntityCreationRequest(NoeudAbstrait* entity);

	MapSession() = delete;
};

}

#endif // MAP_SESSION