#include <iostream>

#include "UserAuthLobby.h"

namespace server
{

UserAuthLobby::UserAuthLobby(Networking::ServerListener* listener, MapRoomManager* mapRoomManager)
	: MultiUserSession('u'), mapRoomManager_(mapRoomManager)
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
	danglingUsers_.insert(std::pair<uint32_t, User*>(userId, user));
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
	addUser(sender);
	mapRoomManager_->addUser(sender);
	sender->addObserver(mapRoomManager_);
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


void UserAuthLobby::onDisconnected(User* disconnectedUser)
{
	// Find the disconnected user.
	int userId = disconnectedUser->info_.id_;
	DanglingUsersContainer::iterator it = danglingUsers_.find(userId);
	assert(it != danglingUsers_.end());
	
	// If the user is authentificated, remove from authentificated list.
	if (it->second->info_.isAuthentified_)
	{
		UsersContainer::iterator authDisconnectedUser = users_.find(userId);
		users_.erase(authDisconnectedUser);
	}

	// Remove from dangling list and deallocate the user.
	std::cout << "User " << std::to_string(it->second->info_.id_) << " disconnected." << std::endl;
	danglingUsers_.erase(it);
}

}