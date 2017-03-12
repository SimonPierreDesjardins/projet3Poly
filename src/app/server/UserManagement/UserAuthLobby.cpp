#include <iostream>

#include "UserAuthLobby.h"
#include "../Database/IdGenerator.h"
#include "NetworkStandard.h"

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
	UserInformation info;
	info.UserName = std::string(message.begin() + Networking::MessageStandard::DATA_START, message.end());
	_users.insert({ info.UserName, User(info) });
}

void UserAuthLobby::handleLoginRequest(ConnectionWrapper* wrapper, std::string message)
{
	// TODO: Check if the username exists and is not used.
	std::cout << "Received login request with username: " << message.substr(6, message.size() - 6) << "." << std::endl;

	UserInformation* information = new UserInformation();
	information->UserName = IdGenerator::GenerateId();

	std::string username(message.begin() + Networking::MessageStandard::DATA_START, message.end());

	if (_users.count(username) > 0) {
		// friendly user gets VIP treatment
		User* authedUser = &_users.at(username);
		authedUser->AssignConnection(wrapper->GetConnection());
		//TODO: Change the to string to an actual byte conversion
		authedUser->ForwardMessage(Networking::MessageStandard::AddMessageLengthHeader("uas" + std::to_string(authedUser->Info.GetId())));
		AddUser(authedUser);
	}
	else {
		// user doesn't exist... REBUKE
	}

	User* user = new User(*information);
	Networking::Connection* connection = wrapper->GetConnection();
	user->AssignConnection(wrapper->GetConnection());

	delete wrapper;
}

void UserAuthLobby::OnReceivedMessage(ConnectionWrapper * wrapper, const std::string& message)
{
	// We should only receive messages for the user system
	assert(message.size() > 6 && message[Networking::MessageStandard::SYSTEM] == 'u');

	switch (message[Networking::MessageStandard::COMMAND])
	{
	case 'c':
		handleCreateUsernameRequest(wrapper, message);
		break;

	case 'l':
		handleLoginRequest(wrapper, message);
		break;

	}
	// Attempt to authenticate user with message

	// Auto authenticate for now
}

void UserAuthLobby::OnDisconnection(ConnectionWrapper * wrapper)
{
	// Handle unauthentified connection disconnected here, wrapper deleted for now.
	delete wrapper;
}

char UserAuthLobby::GetSystemType()
{
	return 'u';
}

void UserAuthLobby::TreatUserJoin(User * user)
{
	// This method is called when the authlobby has a user login
	for each(auto userReceiver in _userReceivers) {
		userReceiver->AddUser(user);
	}
}

void UserAuthLobby::TreatUserMessage(User * user, const std::string & message)
{

	// treat user information change requests
	switch (message[Networking::MessageStandard::COMMAND]) {
		case 'a':
			break;
		case 'm':
			break;
	}
}

void UserAuthLobby::TreatUserDisconnect(User * user)
{
	// Make associated user in list disconnected
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
	_authLoby->OnDisconnection(this);
}

void ConnectionWrapper::OnMessageSent(const std::string& message)
{
	_authLoby->OnReceivedMessage(this, message);
}

}