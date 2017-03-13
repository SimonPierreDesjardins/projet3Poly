#include <iostream>

#include "UserAuthLobby.h"
#include "../Database/IdGenerator.h"
#include "TypeSerializerDeserializer.h"
#include "NetworkStandard.h"

namespace server
{

UserAuthLobby::UserAuthLobby(Networking::ServerListener* listener, UserDatabase* userDB, std::vector<MultiUserSystem*> mus)
{
	_userDB = userDB;
	_userReceivers = mus;

	// Build user list from DB
	for (auto userIdPair : _userDB->GetElements()) {
		_users.insert({userIdPair.second->UserName, new User(*userIdPair.second)});
	}

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
	
	// Add new user to DB
	UserInformation* info = new UserInformation;
	std::string username = std::string(message.begin() + Networking::MessageStandard::DATA_START, message.end());
	info->UserName = username;
	_userDB->CreateEntry(info);

	// Add new user to userlist
	_users.insert({ info->UserName, new User(*info) });
}

void UserAuthLobby::handleLoginRequest(ConnectionWrapper* wrapper, std::string message)
{
	std::string username(message.begin() + Networking::MessageStandard::DATA_START, message.end());
	
	std::cout << "Received login request with username: " << username << "." << std::endl;

	//TODO: check if user is already connected
	if (_users.count(username) > 0) {
		
		// Assign connection to its user
		User* authedUser = _users.at(username);
		authedUser->AssignConnection(wrapper->GetConnection());
		
		// wrapper no longer needed since user is wrapping connection
		delete wrapper;

		AddUser(authedUser);

		
	}
	else {
		// user doesn't exist...REBUKE!
		std::string failMessage = "uaf";
		wrapper->GetConnection()->SendData(Networking::MessageStandard::AddMessageLengthHeader(failMessage));
	}
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
	// Confirm authentification.
	std::string authConfirmation = "uas";
	Networking::serialize(user->Info.GetId(), authConfirmation);
	user->ForwardMessage(Networking::MessageStandard::AddMessageLengthHeader(authConfirmation));

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