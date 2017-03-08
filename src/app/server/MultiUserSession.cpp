#include "MultiUserSession.h"

namespace server
{


MultiUserSession::~MultiUserSession()
{
}

void MultiUserSession::onDisconnected(User* disconnectedUser)
{
	removeUser(disconnectedUser);
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
	// TODO: for loop here with send message.
}

}