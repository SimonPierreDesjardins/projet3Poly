#include <iostream>

#include "UserAuthLobby.h"

namespace server
{

UserAuthLobby::UserAuthLobby(Networking::ServerListener* listener, MapRoomManager* mapRoomManager)
	: mapRoomManager_(mapRoomManager)
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

void UserAuthLobby::postAddUser(User* user)
{
	user->addSystemObserver(this, USER_MESSAGE);
}

void UserAuthLobby::postRemoveUser(User* user)
{
	// If the user is authentificated, remove from authentificated list.
	if (user->info_.isAuthentified_)
	{
		authUsers_.erase(user->info_.id_);
	}
}

void UserAuthLobby::handleConnection(Networking::Connection * connection)
{
	uint32_t userId = nextUserId_++;
	User* user = new User(userId);
	user->AssignConnection(connection);
	addUser(user);
}

void UserAuthLobby::handleCreateUsernameRequest(User* sender, std::string message)
{
	// TODO: Check if the new username is available and add to database.
	std::cout << "Received profile creation request with username: " << message.substr(6, message.size() - 6) << "." << std::endl;
}

void UserAuthLobby::handleLoginRequest(User* sender, std::string message)
{
	// TODO: Check if the username exists and is not used.
	std::cout << "Received login request with username: " << message.substr(6, message.size() - 6) << "." << std::endl;
	authUsers_.insert(std::make_pair(sender->info_.id_, sender));
	mapRoomManager_->addUser(sender);
	// chatRoomManager_->addUser(sender);
}

void UserAuthLobby::onReceivedMessage(User* sender, const std::string& message)
{
	// We should only receive messages for the user system
	assert(message.size() > 6 && message[4] == 'u');

	switch (message[5])
	{
	case 'c':
		handleCreateUsernameRequest(sender, message);
		break;

	case 'l':
		handleLoginRequest(sender, message);
		break;

	case 'a':
		break;
	case 'm':
		break;
	}
}

void UserAuthLobby::onUserDisconnected(User* disconnectedUser)
{
	// Remove the user from dangling users and authentificated users list if he's there.
	uint32_t userId = disconnectedUser->info_.id_;
	users_.erase(userId);
	authUsers_.erase(userId);
}

}