#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

#include "Observable.h"

namespace server
{

class User;

enum SystemType
{
	USER_MESSAGE = 'u',
	CHAT_MESSAGE = 'c',
	MAP_MESSAGE = 'm',
	PHYSIC_MESSAGE = 'p',
	MAP_EDITION_MESSAGE = 'e'
};

class Observer
{

friend class Observable;

public:
	Observer() = default;
	virtual ~Observer() = 0;

	virtual void onUserMessageReceived(User* user, const std::string& message) = 0;
	virtual void onUserDisconnected(User* user) = 0;
};

inline Observer::~Observer()
{
}

}

#endif // OBSERVABLE_H
