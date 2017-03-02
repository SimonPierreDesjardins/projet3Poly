#pragma once
#ifndef __USER_H
#define __USER_H

#include "Networking.h"
#include "../Database/UserDatabase.h"

namespace server {

	class User {
	public:
		User(UserInformation& userInfo);

		~User();

		void AssignConnection(Networking::Connection* connectionToTreat);

		void AssignInfo(UserInformation& info);

		void ForwardMessage(std::string& message);

		__event void OnUserDisconnected(User* thisUser);
		__event void OnUserSentMessage(User* thisUser, std::string& message);

		UserInformation& Info;

	private:
		void HookToConnection(Networking::Connection* connectionToListenTo);
		void UnhookFromConnection(Networking::Connection* connectionToListenTo);

		void OnReceivedMessage(std::string& message);
		void OnDisconnect();

		Networking::Connection* _connection;

	};
}


#endif