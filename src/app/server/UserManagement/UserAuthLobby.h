#pragma once
#ifndef __USER_AUTH_LOBBY_H
#define __USER_AUTH_LOBBY_H

#include <unordered_map>
#include <memory>
#include <string>

#include "Networking.h"

#include "MultiUserSession.h"

#include "User.h"
#include "MapRoomManager.h"

namespace server 
{

class UserAuthLobby : public MultiUserSession
{
public:
	UserAuthLobby(Networking::ServerListener* listener, MapRoomManager* mapRoomManager);
	virtual ~UserAuthLobby();

	virtual void onReceivedMessage(User* sender, const std::string& message);
	virtual void onDisconnected(User* disconnectedUser);

private:

	Networking::ServerListener* _listener;

	MapRoomManager* mapRoomManager_;
	// ChatRoomManager here

	typedef std::unordered_map<uint32_t, User*> DanglingUsersContainer;
	DanglingUsersContainer danglingUsers_;

	uint32_t nextUserId_ = 0;

	// Connection reception treatment
	void HookToListenerEvents(Networking::ServerListener* listener);
	void UnhookFromListenerEvents(Networking::ServerListener* listener);

	void handleConnection(Networking::Connection* handleConnection);

	void handleCreateUsernameRequest(User* sender, std::string message);
	void handleLoginRequest(User* sender, std::string username);
	//void handleModifiedPropertyRequest();
};

}


#endif