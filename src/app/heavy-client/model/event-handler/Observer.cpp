#include "Observer.h"

namespace event_handler
{

int Observer::nextObservedId_ = 0;

Observer::~Observer()
{
	id_ = nextObservedId_++;
}

void Observer::onEntitySelected()
{
}

void Observer::onEntityMovedAbsolute(int entityId, const glm::vec3& position)
{
}

void Observer::onEntityMovedRelative(int entityId, const glm::vec3& position)
{
}

void Observer::onEntityResized()
{
}

void Observer::onEntityRotated()
{
}

void Observer::onEntityCreated()
{
}

void Observer::onEntityDeleted()
{
}

}