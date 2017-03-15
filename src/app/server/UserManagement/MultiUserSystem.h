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
	void AddUser(User* user);
	void RemoveUser(User* user);
	inline size_t GetNumberOfUsers() const;

	void broadcastMessage(const std::string& message);
	void broadcastMessage(User* excludedUser, const std::string& message);

protected:

	virtual char GetSystemType() = 0;
	virtual void TreatUserJoin(User* user) = 0;
	virtual void TreatUserMessage(User* user, const std::string& message) = 0;
	virtual void TreatUserDisconnect(User* user) = 0;

	std::unordered_map<unsigned int, User*> _connectedUserList;

private:
	virtual void onUserDisconnected(User* user);
	virtual void onUserMessageReceived(User* user, const std::string& message);

};

inline size_t MultiUserSystem::GetNumberOfUsers() const
{
	return _connectedUserList.size();
}


}

#endif // !__MULTI_USER__SYSTEM_H

