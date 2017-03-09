#pragma once
#ifndef __USER_H
#define __USER_H

#include "Networking.h"

#include "Observable.h"

namespace server
{

class UserInformation 
{
public:
	std::string userName_;
	int id_;
	bool isAuthentified_ = false;
};

class User : public Observable
{
public:
	UserInformation info_;

	User() = default;
	User(int id);
	virtual ~User();

	void AssignConnection(Networking::Connection* connectionToTreat);

	inline void AssignInfo(UserInformation info);
	inline void sendMessage(const std::string& message);

private:
	void HookToConnection(Networking::Connection* connectionToListenTo);

	void OnReceivedMessage(const std::string& message);
	void OnConnectionLost();

	Networking::Connection* _connection;
};

inline void User::sendMessage(const std::string& message)
{
	_connection->SendData(message);
}

inline void User::AssignInfo(UserInformation info)
{
	info_ = info;
}

}

#endif