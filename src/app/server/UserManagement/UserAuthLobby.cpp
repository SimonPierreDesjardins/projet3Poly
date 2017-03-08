#include <iostream>

#include "UserAuthLobby.h"

namespace server
{

UserAuthLobby::UserAuthLobby(Networking::ServerListener* listener)
	: MultiUserSession('u')
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
	uint32_t userId = nextUserId_++;
	User* user = new User(userId);
	user->addObserver(this);
	user->AssignConnection(connection);
	ownedUsers_.insert(std::pair<uint32_t, User*>(userId, user));
}

void UserAuthLobby::onReceivedMessage(const std::string& message)
{
	// TODO: Handle user request disconnection here.
	// TODO: Handle user authentification here.
	// TODO: Add map from user id to username to confirm authentification.
}


void UserAuthLobby::onDisconnected(uint32_t userId)
{
	// Find the disconnected user.
	OwnedUsersContainer::iterator disconnectedUser = ownedUsers_.find(userId);
	assert(disconnectedUser != ownedUsers_.end());
	
	// If the user is authentificated, remove from authentificated list.
	if (disconnectedUser->second->info_.isAuthentified_)
	{
		UsersContainer::iterator authDisconnectedUser = users_.find(userId);
		users_.erase(authDisconnectedUser);
	}

	// Remove from owned list and deallocate the user.
	std::cout << "User " << std::to_string(disconnectedUser->second->info_.id_) << " disconnected.";
	ownedUsers_.erase(disconnectedUser);
}

}