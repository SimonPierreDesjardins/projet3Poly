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
	delete _connection;
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
	std::cout << message << std::endl;
	dispatchReceivedMessage(message);
}

void User::OnConnectionLost()
{
	notifyDisconnected(info_.id_);
	delete this;
}

}