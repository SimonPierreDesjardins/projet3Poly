#ifndef CLIENT_MAP_SESSION
#define CLIENT_MAP_SESSION

#include <unordered_map>
#include <queue>
#include <stack>
#include <mutex>

#include "glm/glm.hpp"
#include "NetworkStandard.h"
#include "NetworkManager.h"

#include "MapSession.h"

class ArbreRendu;
class NoeudAbstrait;
class PhysicsComponent;
class ModeAbstrait;

namespace engine {
	class SimulationEngine;
}

namespace client_network
{

class ClientMapSession : public engine::MapSession
{
public:
	struct UserInfo
	{
		uint32_t userId;
		std::string userName;
		glm::vec4 selectionColor;
	};

	struct SessionInfo
	{
		char mapType;
		uint32_t mapId;
		std::string mapName;
	};

	SessionInfo info;

	ClientMapSession(engine::SimulationEngine* engine, NetworkManager* network);
	virtual ~ClientMapSession() = default;

	uint32_t getThisUserId() override;

	void synchronizedAnimate(double dt, ModeAbstrait* mode);
	void mapReady(ModeAbstrait* mode);

	// Entity created
	virtual void localEntityCreated(NoeudAbstrait* entity) override;
	void serverEntityCreated(uint8_t type, uint32_t parentId,
		const glm::vec3& relPos, const glm::vec3& absPos,
		const glm::vec3& rotation, const glm::vec3& scale,
		uint32_t entityId, uint32_t userId);

	// Entity deleted
	virtual void deleteLocalEntity(NoeudAbstrait* entity) override;
	void serverEntityDeleted(uint32_t entityId);

	// Entity selection
	virtual void updateSelectionStateLocalEntityAndChildren(NoeudAbstrait* entity, bool isSelected) override;
	void serverEntitySelected(uint32_t entityId, bool isSelected, uint32_t userId);

	void serverEntityPropertyUpdated(uint32_t entityId, Networking::PropertyType, const glm::vec3& updatedProperty);
	virtual void localEntityPropertyUpdated(NoeudAbstrait* entity, Networking::PropertyType, const glm::vec3& updatedProperty) override;

	void setIsOnlineSession(bool isOnline);

	void requestToLeaveMapSession();
	void serverUserLeftMapSession(uint32_t userId);

	void addUser(uint32_t userId, const std::string& userName = "");
	void removeUser(uint32_t userId);
	void clearUsers();

private:
	
	std::mutex pendingQueueLock_;

	ArbreRendu* entityTree_;
	NetworkManager* network_;
	ModeAbstrait* currentMode_ = nullptr;
	bool isOnline_ = false;

	std::stack<glm::vec4> selectionColors;
	std::unordered_map<uint32_t, UserInfo> users_;
	std::unordered_map<uint32_t, NoeudAbstrait*> confirmedEntities_;
	std::queue<NoeudAbstrait*> pendingEntityCreationRequests_;

	void sendEntityCreationRequest(NoeudAbstrait* entity);
	void clearMapSession();

	void createServerEntity(const PhysicsComponent& physics, uint8_t type, uint32_t entityId, uint32_t parendId, uint32_t userId);
	void confirmLocalEntity(NoeudAbstrait* entity, uint32_t entityId);


	ClientMapSession() = delete;
};

}

#endif // CLIENT_MAP_SESSION