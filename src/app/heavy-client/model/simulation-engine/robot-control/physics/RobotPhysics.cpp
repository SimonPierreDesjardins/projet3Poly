#include "RobotPhysics.h"

#include "MapSession.h"
#include "ArbreRendu.h"
#include "NoeudRobot.h"
#include "NoeudPoteau.h"
#include "EnginSon.h"

void RobotPhysics::init(NoeudRobot* robot, ArbreRendu* tree, client_network::MapSession* mapSession)
{
	collisionDetection_ = VisiteurDetectionRobot(robot);
	robot_ = robot;
	tree_ = tree;
	mapSession_ = mapSession;
	isInitialized_ = true;
}

void RobotPhysics::applyPhysicsEffects(float dt)
{
	if (!isInitialized_) return;

	tree_->accepterVisiteur(&collisionDetection_);
    robot_->mettreAJourPosition(dt);
	//robot_->effectuerCollision(dt);

	PhysicsComponent& physics = robot_->getPhysicsComponent();

	mapSession_->localEntityPropertyUpdated(robot_, Networking::ABSOLUTE_POSITION, glm::vec3(physics.absolutePosition));
	mapSession_->localEntityPropertyUpdated(robot_, Networking::RELATIVE_POSITION, glm::vec3(physics.relativePosition));
	mapSession_->localEntityPropertyUpdated(robot_, Networking::ROTATION, glm::vec3(physics.rotation));
	mapSession_->localEntityPropertyUpdated(robot_, Networking::LINEAR_VELOCITY, glm::vec3(physics.linearVelocity));
	mapSession_->localEntityPropertyUpdated(robot_, Networking::ANGULAR_VELOCITY, glm::vec3(physics.angularVelocity));
}


