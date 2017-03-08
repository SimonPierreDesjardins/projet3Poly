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
	User() = default;
	User(int id);
	virtual ~User();

	void AssignConnection(Networking::Connection* connectionToTreat);

	void AssignInfo(UserInformation info) {
		info_ = info;
	}

	UserInformation info_;

private:
	void HookToConnection(Networking::Connection* connectionToListenTo);

	void OnReceivedMessage(const std::string& message);
	void OnConnectionLost();

	Networking::Connection* _connection;

};

}


#endif