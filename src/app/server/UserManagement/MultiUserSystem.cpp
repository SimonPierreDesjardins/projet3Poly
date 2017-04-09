#include "MultiUserSystem.h"

void server::MultiUserSystem::AddUser(User * user)
{
	_connectedUserList.insert({ user->Info.GetId(), user });
	user->addSystemObserver(this, GetSystemType());
	TreatUserJoin(user);
}

bool server::MultiUserSystem::RemoveUser(User* user)
{
	uint32_t nErased = (uint32_t)_connectedUserList.erase(user->Info.GetId());
	bool userFound = nErased != 0;
	if (userFound)
	{
		user->removeSystemObserver(GetSystemType());
		TreatUserDisconnect(user);
	}
	return userFound;
}

bool server::MultiUserSystem::containsUser(User* user)
{
	return (_connectedUserList.find(user->Info.GetId()) != _connectedUserList.end());
}

void server::MultiUserSystem::onUserDisconnected(User * user)
{
	_connectedUserList.erase(user->Info.GetId());
	TreatUserDisconnect(user);
}

void server::MultiUserSystem::onUserMessageReceived(User * user, const std::string & message)
{
	TreatUserMessage(user, message);
}

void server::MultiUserSystem::broadcastMessage(const std::string & message)
{
	for (auto it = _connectedUserList.begin(); it != _connectedUserList.end(); it++)
	{
		it->second->ForwardMessage(message);
	}
}

void server::MultiUserSystem::broadcastMessage(User * excludedUser, const std::string & message)
{
	for (auto it = _connectedUserList.begin(); it != _connectedUserList.end(); it++)
	{
		if (it->second != excludedUser)
		{
			it->second->ForwardMessage(message);
		}
	}
}
