#ifndef ENTITY_H
#define ENTITY_H

#include <Eigen/Dense>
#include <unordered_map>
#include "NetworkStandard.h"

namespace server
{

class Entity
{
public:
	using ChildrenContainer = std::unordered_map<uint32_t, Entity*>;

	char entityType_ { 0 };
	uint32_t userId_{ 0 };
	uint32_t entityId_{ 0 };

	Entity();
	~Entity() = default;

	inline void setParent(Entity* parent);
	inline Entity* getParent();
	inline void addChild(Entity* child);
	inline void removeChild(Entity* child);
	inline int getChildCount();

	inline ChildrenContainer::iterator begin();
	inline ChildrenContainer::iterator end();

	inline void updatePhysicProperty(Networking::PropertyType propertyType, const Eigen::Vector3f& propertyValue);
	inline Eigen::Vector3f* getProperty(Networking::PropertyType propertyType);


private:
	Entity* parent_{ nullptr };
	std::unordered_map<uint32_t, Entity*> children_;
	std::unordered_map<Networking::PropertyType, Eigen::Vector3f> properties_;
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

inline void Entity::updatePhysicProperty(Networking::PropertyType propertyType, const Eigen::Vector3f& propertyValue)
{
	auto it = properties_.find(propertyType);
	if (it != properties_.end())
	{
		it->second = propertyValue;
	}
}

inline Eigen::Vector3f* Entity::getProperty(Networking::PropertyType propertyType)
{
	Eigen::Vector3f* property = nullptr;
	auto it = properties_.find(propertyType);
	if (it != properties_.end())
	{
		property = &it->second;
	}
	return property;
}

}

#endif // ENTITY_H