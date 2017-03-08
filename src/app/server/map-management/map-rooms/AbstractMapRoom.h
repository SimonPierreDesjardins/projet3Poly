#ifndef ABSTRACT_MAP_ROOM_H
#define ABSTRACT_MAP_ROOM_H

#include "MultiUserSession.h"
#include "EntityTree.h"

namespace server
{

class AbstractMapRoom : public MultiUserSession
{
public:	
	AbstractMapRoom() = default;
	virtual ~AbstractMapRoom() = 0;

protected:
	EntityTree tree_;

	virtual void postAddUser(User* user);
	virtual void postRemoveUser(User* user);

	virtual void onReceivedMessage(User* sender, const std::string& message);

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
};

}
#endif // ABSTRACT_MAP_ROOM