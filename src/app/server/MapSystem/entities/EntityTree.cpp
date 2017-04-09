#include "EntityTree.h"
#include "ArbreRenduINF2990.h"

namespace server
{

EntityTree::EntityTree()
{
	Entity root;
	root.entityId_ = 0;
	entities_.insert(std::make_pair(0, std::move(root)));
	physicsTree_ = new ArbreRenduINF2990();
	physicsTree_->initialiser(false);
}

EntityTree::~EntityTree()
{
	physicsTree_->vider();
	delete physicsTree_;
}

Entity* EntityTree::createEntity(char entityType, uint32_t parentId)
{
	Entity* newEntityPtr = nullptr;
	EntityContainer::iterator it = entities_.find(parentId);
	if (it != entities_.end())
	{
		// Handle map save here.
		Entity newEntity((physicsTree_->creerNoeud((EntityType)entityType)).get());
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


char server::EntityTree::GetEntityType(const std::string & itemType)
{
	if (itemType == "poteau") {
		return Networking::MessageStandard::ItemTypes::POST_ENTITY;
	}
	if (itemType == "depart") {
		return Networking::MessageStandard::ItemTypes::START_ENTITY;
	}
	if (itemType == "ligneNoire") {
		return Networking::MessageStandard::ItemTypes::BLACK_LINE_ENTITY;
	}
	if (itemType == "segment") {
		return Networking::MessageStandard::ItemTypes::SEGMENT_ENTITY;
	}
	if (itemType == "jonction") {
		return Networking::MessageStandard::ItemTypes::JUNCTION_ENTITY;
	}
	if (itemType == "mur") {
		return Networking::MessageStandard::ItemTypes::WALL_ENTITY;
	}
	if (itemType == "teleporteur") {
		return Networking::MessageStandard::ItemTypes::TELEPORT_ENTITY;
	}
	return -1;
}

std::string server::EntityTree::GetEntityType(char itemType)
{
	//TODO: Implement this
	if (itemType == Networking::MessageStandard::ItemTypes::TABLE_ENTITY) {
		return "table";
	}
	if (itemType == Networking::MessageStandard::ItemTypes::POST_ENTITY) {
		return "poteau";
	}
	if (itemType == Networking::MessageStandard::ItemTypes::START_ENTITY) {
		return "depart";
	}
	if (itemType == Networking::MessageStandard::ItemTypes::BLACK_LINE_ENTITY) {
		return "ligneNoire";
	}
	if (itemType == Networking::MessageStandard::ItemTypes::SEGMENT_ENTITY) {
		return "segment";
	}
	if (itemType == Networking::MessageStandard::ItemTypes::JUNCTION_ENTITY) {
		return "jonction";
	}
	if (itemType == Networking::MessageStandard::ItemTypes::WALL_ENTITY) {
		return "mur";
	}
	if (itemType == Networking::MessageStandard::ItemTypes::TELEPORT_ENTITY) {
		return "teleporteur";
	}
	return "";
}


}

