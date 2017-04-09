#include "AbstractMapRoom.h"
#include "ServerMapSession.h"
#include "ControleRobot.h"

namespace server {

	void ServerMapSession::ControlUserRobot(NoeudRobot * robot)
	{
		// create a controller for the robot with map session for physics updates
		controler_ = new ControleRobot(robot);
	}

	void ServerMapSession::RelinquishControlOfRobot()
	{
		// TODO: cleanly shut down controler
		delete controler_;
	}

	void ServerMapSession::localEntityCreated(NoeudAbstrait * entity)
	{
		// TODO: Call this when a user's robot is created by this session (iOS robot creation message?)
	}

	void ServerMapSession::deleteLocalEntity(NoeudAbstrait * entity)
	{
		// TODO: Call this when a user's robot is destroyed
	}

	void ServerMapSession::localEntityPropertyUpdated(NoeudAbstrait * entity, Networking::PropertyType, const glm::vec3 & updatedProperty)
	{
		// broadcast to users when robot entity is updated
	}

	void ServerMapSession::localEntityPropertiesUpdated(NoeudAbstrait * entity)
	{
		// broadcast to users when robot properties are updated.
	}

	void ServerMapSession::updateSelectionStateLocalEntityAndChildren(NoeudAbstrait * entity, bool isSelected)
	{
		// No need to implement this for now
	}

	// gets the user associated to this session (and robot)
	uint32_t ServerMapSession::getThisUserId()
	{
		return uint32_t();
	}
}