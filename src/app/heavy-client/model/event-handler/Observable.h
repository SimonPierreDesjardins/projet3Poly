#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <unordered_map>

#include "glm/glm.hpp"

namespace event_handler
{

class Observer;

class Observable
{
public:
	Observable() = default;
	virtual ~Observable() = 0;

	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);

	void notifyEntityMovedRelative(int entityId, const glm::vec3& position);
	void notifyEntityMovedAbsolute(int entityId, const glm::vec3& position);
	void notifyEntityResized(int entityId, const glm::vec3& position);
	void notifyEntityRotated(int entityId, const glm::vec3& position);
	void notifyEntitySelected();

	void notifyEntityCreated();
	void notifyEntityDeleted();

private:
	std::unordered_map<int, Observer*> observers_;
};

}

#endif // OBSERVABLE_H