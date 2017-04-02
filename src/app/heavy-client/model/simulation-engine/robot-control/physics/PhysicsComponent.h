///////////////////////////////////////////////////////////////////////////////
/// @file PhysicsComponent.h
/// @author Olivier St-amour
/// @date 2017-03-28
/// @version 3.2
///
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "glm/glm.hpp"

///////////////////////////////////////////////////////////////////////////
/// @class PhysicsComponent
/// @brief Classe qui représente les propriétés physiques d'un objet.
/// @author Olivier St-Amour
/// @date 2017-03-28
///////////////////////////////////////////////////////////////////////////
class PhysicsComponent
{
public:
	PhysicsComponent() = default;
	~PhysicsComponent() = default;

	glm::dvec3 absolutePosition;
	glm::dvec3 relativePosition;
	glm::dvec3 scale;
	glm::dvec3 rotation;
	glm::dvec3 linearVelocity;
	glm::dvec3 angularVelocity;

	// Objects with negative mass will behave like they have infinite mass:
	// They can't move and will apply an elastic collision.
	// Note: The curvature of space-time is not simulated.
	float mass{ -1.0 };
};

#endif // PHYSICS_COMPONENT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////