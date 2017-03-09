#ifndef ENTITY_H
#define ENTITY_H

#include <Eigen/Dense>
#include <unordered_map>

namespace server
{

class Entity
{
public:
	Eigen::Vector3f relativePosition_;
	Eigen::Vector3f absolutePosition_;
	Eigen::Vector3f rotation_;
	Eigen::Vector3f scale_;

	char entityType_ { -1 };
	int32_t selectingUser_{ -1 };
	int32_t entityId_{ -1 };

	Entity() = default;
	Entity(uint32_t entityId, char entityType, Entity* parent,
		const Eigen::Vector3f& relativePosition, const Eigen::Vector3f& absolutePosition);
	~Entity() = default;

	inline void setParent(Entity* parent);
	inline Entity* getParent();
	inline void addChild(Entity* child);
	inline void removeChild(Entity* child);

private:

	Entity* parent_{ nullptr };
	std::unordered_map<uint32_t, Entity*> children_;
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

}

#endif // ENTITY_H