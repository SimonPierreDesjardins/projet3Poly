#ifndef MULTI_USER_SESSION_H
#define MULTI_USER_SESSION_H

#include <unordered_map>

#include "User.h"
#include "Observer.h"

namespace server
{

class MultiUserSession : public Observer
{
public:
	MultiUserSession() = default;
	virtual ~MultiUserSession() = 0;

	inline int getSessionId() const;

	virtual void onReceivedMessage(User* sender, const std::string& message) = 0;
	virtual void onDisconnected(User* diconnectedUser);

	void addUser(User* user);
	void removeUser(User* user);

	virtual void broadcastMessage(const std::string& message);

protected:
	virtual void postAddUser(User* user);
	virtual void postRemoveUser(User* user);

	typedef std::unordered_map<uint32_t, User*> UsersContainer;
	UsersContainer users_;
};

}

#endif // MULTI_USER_SESSION_H
