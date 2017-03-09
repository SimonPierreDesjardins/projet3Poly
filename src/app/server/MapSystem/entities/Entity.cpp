#include "Entity.h"

namespace server
{

Entity::Entity(uint32_t entityId, char entityType, Entity* parent,
	const Eigen::Vector3f& relativePosition, const Eigen::Vector3f& absolutePosition)
		: entityId_(entityId), entityType_(entityType), parent_(parent), 
		  relativePosition_(relativePosition), absolutePosition_(absolutePosition)
{
}

}

