///////////////////////////////////////////////////////////////////////////////
/// @file RobotPhysics.h
/// @author Olivier St-amour
/// @date 2017-03-28
/// @version 3.2
///
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef ROBOT_PHYSICS_H
#define ROBOT_PHYSICS_H

#include "VisiteurDetectionRobot.h"

///////////////////////////////////////////////////////////////////////////
/// @class RobotPhysics
/// @brief Classe qui s'occupe de simuler la physique d'un robot
/// @author Olivier St-Amour
/// @date 2017-03-28
///////////////////////////////////////////////////////////////////////////
class RobotPhysics
{
public:
	RobotPhysics() = default;
	~RobotPhysics() = default;

	void init(NoeudRobot* robot, ArbreRendu* arbre);

    // Mise à jour des attributs du robot.
	void applyPhysicsEffects(float dt);


private:
	bool isInitialized_ = false;

	NoeudRobot* robot_ = nullptr;
	ArbreRendu* tree_ = nullptr;

	VisiteurDetectionRobot collisionDetection_;

	void updateRobotState(float dt);


};

#endif ROBOT_PHYSICS_H

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
