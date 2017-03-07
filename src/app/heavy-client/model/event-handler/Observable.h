#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <unordered_map>

#include "LocalEvent.h"

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

	void notify(const LocalEvent& localEvent);

private:
	std::unordered_map<int, Observer*> observers_;
};

}

#endif // OBSERVABLE_H