#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
#include "NetworkStandard.h"
#include "NoeudAbstrait.h"

class NoeudAbstrait;

namespace server
{

class EntityProperty {
	// contains reference to the entity and the node's physics component's equivalent property
};

class Entity
{
public:
	using ChildrenContainer = std::unordered_map<uint32_t, Entity*>;

	char entityType_ { 0 };
	uint32_t userId_{ 0 };
	uint32_t entityId_{ 0 };

	Entity(std::shared_ptr<NoeudAbstrait> node);
	~Entity() = default;

	inline void setParent(Entity* parent);
	inline Entity* getParent();
	inline void addChild(Entity* child);
	inline void removeChild(Entity* child);
	inline int getChildCount();

	inline ChildrenContainer::iterator begin();
	inline ChildrenContainer::iterator end();

	inline void updatePhysicProperty(Networking::PropertyType propertyType, const glm::dvec3& propertyValue);
	inline glm::dvec3* getProperty(Networking::PropertyType propertyType);
	inline std::shared_ptr<NoeudAbstrait>& getTreeNode();


private:
	void SetupInitialProperties();
	Entity* parent_{ nullptr };
	std::unordered_map<uint32_t, Entity*> children_;
	std::shared_ptr<NoeudAbstrait> treeNode_ = nullptr;
};

inline void Entity::setParent(Entity* parent)
{
	parent_ = parent;
}

inline Entity* Entity::getParent()
{
	return parent_;
}

inline void Entity::addChild(Entity* child)
{
	child->setParent(this);
	treeNode_->ajouter(child->getTreeNode());
	children_.insert(std::make_pair(child->entityId_, child));
}

inline void Entity::removeChild(Entity* child)
{
	children_.erase(child->entityId_);
}

inline int Entity::getChildCount()
{
	return children_.size();
}

inline Entity::ChildrenContainer::iterator Entity::begin()
{
	return children_.begin();
}

inline Entity::ChildrenContainer::iterator Entity::end()
{
	return children_.end();
}

inline void Entity::updatePhysicProperty(Networking::PropertyType propertyType, const glm::dvec3& propertyValue)
{
	*(getProperty(propertyType)) = propertyValue;
}

inline glm::dvec3* Entity::getProperty(Networking::PropertyType propertyType)
{
	switch (propertyType) {
	case Networking::PropertyType::ABSOLUTE_POSITION:
		return &treeNode_->getPhysicsComponent().absolutePosition;
	case Networking::PropertyType::RELATIVE_POSITION:
		return &treeNode_->getPhysicsComponent().relativePosition;
	case Networking::PropertyType::ANGULAR_VELOCITY:
		return &treeNode_->getPhysicsComponent().angularVelocity;
	case Networking::PropertyType::LINEAR_VELOCITY:
		return &treeNode_->getPhysicsComponent().linearVelocity;
	case Networking::PropertyType::ROTATION:
		return &treeNode_->getPhysicsComponent().rotation;
	case Networking::PropertyType::SCALE:
		return &treeNode_->getPhysicsComponent().scale;
	default:
		return nullptr;
	}
}

inline std::shared_ptr<NoeudAbstrait>& Entity::getTreeNode()
{
	return treeNode_;
}

}

#endif // ENTITY_H