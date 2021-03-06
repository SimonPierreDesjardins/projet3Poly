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

class ConnectionWrapper;

class UserAuthLobby : private MultiUserSystem
{
public:
	UserAuthLobby(Networking::ServerListener* listener, UserDatabase* userDB, std::vector<MultiUserSystem*> mus);
	virtual ~UserAuthLobby();

	void OnReceivedMessage(ConnectionWrapper* user, const std::string& message);
	void OnDisconnection(ConnectionWrapper* user);
protected:
	virtual char GetSystemType();
	virtual void TreatUserJoin(User* user);
	virtual void TreatUserMessage(User* user, const std::string& message);
	virtual void TreatUserDisconnect(User* user);

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

	// created from all user infos in DB
	std::unordered_map<std::string, User*> _users;
	// link to db for user creation messages
	UserDatabase* _userDB;

};

// Wraps a connection to send connection reference on callbacks
class ConnectionWrapper 
{
public:
	ConnectionWrapper(Networking::Connection* connection, UserAuthLobby* authLobby);

	Networking::Connection* GetConnection();

	void OnDisconnect();
	void OnMessageSent(const std::string& message);

private:

	void HookToConnection(Networking::Connection* connectionToListenTo);

	Networking::Connection* _connection;
	UserAuthLobby* _authLoby;
};

}


#endif