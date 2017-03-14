#ifndef ENTITY_H
#define ENTITY_H

#include <Eigen/Dense>
#include <unordered_map>

namespace server
{

enum PropertyType
{
	RELATIVE_POSITION = 'p',
	ABSOLUTE_POSITION = 'a',
	ROTATION = 'r',
	SCALE = 's',
	LINEAR_VELOCITY = 'v',
	ANGULAR_VELOCITY = 'w'
};

class Entity
{
public:
	Eigen::Vector3f relativePosition_{ 0.0, 0.0, 0.0 };
	Eigen::Vector3f absolutePosition_{ 0.0, 0.0, 0.0 };
	Eigen::Vector3f rotation_{ 0.0, 0.0, 0.0 };
	Eigen::Vector3f scale_{ 1.0, 1.0, 1.0 };

	char entityType_ { 0 };
	uint32_t userId_{ 0 };
	uint32_t entityId_{ 0 };

	Entity();
	~Entity() = default;

	inline void setParent(Entity* parent);
	inline Entity* getParent();
	inline void addChild(Entity* child);
	inline void removeChild(Entity* child);
	inline void updatePhysicProperty(PropertyType propertyType, const Eigen::Vector3f& propertyValue);
	inline Eigen::Vector3f* getProperty(PropertyType propertyType);

private:
	Entity* parent_{ nullptr };
	std::unordered_map<uint32_t, Entity*> children_;
	std::unordered_map<PropertyType, Eigen::Vector3f> properties_;
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

inline void Entity::updatePhysicProperty(PropertyType propertyType, const Eigen::Vector3f& propertyValue)
{
	auto it = properties_.find(propertyType);
	if (it != properties_.end())
	{
		it->second = propertyValue;
	}
}

inline Eigen::Vector3f* Entity::getProperty(PropertyType propertyType)
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