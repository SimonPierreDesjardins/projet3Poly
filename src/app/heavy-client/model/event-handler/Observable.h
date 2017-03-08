#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <unordered_map>

#include "LocalEvent.h"

class NoeudAbstrait;

namespace event_handler
{

class Observer;

class Observable
{
public:
	Observable() = default;
	virtual ~Observable() = 0;

	inline void setObserver(Observer* observer);

	void notifyEntityCreated(NoeudAbstrait* noeud);

protected:
	Observer* observer_;
};

void Observable::setObserver(Observer* observer)
{
	assert(observer != nullptr);
	observer_ = observer;
}

}

#endif // OBSERVABLE_H