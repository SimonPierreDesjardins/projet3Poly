#include "EntityTree.h"

namespace server
{

EntityTree::EntityTree()
{
	Entity root;
	root.entityId_ = 0;
	entities_.insert(std::make_pair(0, std::move(root)));
}

EntityTree::~EntityTree()
{
}

uint32_t EntityTree::createEntity(char entityType, uint32_t parentId,
	const Eigen::Vector3f& initialRelativePosition, const Eigen::Vector3f& initialAbsolutePosition)
{
	uint32_t newEntityId = 0;
	EntityContainer::iterator it = entities_.find(parentId);
	if (it != entities_.end())
	{
		// Handle map save here.
		Entity* parent = &it->second;
		newEntityId = nextEntityId_++;
		Entity newEntity(newEntityId, entityType, parent, initialRelativePosition, initialAbsolutePosition);
		entities_.insert(std::make_pair(newEntityId, std::move(newEntity)));
	}
	return newEntityId;
}

bool EntityTree::deleteEntity(uint32_t entityToDelete)
{
	bool success = false;
	EntityContainer::iterator it = entities_.find(entityToDelete);
	if(it != entities_.end())
	{
		Entity* parent = it->second.getParent();
		parent->removeChild(&it->second);
		entities_.erase(it);
		success = true;
	}
	return success;
}

Entity* EntityTree::findEntity(uint32_t entityId)
{
	Entity* foundEntity = nullptr;
	EntityContainer::iterator it = entities_.find(entityId);
	if (it != entities_.end())
	{
		foundEntity = &it->second;
	}
	return foundEntity;
}

}

