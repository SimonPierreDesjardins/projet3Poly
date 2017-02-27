#pragma once

#ifndef __MULTI_USER__SYSTEM_H
#define __MULTI_USER__SYSTEM_H

#include "User.h"
#include <map>

namespace server{
	class MultiUserSystem {
	public:
		void AddUser(User* user);

	protected:

		virtual void TreatUserJoin(User* user) = 0;

		virtual void TreatUserMessage(User* user, std::string& message) = 0;

		virtual void TreatUserDisconnect(User* user) = 0;

		std::map<std::string, User*> _userList;

	private:
		void StartListeningToUser(User* user);
		void StopListeningToUser(User* user);

		void OnUserDisconnected(User* user);

		void OnUserMessageReceived(User* user, std::string& message);

	};
}

#endif // !__MULTI_USER__SYSTEM_H

