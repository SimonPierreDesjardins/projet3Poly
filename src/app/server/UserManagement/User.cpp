#include "User.h"

void server::User::AssignConnection(Networking::Connection * connectionToTreat)
{
	HookToConnection(connectionToTreat);
}

server::User::User(UserInformation & userInfo):Info(userInfo)
{
}

server::User::~User()
{
	UnhookFromConnection(_connection);
	Networking::NetworkObjects::Dispose(_connection);
}

void server::User::HookToConnection(Networking::Connection * connectionToListenTo)
{
	__hook(&Networking::Connection::OnReceivedData, connectionToListenTo, &User::OnReceivedMessage);
	__hook(&Networking::Connection::OnConnectionLost, connectionToListenTo, &User::OnDisconnect);
}

void server::User::UnhookFromConnection(Networking::Connection * connectionToDeafenFrom)
{
	__unhook(&Networking::Connection::OnReceivedData, connectionToDeafenFrom, &User::OnReceivedMessage);
	__unhook(&Networking::Connection::OnConnectionLost, connectionToDeafenFrom, &User::OnDisconnect);
}

void server::User::OnReceivedMessage(std::string& message)
{
	OnUserSentMessage(this, message);
}

void server::User::OnDisconnect()
{
	UnhookFromConnection(_connection);
	Networking::NetworkObjects::Dispose(_connection);
	OnUserDisconnected(this);
}
