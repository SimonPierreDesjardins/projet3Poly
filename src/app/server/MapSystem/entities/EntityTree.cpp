#include "EntityTree.h"
#include "ArbreRenduINF2990.h"

namespace server
{

EntityTree::EntityTree()
{
	Entity root;
	root.entityId_ = 0;
	entities_.insert(std::make_pair(0, std::move(root)));
	ArbreRenduINF2990 arbre;
}

EntityTree::~EntityTree()
{
}

Entity* EntityTree::createEntity(char entityType, uint32_t parentId)
{
	Entity* newEntityPtr = nullptr;
	EntityContainer::iterator it = entities_.find(parentId);
	if (it != entities_.end())
	{
		// Handle map save here.
		Entity newEntity;
		newEntity.entityType_ = entityType;
		newEntity.setParent(&it->second);
		newEntity.entityId_ = nextEntityId_++;
		auto result = entities_.insert(std::make_pair(newEntity.entityId_, std::move(newEntity)));
		// Return reference.
		if (result.second)
		{
			newEntityPtr = &result.first->second;
		}
		it->second.addChild(newEntityPtr);
	}
	return newEntityPtr;
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

