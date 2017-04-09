#ifndef SERVER_MAP_SESSION_H
#define SERVER_MAP_SESSION_H

#include "map-session/MapSession.h"

class NoeudRobot;
class ControleRobot;
class AbstractMapRoom;

namespace server
{

class ServerMapSession : public engine::MapSession
{
public:
	ServerMapSession(User* user, ArbreRenduINF2990* tree, AbstractMapRoom* room) :MapSession((ArbreRendu*)tree) {}

	void ControlUserRobot(NoeudRobot* robot); // takes charge of this MapSession User's robot

	void RelinquishControlOfRobot(); // release control of currently controlled robot and lets client handle updating

	// Inherited via MapSession
	virtual void localEntityCreated(NoeudAbstrait * entity) override;

	virtual void deleteLocalEntity(NoeudAbstrait * entity) override;

	virtual void localEntityPropertyUpdated(NoeudAbstrait * entity, Networking::PropertyType, const glm::vec3 & updatedProperty) override;

	virtual void localEntityPropertiesUpdated(NoeudAbstrait * entity) override;

	virtual void updateSelectionStateLocalEntityAndChildren(NoeudAbstrait * entity, bool isSelected) override;

	virtual uint32_t getThisUserId() override;

private:
	NoeudRobot* robot_;
	ControleRobot* controler_;

};

}

#endif // SIMULATION_ROOM_H
