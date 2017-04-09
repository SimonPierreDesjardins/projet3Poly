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

namespace engine
{

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

	MapSession(ArbreRendu* tree);
	virtual ~MapSession() = default;

	inline uint32_t getThisUserId() const;

	// Entity created
	virtual void localEntityCreated(NoeudAbstrait* entity) = 0;

	// Entity deleted
	virtual void deleteLocalEntity(NoeudAbstrait* entity) = 0;

	virtual void localEntityPropertyUpdated(NoeudAbstrait* entity, Networking::PropertyType, const glm::vec3& updatedProperty) = 0;
	virtual void localEntityPropertiesUpdated(NoeudAbstrait* entity) = 0;

	virtual void updateSelectionStateLocalEntityAndChildren(NoeudAbstrait* entity, bool isSelected) = 0;

	virtual uint32_t getThisUserId() = 0;

protected:

	ArbreRendu* entityTree_;

	MapSession() = delete;
};

}

#endif // MAP_SESSION