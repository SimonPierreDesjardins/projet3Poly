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

	bool EstClientLourd();
	void EstClientLourd(bool estClientLourd);


private:
	void HookToConnection(Networking::Connection* connectionToListenTo);

	void OnReceivedMessage(const std::string& message);
	void OnConnectionLost();

	Networking::Connection* _connection;

	bool estClientLourd_ = false;

	static void StartMessageReadThread();
	static void StopMessageReadThread();
	static void lookupMessage();

	static std::queue<std::pair<User*, std::string>> _messageQueue;
	static std::mutex _queueMutex;
	static std::thread _messageReaderThread;
	static bool _runThread;
	static int UserCount;
};

inline void User::ForwardMessage(const std::string& message)
{
	assert(message.size() > 0);
	_connection->SendData(message);
}

inline void User::AssignInfo(UserInformation& info)
{
	Info = info;
}

}

#endif