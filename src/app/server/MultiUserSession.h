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
	MultiUserSession(char systemType);
	virtual ~MultiUserSession() = 0;
	inline int getSessionId() const;

	void addUser(User* user);

protected:

	typedef std::unordered_map<uint32_t, User*> UsersContainer;
	UsersContainer users_;

private:
	MultiUserSession();
};

}

#endif // MULTI_USER_SESSION_H
