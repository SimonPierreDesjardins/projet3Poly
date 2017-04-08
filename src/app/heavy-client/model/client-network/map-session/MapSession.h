#ifndef MAP_SESSION
#define MAP_SESSION

#include <unordered_map>
#include <queue>
#include <stack>
#include <mutex>
#include "glm/glm.hpp"
#include "NetworkStandard.h"

class ArbreRendu;
class NoeudAbstrait;
class PhysicsComponent;
class ModeAbstrait;

namespace engine {
	class SimulationEngine;
}

namespace client_network
{

class NetworkManager;

class MapSession
{
public:
	struct UserInfo
	{
		uint32_t userId;
		std::string userName;
		glm::vec4 selectionColor;
		// TODO: handle permissions here.
	};

	struct SessionInfo
	{
		char mapType;
		uint32_t mapId;
		std::string mapName;
		// TODO: handle permissions here.
	};

	SessionInfo info;

	MapSession(engine::SimulationEngine* engine, NetworkManager* network);
	virtual ~MapSession() = default;

	uint32_t getThisUserId() const;

	void synchronizedAnimate(double dt, ModeAbstrait* mode);

	void mapReady(ModeAbstrait* mode);

	// Entity created
	void localEntityCreated(NoeudAbstrait* entity);
	void serverEntityCreated(uint8_t type, uint32_t parentId,
		const glm::vec3& relPos, const glm::vec3& absPos,
		const glm::vec3& rotation, const glm::vec3& scale,
		uint32_t entityId, uint32_t userId);

	// Entity deleted
	void deleteLocalEntity(NoeudAbstrait* entity);
	void serverEntityDeleted(uint32_t entityId);

	// Entity selection
	void updateSelectionStateLocalEntityAndChildren(NoeudAbstrait* entity, bool isSelected);
	void serverEntitySelected(uint32_t entityId, bool isSelected, uint32_t userId);

	// Property update
	void serverEntityPropertyUpdated(uint32_t entityId, Networking::PropertyType, const glm::vec3& updatedProperty);
	void localEntityPropertyUpdated(NoeudAbstrait* entity, Networking::PropertyType, const glm::vec3& updatedProperty);

	void setIsOnlineSession(bool isOnline);

	void requestToLeaveMapSession();
	void serverUserLeftMapSession(uint32_t userId);

	void addUser(uint32_t userId, const std::string& userName = "");
	void removeUser(uint32_t userId);
	void clearUsers();

private:
	
	std::mutex sessionLock_;

	ModeAbstrait* currentMode_ = nullptr;
	engine::SimulationEngine* engine_;
	ArbreRendu* entityTree_;
	NetworkManager* network_;

	bool isOnline_ = false;

	std::stack<glm::vec4> selectionColors;
	std::unordered_map<uint32_t, UserInfo> users_;
	std::unordered_map<uint32_t, NoeudAbstrait*> confirmedEntities_;
	std::queue<NoeudAbstrait*> pendingEntityCreationRequests_;

	void sendEntityCreationRequest(NoeudAbstrait* entity);
	void clearMapSession();

	void createServerEntity(const PhysicsComponent& physics, uint8_t type, uint32_t entityId, uint32_t parendId, uint32_t userId);
	void confirmLocalEntity(NoeudAbstrait* entity, uint32_t entityId);


	MapSession() = delete;
};


}

#endif // MAP_SESSION