#ifndef ABSTRACT_MAP_ROOM_H
#define ABSTRACT_MAP_ROOM_H

#include "MultiUserSystem.h"
#include "EntityTree.h"

namespace server
{

class AbstractMapRoom : public MultiUserSystem
{
public:	
	AbstractMapRoom();
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

	virtual void handleRelativePositionUpdateMessage(User* sender, const std::string& message);
	virtual void handleAbsolutePositionUpdateMessage(User* sender, const std::string& message);
	virtual void handleLinearVelocityUpdateMessage(User* sender, const std::string& message);
	virtual void handleAngularVelocityUpdateMessage(User* sender, const std::string& message);
	virtual void handleRotationUpdateMessage(User* sender, const std::string& message);
	virtual void handleScaleUpdateMessage(User* sender, const std::string& message);

	virtual void buildEntityCreationMessage(Entity* entity, std::string& message);
};

}
#endif // ABSTRACT_MAP_ROOM