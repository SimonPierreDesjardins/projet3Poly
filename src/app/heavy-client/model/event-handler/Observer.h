#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

#include "LocalEvent.h"

namespace event_handler
{

class Observer
{
public:
	Observer() = default;
	virtual ~Observer() = 0;

	inline int getId() const;

	virtual void handleLocalEvent(const LocalEvent& localEvent) = 0;

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
