#include "Entity.h"

namespace server
{


Entity::Entity(std::shared_ptr<NoeudAbstrait> node)
{
	treeNode_ = node;
	entityType_ = node->getType();
}

void Entity::SetupInitialProperties() {
}

}

	

