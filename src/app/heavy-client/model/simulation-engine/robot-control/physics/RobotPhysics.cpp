#include "RobotPhysics.h"

#include "ArbreRendu.h"
#include "NoeudRobot.h"
#include "NoeudPoteau.h"
#include "EnginSon.h"

void RobotPhysics::init(NoeudRobot* robot, ArbreRendu* tree)
{
	collisionDetection_ = VisiteurDetectionRobot(robot);
	robot_ = robot;
	tree_ = tree;
	isInitialized_ = true;
}

void RobotPhysics::applyPhysicsEffects(float dt)
{
	if (!isInitialized_) return;

    robot_->mettreAJourPosition(dt);
	tree_->accepterVisiteur(&collisionDetection_);
	robot_->effectuerCollision(dt);
}


