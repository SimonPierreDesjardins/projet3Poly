#ifndef ABSTRACT_MAP_ROOM_H
#define ABSTRACT_MAP_ROOM_H

#include "MultiUserSystem.h"
#include "EntityTree.h"
#include "Database\MapDatabase.h"
#include "MapFileLoader.h"

namespace server
{

class AbstractMapRoom : public MultiUserSystem
{
public:	
	AbstractMapRoom(MapInfo* info, MapFileEntry* mapFile);
	virtual ~AbstractMapRoom() = 0;

	// reference to the current map info
	MapInfo* mapInfo = nullptr;

protected:
	EntityTree tree_;
	char systemType_{ 'p' };

	virtual char GetSystemType();

	virtual void TreatUserJoin(User* user);
	virtual void TreatUserDisconnect(User* user);
	virtual void TreatUserMessage(User* sender, const std::string& message);

	virtual void handlePhysicMessage(User* sender, const std::string& message);
	virtual void handleSinglePropertyMessage(User* sender, const std::string& message);
	virtual void handleStackedPropertyMessage(User* sender, const std::string& message);

	virtual void handleMapEditionMessage(User* sender, const std::string& message);

	virtual void handleEntityCreationMessage(User* sender, const std::string& message);
	virtual void handleEntityRemovalMessage(User* sender, const std::string& message);
	virtual void handleEntitySelectionMessage(User* sender, const std::string& message);

	void updateEntityProperty(char property, Entity* entity, const Eigen::Vector3f& value);

	virtual void buildEntityCreationMessage(Entity* entity, std::string& message);
	void buildEntitySelectedMessage(Entity* entity, std::string& message);


	MapFileLoader* mapFileLoader_;

	AbstractMapRoom() = delete;
};

}
#endif // ABSTRACT_MAP_ROOM