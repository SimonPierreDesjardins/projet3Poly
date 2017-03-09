#pragma once
#ifndef __USER_H
#define __USER_H

#include "Networking.h"
#include "../Database/UserDatabase.h"

#include "Observable.h"

namespace server
{

class User : public Observable
{
public:
	UserInformation& Info;

	User(UserInformation& userInfo);
	virtual ~User();

	void AssignConnection(Networking::Connection* connectionToTreat);
	inline void AssignInfo(UserInformation& info);

	void ForwardMessage(const std::string& message);

private:
	void HookToConnection(Networking::Connection* connectionToListenTo);

	void OnReceivedMessage(const std::string& message);
	void OnConnectionLost();

	Networking::Connection* _connection;
};

inline void User::ForwardMessage(const std::string& message)
{
	_connection->SendData(message);
}

inline void User::AssignInfo(UserInformation& info)
{
	Info = info;
}

}

#endif