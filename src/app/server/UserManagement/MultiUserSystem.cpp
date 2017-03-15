#include "MultiUserSystem.h"

void server::MultiUserSystem::AddUser(User * user)
{
	_connectedUserList.insert({ user->Info.GetId(), user });
	user->addSystemObserver(this, GetSystemType());
	TreatUserJoin(user);
}

void server::MultiUserSystem::RemoveUser(User* user)
{
	_connectedUserList.erase(user->Info.GetId());
	user->removeSystemObserver(GetSystemType());
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
