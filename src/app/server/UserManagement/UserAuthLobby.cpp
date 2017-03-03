#include <iostream>

#include "UserAuthLobby.h"
#include "../Database/IdGenerator.h"


server::UserAuthLobby::UserAuthLobby(Networking::ServerListener* listener, MultiUserSystem& mus):_userReceiver(mus)
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
	//Normally, listen to this connection and wait for it to identify itself

	// For first release, just confirm connection and forward to the map system

	UserInformation* information = new UserInformation();
	information->UserName = IdGenerator::GenerateId();

	User* connectedUser = new User(*information);

	_userReceiver.AddUser(connectedUser);

	//User* user = new User();
	//HookToWrapper(new ConnectionWrapper(connection));
	//user->AssignConnection(connection);
}

void server::UserAuthLobby::HookToWrapper(ConnectionWrapper * wrapper)
{
	__hook(&ConnectionWrapper::OnDisconnect, wrapper, &UserAuthLobby::OnUserDisconnect, this);
	__hook(&ConnectionWrapper::OnMessageSent, wrapper, &UserAuthLobby::OnReceivedMessage, this);
}

void server::UserAuthLobby::UnhookFromWrapper(ConnectionWrapper * wrapper)
{
	__unhook(&ConnectionWrapper::OnDisconnect, wrapper, &UserAuthLobby::OnUserDisconnect, this);
	__unhook(&ConnectionWrapper::OnMessageSent, wrapper, &UserAuthLobby::OnReceivedMessage, this);
}

void server::UserAuthLobby::OnReceivedMessage(ConnectionWrapper * wrapper, std::string& message)
{
	// Attempt to authenticate user with message

	// Auto authenticate for now
}

void server::UserAuthLobby::OnUserDisconnect(ConnectionWrapper * wrapper)
{
	// unhook from events and dispose of user
	//UnhookFromWrapper(wrapper);
	//delete user;
}

server::ConnectionWrapper::ConnectionWrapper(Networking::Connection * connection)
{
	_connection = connection;
	ListenToConnection(connection);
}

Networking::Connection * server::ConnectionWrapper::GetConnection()
{
	return _connection;
}

void server::ConnectionWrapper::ListenToConnection(Networking::Connection * connection)
{
	__hook(&Networking::Connection::OnReceivedData, connection, &ConnectionWrapper::OnData);
	__hook(&Networking::Connection::OnConnectionLost, connection, &ConnectionWrapper::OnDisco);
}

void server::ConnectionWrapper::StopListeningToConnection(Networking::Connection * connection)
{
	__unhook(&Networking::Connection::OnReceivedData, connection, &ConnectionWrapper::OnData);
	__unhook(&Networking::Connection::OnConnectionLost, connection, &ConnectionWrapper::OnDisco);
}

void server::ConnectionWrapper::OnData(std::string & message)
{
	__raise OnMessageSent(this, message);
}

void server::ConnectionWrapper::OnDisco()
{
	__raise OnDisconnect(this);
}
