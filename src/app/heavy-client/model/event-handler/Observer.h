#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

#include "NoeudAbstrait.h"

namespace event_handler
{

class Observer
{
public:
	Observer() = default;
	virtual ~Observer() = 0;

	inline int getId() const;

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
