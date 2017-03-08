#include "MultiUserSession.h"

namespace server
{


MultiUserSession::MultiUserSession(char systemType)
	: Observer(systemType)
{
}

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
}

void MultiUserSession::removeUser(User* user)
{
	uint32_t userId = user->info_.id_;
	if (users_.find(userId) != users_.end())
	{
		users_.erase(user->info_.id_);
	}
}

void MultiUserSession::broadcastMessage(const std::string& message)
{
	// TODO: for loop here with send message.
}

}