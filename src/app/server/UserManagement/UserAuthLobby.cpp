#include <iostream>

#include "UserAuthLobby.h"
#include "../Database/IdGenerator.h"

namespace server
{

server::UserAuthLobby::UserAuthLobby(Networking::ServerListener* listener, std::vector<MultiUserSystem*> mus)
{
	_userReceivers = mus;
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
	ConnectionWrapper* wrapper = new ConnectionWrapper(connection);
	HookToWrapper(wrapper);
}

void UserAuthLobby::handleCreateUsernameRequest(ConnectionWrapper* wrapper, std::string message)
{
	// TODO: Check if the new username is available and add to database.
	std::cout << "Received profile creation request with username: " << message.substr(6, message.size() - 6) << "." << std::endl;
}

void UserAuthLobby::handleLoginRequest(ConnectionWrapper* wrapper, std::string message)
{
	// TODO: Check if the username exists and is not used.
	std::cout << "Received login request with username: " << message.substr(6, message.size() - 6) << "." << std::endl;

	UserInformation* information = new UserInformation();
	information->UserName = IdGenerator::GenerateId();

	User* user = new User(*information);
	Networking::Connection* connection = wrapper->GetConnection();
	user->AssignConnection(wrapper->GetConnection());

	UnhookFromWrapper(wrapper);
	delete wrapper;
	

	for each(auto userReceiver in _userReceivers) {
		userReceiver->AddUser(user);
	}
}

void server::UserAuthLobby::HookToWrapper(ConnectionWrapper * wrapper)
{
	__hook(&ConnectionWrapper::OnDisconnect, wrapper, &UserAuthLobby::OnUserDisconnect);
	__hook(&ConnectionWrapper::OnMessageSent, wrapper, &UserAuthLobby::OnReceivedMessage);
}

void server::UserAuthLobby::UnhookFromWrapper(ConnectionWrapper * wrapper)
{
	__unhook(&ConnectionWrapper::OnDisconnect, wrapper, &UserAuthLobby::OnUserDisconnect);
	__unhook(&ConnectionWrapper::OnMessageSent, wrapper, &UserAuthLobby::OnReceivedMessage);
}

void server::UserAuthLobby::OnReceivedMessage(ConnectionWrapper * wrapper, const std::string& message)
{
	// We should only receive messages for the user system
	assert(message.size() > 6 && message[4] == 'u');

	switch (message[5])
	{
	case 'c':
		handleCreateUsernameRequest(wrapper, message);
		break;

	case 'l':
		handleLoginRequest(wrapper, message);
		break;

	case 'a':
		break;
	case 'm':
		break;
	}
	// Attempt to authenticate user with message

	// Auto authenticate for now
}

void server::UserAuthLobby::OnUserDisconnect(ConnectionWrapper * wrapper)
{
	// unhook from events and dispose of user
	UnhookFromWrapper(wrapper);
	//delete user;
}

server::ConnectionWrapper::ConnectionWrapper(Networking::Connection * connection)
{
	_connection = connection;
	HookToConnection(connection);
}

Networking::Connection * server::ConnectionWrapper::GetConnection()
{
	return _connection;
}

void ConnectionWrapper::HookToConnection(Networking::Connection * connectionToListenTo)
{
	connectionToListenTo->hookOnConnectionLost(&ConnectionWrapper::OnDisco, this);
	connectionToListenTo->hookOnReceivedMessage(&ConnectionWrapper::OnData, this);
}

void server::ConnectionWrapper::OnData(const std::string & message)
{
	__raise OnMessageSent(this, message);
}

void server::ConnectionWrapper::OnDisco()
{
	__raise OnDisconnect(this);
}

}