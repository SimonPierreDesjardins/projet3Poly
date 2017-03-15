#include "Entity.h"

namespace server
{

Entity::Entity()
{
	properties_.insert(std::make_pair(Networking::ABSOLUTE_POSITION, std::move(Eigen::Vector3f(0.0, 0.0, 0.0))));
	properties_.insert(std::make_pair(Networking::RELATIVE_POSITION, std::move(Eigen::Vector3f(0.0, 0.0, 0.0))));
	properties_.insert(std::make_pair(Networking::ROTATION, std::move(Eigen::Vector3f(0.0, 0.0, 0.0))));
	properties_.insert(std::make_pair(Networking::SCALE, std::move(Eigen::Vector3f(1.0, 1.0, 1.0))));
	properties_.insert(std::make_pair(Networking::LINEAR_VELOCITY, std::move(Eigen::Vector3f(0.0, 0.0, 0.0))));
	properties_.insert(std::make_pair(Networking::ANGULAR_VELOCITY, std::move(Eigen::Vector3f(0.0, 0.0, 0.0))));
}

}

	

