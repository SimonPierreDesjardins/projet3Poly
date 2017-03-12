#include "User.h"
#include <iostream>

namespace server
{

server::User::User(UserInformation & userInfo)
	: Info(userInfo)
{
	_connection == NULL;
}

User::~User()
{
	Networking::NetworkObjects::Dispose(_connection);
}

void User::AssignConnection(Networking::Connection * connectionToTreat)
{
	_connection = connectionToTreat;
	HookToConnection(connectionToTreat);
}

void User::HookToConnection(Networking::Connection * connectionToListenTo)
{
	_connection->hookOnReceivedMessage(&User::OnReceivedMessage, this);
	_connection->hookOnConnectionLost(&User::OnConnectionLost, this);
}

void User::OnReceivedMessage(const std::string& message)
{
	dispatchReceivedMessage(this, message);
}

void User::OnConnectionLost()
{
	notifyDisconnected(this);
	delete this;
}

}