#pragma once

#ifndef __MULTI_USER__SYSTEM_H
#define __MULTI_USER__SYSTEM_H

#include "User.h"
#include <unordered_map>
#include "Observer.h"

namespace server
{

class MultiUserSystem : public Observer
{
public:
	using UserContainer = std::unordered_map<unsigned int, User*>;

	void AddUser(User* user);
	bool RemoveUser(User* user);

	inline size_t GetNumberOfUsers() const;

	void broadcastMessage(const std::string& message);
	void broadcastMessage(User* excludedUser, const std::string& message);

	inline UserContainer::iterator userListBegin();
	inline UserContainer::iterator userListEnd();


protected:

	virtual char GetSystemType() = 0;
	virtual void TreatUserJoin(User* user) = 0;
	virtual void TreatUserMessage(User* user, const std::string& message) = 0;
	virtual void TreatUserDisconnect(User* user) = 0;

	UserContainer _connectedUserList;

private:
	virtual void onUserDisconnected(User* user);
	virtual void onUserMessageReceived(User* user, const std::string& message);

};

inline size_t MultiUserSystem::GetNumberOfUsers() const
{
	return _connectedUserList.size();
}

inline MultiUserSystem::UserContainer::iterator MultiUserSystem::userListBegin()
{
	return _connectedUserList.begin();
}

inline MultiUserSystem::UserContainer::iterator MultiUserSystem::userListEnd()
{
	return _connectedUserList.end();
}

}

#endif // !__MULTI_USER__SYSTEM_H

