#include <iostream>

#include "UserAuthLobby.h"

namespace server
{

UserAuthLobby::UserAuthLobby(Networking::ServerListener* listener)
{
	HookToListenerEvents(listener);
}

UserAuthLobby::~UserAuthLobby()
{
	UnhookFromListenerEvents(_listener);
	Networking::NetworkObjects::Dispose(_listener);
}


void UserAuthLobby::HookToListenerEvents(Networking::ServerListener * listener)
{
	_listener = listener;
	__hook(&Networking::ServerListener::OnOtherConnected, listener, &UserAuthLobby::handleConnection);
}

void UserAuthLobby::UnhookFromListenerEvents(Networking::ServerListener * listener)
{
	__unhook(&Networking::ServerListener::OnOtherConnected, listener, &UserAuthLobby::handleConnection);
	_listener = nullptr;
}


void UserAuthLobby::handleConnection(Networking::Connection * connection)
{
	int userId = nextUserId_++;
	std::unique_ptr<User> user = std::make_unique<User>(userId);
	user->addObserver(this);
	user->AssignConnection(connection);
	users_.insert(std::pair<int, std::unique_ptr<User>>(userId, std::move(user)));
}

void UserAuthLobby::onReceivedMessage(const std::string& message)
{
	// TODO: Handle user request disconnection here.
	// TODO: Handle user authentification here.
}


void UserAuthLobby::onDisconnected(int userId)
{
	UsersContainer::iterator disconnectedUser = users_.find(userId);
	assert(disconnectedUser != users_.end());
	
	// If the user is authetified, remove from authentified list.
	if (disconnectedUser->second->info_.isAuthentified_)
	{
		AuthUsersContainer::iterator authDisconnectedUser = authentificatedUsers_.find(disconnectedUser->second->info_.userName_);
		authentificatedUsers_.erase(authDisconnectedUser);
	}
	users_.erase(disconnectedUser);
}

}