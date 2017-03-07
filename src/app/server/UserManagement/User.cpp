#include "User.h"
#include <iostream>

namespace server
{

User::User(int id)
{
	info_.id_ = id;
}

User::~User()
{
	UnhookFromConnection(_connection);
	Networking::NetworkObjects::Dispose(_connection);
}

void User::AssignConnection(Networking::Connection * connectionToTreat)
{
	_connection = connectionToTreat;
	HookToConnection(connectionToTreat);
}

void User::HookToConnection(Networking::Connection * connectionToListenTo)
{
	__hook(&Networking::Connection::OnReceivedData, connectionToListenTo, &User::OnReceivedMessage);
	__hook(&Networking::Connection::OnConnectionLost, connectionToListenTo, &User::OnDisconnect);
}

void User::UnhookFromConnection(Networking::Connection * connectionToDeafenFrom)
{
	__unhook(&Networking::Connection::OnReceivedData, connectionToDeafenFrom, &User::OnReceivedMessage);
	__unhook(&Networking::Connection::OnConnectionLost, connectionToDeafenFrom, &User::OnDisconnect);
}

void User::OnReceivedMessage(std::string& message)
{
	std::cout << message << std::endl;
	//dispatchReceivedMessage(message);
}

void User::OnDisconnect()
{
	//notifyDisconnected(info_.id_);
}

}