#ifndef ABSTRACT_MAP_ROOM_H
#define ABSTRACT_MAP_ROOM_H

#include "MultiUserSystem.h"
#include "EntityTree.h"
#include "Database\MapDatabase.h"

namespace server
{

class AbstractMapRoom : public MultiUserSystem
{
public:	
	AbstractMapRoom(MapInfo* mapInfo);
	virtual ~AbstractMapRoom() = 0;

protected:
	EntityTree tree_;
	char systemType_{ 'p' };

	virtual char GetSystemType();

	virtual void TreatUserJoin(User* user);
	virtual void TreatUserDisconnect(User* user);
	virtual void TreatUserMessage(User* sender, const std::string& message);

	virtual void handlePhysicMessage(User* sender, const std::string& message);
	virtual void handleMapEditionMessage(User* sender, const std::string& message);

	virtual void handleEntityCreationMessage(User* sender, const std::string& message);
	virtual void handleEntityDeletionMessage(User* sender, const std::string& message);
	virtual void handleEntitySelectionMessage(User* sender, const std::string& message);

	void updateEntityProperty(char property, Entity* entity, const Eigen::Vector3f& value);

	virtual void buildEntityCreationMessage(Entity* entity, std::string& message);

	// reference to the current map info
	MapInfo* mapInfo_ = nullptr;
};

}
#endif // ABSTRACT_MAP_ROOM