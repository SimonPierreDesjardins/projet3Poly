#include "EntityTree.h"
#include "ArbreRenduINF2990.h"

namespace server
{

EntityTree::EntityTree()
{
	physicsTree_ = std::make_shared<ArbreRenduINF2990>();
	physicsTree_->initialiser(false);
	Entity root(physicsTree_);
	root.entityId_ = 0;
	entities_.insert(std::make_pair(0, std::move(root)));

}

EntityTree::~EntityTree()
{
	physicsTree_->vider();
}

Entity* EntityTree::createEntity(char entityType, uint32_t parentId)
{
	treeLock_.lock();
	Entity* newEntityPtr = nullptr;
	EntityContainer::iterator it = entities_.find(parentId);
	if (it != entities_.end())
	{
		// Handle map save here.
		Entity newEntity((physicsTree_->creerNoeud((EntityType)entityType)));
		newEntity.entityType_ = entityType;
		newEntity.entityId_ = nextEntityId_++;
		auto result = entities_.insert(std::make_pair(newEntity.entityId_, std::move(newEntity)));
		// Return reference.
		if (result.second)
		{
			newEntityPtr = &result.first->second;
		}
		it->second.addChild(newEntityPtr);
	}
	treeLock_.unlock();
	return newEntityPtr;
}

bool EntityTree::deleteEntity(uint32_t entityToDelete)
{
	treeLock_.lock();
	bool success = false;
	EntityContainer::iterator it = entities_.find(entityToDelete);
	if(it != entities_.end())
	{
		Entity* parent = it->second.getParent();
		parent->removeChild(&it->second);
		entities_.erase(it);
		success = true;
	}
	treeLock_.unlock();
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

inline ArbreRenduINF2990 * EntityTree::getPhysicsTree()
{
	return physicsTree_.get();
}


char server::EntityTree::GetEntityType(const std::string & itemType)
{
	if (itemType == "table") {
		return EntityType::TABLE_ENTITY;
	}
	if (itemType == "poteau") {
		return EntityType::POST_ENTITY;
	}
	if (itemType == "depart") {
		return EntityType::START_ENTITY;
	}
	if (itemType == "ligneNoire") {
		return EntityType::BLACK_LINE_ENTITY;
	}
	if (itemType == "segment") {
		return EntityType::SEGMENT_ENTITY;
	}
	if (itemType == "jonction") {
		return EntityType::JUNCTION_ENTITY;
	}
	if (itemType == "mur") {
		return EntityType::WALL_ENTITY;
	}
	if (itemType == "teleporteur") {
		return EntityType::TELEPORT_ENTITY;
	}
	if (itemType == "paireteleporteurs") {
		return EntityType::PAIRTELEPORT_ENTITY;
	}
}

}

