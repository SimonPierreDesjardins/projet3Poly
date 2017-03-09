#pragma once
#ifndef __USER_AUTH_LOBBY_H
#define __USER_AUTH_LOBBY_H

#include <unordered_map>
#include <memory>
#include <string>

#include "Networking.h"


#include "User.h"
#include "MultiUserSystem.h"

namespace server 
{

// Wraps a connection to send connection reference on callbacks
class ConnectionWrapper 
{
public:
	ConnectionWrapper(Networking::Connection* connection);

	Networking::Connection* GetConnection();

	__event void OnDisconnect(ConnectionWrapper* wrapper);
	__event void OnMessageSent(ConnectionWrapper* wrapper, const std::string& message);

private:

	void HookToConnection(Networking::Connection* connectionToListenTo);

	void OnData(const std::string& message);

	void OnDisco();

	Networking::Connection* _connection;

};

class UserAuthLobby
{
public:
	UserAuthLobby(Networking::ServerListener* listener, std::vector<MultiUserSystem*> mus);
	virtual ~UserAuthLobby();

	void OnReceivedMessage(ConnectionWrapper* user, const std::string& message);
	void OnUserDisconnect(ConnectionWrapper* user);

	void HookToWrapper(ConnectionWrapper* wrapper);
	void UnhookFromWrapper(ConnectionWrapper* wrapper);

private:

	// ChatRoomManager here

	std::vector<MultiUserSystem*> _userReceivers;
	Networking::ServerListener* _listener;

	// Connection reception treatment
	void HookToListenerEvents(Networking::ServerListener* listener);
	void UnhookFromListenerEvents(Networking::ServerListener* listener);

	void handleConnection(Networking::Connection* handleConnection);

	void handleCreateUsernameRequest(ConnectionWrapper* sender, std::string message);
	void handleLoginRequest(ConnectionWrapper* sender, std::string username);
	//void handleModifiedPropertyRequest();
};

}


#endif