#include <iostream>

#include "UserAuthLobby.h"


server::UserAuthLobby::UserAuthLobby(Networking::ServerListener* listener)
{
	HookToListenerEvents(listener);
}

server::UserAuthLobby::~UserAuthLobby()
{
	UnhookFromListenerEvents(_listener);
	Networking::NetworkObjects::Dispose(_listener);
}

void server::UserAuthLobby::HookToListenerEvents(Networking::ServerListener * listener)
{
	_listener = listener;
	__hook(&Networking::ServerListener::OnOtherConnected, listener, &UserAuthLobby::TreatConnection);
}

void server::UserAuthLobby::UnhookFromListenerEvents(Networking::ServerListener * listener)
{
	__unhook(&Networking::ServerListener::OnOtherConnected, listener, &UserAuthLobby::TreatConnection);
	_listener = NULL;
}

void server::UserAuthLobby::TreatConnection(Networking::Connection * connection)
{
	// create a user, hook to its events and add this connection to it

	User* user = new User();
	HookToUser(user);
	user->AssignConnection(connection);
}

void server::UserAuthLobby::HookToUser(User * user)
{
	__hook(&User::OnUserDisconnected, user, &UserAuthLobby::OnUserDisconnect, this);
	__hook(&User::OnUserSentMessage, user, &UserAuthLobby::OnReceivedMessage, this);
}

void server::UserAuthLobby::UnhookFromUser(User * user)
{
	__unhook(&User::OnUserDisconnected, user, &UserAuthLobby::OnUserDisconnect, this);
	__unhook(&User::OnUserSentMessage, user, &UserAuthLobby::OnReceivedMessage, this);
}

void server::UserAuthLobby::OnReceivedMessage(User * user, std::string& message)
{
}

void server::UserAuthLobby::OnUserDisconnect(User * user)
{
	// unhook from events and dispose of user
	//UnhookFromUser(user);
	//delete user;
}
