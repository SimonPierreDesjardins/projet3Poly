#include "Entity.h"

namespace server
{

Entity::Entity()
{
	properties_.insert(std::make_pair(ABSOLUTE_POSITION, std::move(Eigen::Vector3f())));
	properties_.insert(std::make_pair(RELATIVE_POSITION, std::move(Eigen::Vector3f())));
	properties_.insert(std::make_pair(ROTATION, std::move(Eigen::Vector3f())));
	properties_.insert(std::make_pair(SCALE, std::move(Eigen::Vector3f())));
	properties_.insert(std::make_pair(LINEAR_VELOCITY, std::move(Eigen::Vector3f())));
	properties_.insert(std::make_pair(ANGULAR_VELOCITY, std::move(Eigen::Vector3f())));
}

}

	

