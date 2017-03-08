#include "MultiUserSession.h"

namespace server
{


MultiUserSession::~MultiUserSession()
{
}

void MultiUserSession::onDisconnected(User* disconnectedUser)
{
	users_.erase(disconnectedUser->info_.id_);
}

void MultiUserSession::addUser(User* user)
{
	users_.insert(std::pair<uint32_t, User*>(user->info_.id_, user));
	postAddUser(user);
}

void MultiUserSession::removeUser(User* user)
{
	users_.erase(user->info_.id_);
	postRemoveUser(user);
}

void MultiUserSession::postAddUser(User* user)
{
}

void MultiUserSession::postRemoveUser(User* user)
{
}

void MultiUserSession::broadcastMessage(const std::string& message)
{
	UsersContainer::iterator it;
	for (it = users_.begin(); it != users_.end(); it++)
	{
		it->second->sendMessage(message);
	}
}

void MultiUserSession::broadcastMessageExcluded(User* excludedUser, const std::string& message)
{
	UsersContainer::iterator it;
	for (it = users_.begin(); it != users_.end(); it++)
	{
		if (it->second != excludedUser) 
		{
			it->second->sendMessage(message);
		}
	}
}
}