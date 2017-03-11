#include <iostream>

#include "UserAuthLobby.h"
#include "../Database/IdGenerator.h"
#include "TypeSerializerDeserializer.h"

namespace server
{

UserAuthLobby::UserAuthLobby(Networking::ServerListener* listener, std::vector<MultiUserSystem*> mus)
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
	ConnectionWrapper* wrapper = new ConnectionWrapper(connection, this);
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

	delete wrapper;

	for each(auto userReceiver in _userReceivers) {
		userReceiver->AddUser(user);
	}

	// Confirm authentification.
	std::string authConfirmation;
	Networking::serialize((uint32_t)(23), authConfirmation);
	authConfirmation.append("uas");
	authConfirmation.append(user->Info.GetId());
	user->ForwardMessage(authConfirmation);
}

void UserAuthLobby::OnReceivedMessage(ConnectionWrapper * wrapper, const std::string& message)
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

void UserAuthLobby::OnUserDisconnect(ConnectionWrapper * wrapper)
{
	// Handle unauthentified user disconnected here, wrapper deleted for now.
	delete wrapper;
}

ConnectionWrapper::ConnectionWrapper(Networking::Connection * connection, 
	UserAuthLobby* lobby)
{
	_connection = connection;
	_authLoby = lobby;
	HookToConnection(connection);
}

Networking::Connection * ConnectionWrapper::GetConnection()
{
	return _connection;
}

void ConnectionWrapper::HookToConnection(Networking::Connection * connectionToListenTo)
{
	connectionToListenTo->hookOnConnectionLost(&ConnectionWrapper::OnDisconnect, this);
	connectionToListenTo->hookOnReceivedMessage(&ConnectionWrapper::OnMessageSent, this);
}

void ConnectionWrapper::OnDisconnect()
{
	_authLoby->OnUserDisconnect(this);
}

void ConnectionWrapper::OnMessageSent(const std::string& message)
{
	_authLoby->OnReceivedMessage(this, message);
}

}