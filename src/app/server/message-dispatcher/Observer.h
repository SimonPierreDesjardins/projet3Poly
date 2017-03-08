#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

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
public:
	Observer() = default;
	virtual ~Observer() = 0;

	virtual void onReceivedMessage(User* user, const std::string& message) = 0;
	virtual void onDisconnected(User* user) = 0;
};

inline Observer::~Observer()
{
}

}

#endif // OBSERVABLE_H
