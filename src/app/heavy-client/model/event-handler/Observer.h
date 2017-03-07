#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

#include "glm/glm.hpp"

namespace event_handler
{

class Observer
{
public:
	Observer() = default;
	virtual ~Observer() = 0;

	inline int getId() const;

	virtual void onEntitySelected();
	virtual void onEntityMovedRelative(int entityId, const glm::vec3& position);
	virtual void onEntityMovedAbsolute(int entityId, const glm::vec3& position);
	virtual void onEntityResized();
	virtual void onEntityRotated();

	virtual void onEntityCreated();
	virtual void onEntityDeleted();

private:
	static int nextObservedId_;
	int id_ = 0;
};

inline int Observer::getId() const
{
	return id_;
}

}

#endif // OBSERVABLE_H
