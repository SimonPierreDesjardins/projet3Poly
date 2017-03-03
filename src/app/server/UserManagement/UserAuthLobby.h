#pragma once
#ifndef __USER_AUTH_LOBBY_H
#define __USER_AUTH_LOBBY_H

#include <unordered_map>

#include "Networking.h"
#include "User.h"
#include "MultiUserSystem.h"


namespace server {
	// Wraps a connection to send connection reference on callbacks
	class ConnectionWrapper {
	public:
		ConnectionWrapper(Networking::Connection* connection);

		Networking::Connection* GetConnection();

		__event void OnDisconnect(ConnectionWrapper* wrapper);

		__event void OnMessageSent(ConnectionWrapper* wrapper, std::string& message);

	private:

		void ListenToConnection(Networking::Connection* connection);
		void StopListeningToConnection(Networking::Connection* connection);

		void OnData(std::string& message);

		void OnDisco();

		Networking::Connection* _connection;

	};

	class UserAuthLobby {
	public:
		///<summary>Creates a connection authentifier that listens on listener and forwards authenticated users to a multi-user system </summary>
		UserAuthLobby(Networking::ServerListener* listener, MultiUserSystem& mus);

		~UserAuthLobby();

	private:

		// Connection reception treatment
		void HookToListenerEvents(Networking::ServerListener* listener);
		void UnhookFromListenerEvents(Networking::ServerListener* listener);
		void TreatConnection(Networking::Connection* connectionToTreat);

		void HookToWrapper(ConnectionWrapper* wrapper);
		void UnhookFromWrapper(ConnectionWrapper* wrapper);

		void OnReceivedMessage(ConnectionWrapper* user, std::string& message);
		void OnUserDisconnect(ConnectionWrapper* user);

		Networking::ServerListener* _listener;

		// Contains the system authenticated users should be sent to
		MultiUserSystem& _userReceiver;
	};

}


#endif