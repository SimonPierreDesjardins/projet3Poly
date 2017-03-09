#ifndef ENTITY_TREE_H
#define ENTITY_TREE_H

#include <unordered_map>
#include "Entity.h"

namespace server
{

class EntityTree
{
public:

	EntityTree();
	~EntityTree();

	// Create a new entity with initial position, parentId and entity Type.
	uint32_t createEntity(char entityType, uint32_t parentId, 
		const Eigen::Vector3f& initialRelativePosition, const Eigen::Vector3f& initialAbsolutePosition);

	bool deleteEntity(uint32_t entityToDelete);

	Entity* findEntity(uint32_t entityId);

private:
	using EntityContainer = std::unordered_map<uint32_t, Entity>;
	EntityContainer entities_;
	uint32_t nextEntityId_{ 1 };
};


}

#endif // ENTITY_TREE_H