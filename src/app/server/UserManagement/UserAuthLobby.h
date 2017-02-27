#pragma once
#ifndef __USER_AUTH_LOBBY_H
#define __USER_AUTH_LOBBY_H

#include "Networking.h"
#include "User.h"

namespace server {
	class UserAuthLobby {
	public:
		UserAuthLobby(Networking::ServerListener* listener);

		~UserAuthLobby();


	private:

		// Connection reception treatment
		void HookToListenerEvents(Networking::ServerListener* listener);
		void UnhookFromListenerEvents(Networking::ServerListener* listener);
		void TreatConnection(Networking::Connection* connectionToTreat);

		void HookToUser(User* user);
		void UnhookFromUser(User* user);

		void OnReceivedMessage(User* user, std::string& message);
		void OnUserDisconnect(User* user);

		Networking::ServerListener* _listener;
	};

}


#endif