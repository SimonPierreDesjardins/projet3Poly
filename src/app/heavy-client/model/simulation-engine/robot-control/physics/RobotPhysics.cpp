#include "RobotPhysics.h"

#include "map-session/MapSession.h"
#include "ArbreRendu.h"
#include "NoeudRobot.h"
#include "NoeudPoteau.h"
#include "EnginSon.h"
#include "SimulationEngine.h"

#define PI 3.14159265

void RobotPhysics::init(NoeudRobot* robot, engine::SimulationEngine* engine, engine::MapSession* mapSession)
{
	collisionDetection_ = VisiteurDetectionRobot(robot);
	robot_ = robot;
	tree_ = engine->getEntityTree();
	engine_ = engine;
	vue_ = engine->getView();
	physics_ = robot->getPhysicsComponent();
	controleurLumiere_ = engine->getLightController();
	mapSession_ = mapSession;
	isInitialized_ = true;
	profil_ = engine_->getProfil();
}

void RobotPhysics::applyPhysicsEffects(float dt)
{
	if (!isInitialized_) return;

    robot_->mettreAJourPosition(dt);

	physics_ = robot_->getPhysicsComponent();
	mapSession_->localEntityPropertiesUpdated(robot_);

	/*
	mapSession_->localEntityPropertyUpdated(robot_, Networking::ABSOLUTE_POSITION, glm::vec3(physics_.absolutePosition));
	mapSession_->localEntityPropertyUpdated(robot_, Networking::RELATIVE_POSITION, glm::vec3(physics_.relativePosition));
	mapSession_->localEntityPropertyUpdated(robot_, Networking::ROTATION, glm::vec3(physics_.rotation));
	mapSession_->localEntityPropertyUpdated(robot_, Networking::LINEAR_VELOCITY, glm::vec3(physics_.linearVelocity));
	mapSession_->localEntityPropertyUpdated(robot_, Networking::ANGULAR_VELOCITY, glm::vec3(physics_.angularVelocity));
	*/

	tree_->accepterVisiteur(&collisionDetection_);

	vue_ = engine_->getView();

	robot_->suivreCamera(vue_);

	robot_->assignerControleurLumiere(controleurLumiere_);
	controleurLumiere_->animer(robot_->getPhysicsComponent().relativePosition, dt);
	for (int i = 0; i < 3; i++)
	{
		profil_->obtenirCapteursDistance()->at(i).mettreAJour(physics_.absolutePosition, physics_.rotation.z);
	}

	

}


