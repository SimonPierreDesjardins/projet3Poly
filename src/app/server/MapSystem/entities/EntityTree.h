#ifndef ENTITY_TREE_H
#define ENTITY_TREE_H

#include <mutex>
#include <unordered_map>
#include "Entity.h"

class ArbreRenduINF2990;

namespace server
{

class EntityTree
{
public:
	using EntityContainer = std::unordered_map<uint32_t, Entity>;

	EntityTree();
	~EntityTree();


	// Create a new entity with initial position, parentId and entity Type.
	Entity* createEntity(char entityType, uint32_t parentId);
	Entity* createEntity(const std::string& entityType, uint32_t parentId);

	bool deleteEntity(uint32_t entityToDelete);
	Entity* findEntity(uint32_t entityId);

	inline ArbreRenduINF2990* getPhysicsTree();

	inline EntityContainer::iterator begin();
	inline EntityContainer::iterator end();

	inline void lock();
	inline void unlock();

private:

	std::mutex treeLock_;

	EntityContainer entities_;
	uint32_t nextEntityId_{ 1 };
	std::shared_ptr<ArbreRenduINF2990> physicsTree_;
};

inline EntityTree::EntityContainer::iterator EntityTree::begin()
{
	return entities_.begin();
}

inline EntityTree::EntityContainer::iterator EntityTree::end()
{
	return entities_.end();
}

inline void EntityTree::lock()
{
	treeLock_.lock();
}

inline void EntityTree::unlock()
{
	treeLock_.unlock();
}

}

#endif // ENTITY_TREE_H