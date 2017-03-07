#pragma once
#ifndef __USER_AUTH_LOBBY_H
#define __USER_AUTH_LOBBY_H

#include <unordered_map>
#include <memory>
#include <string>

#include "Networking.h"

#include "Observer.h"

#include "User.h"

namespace server 
{

class UserAuthLobby : public Observer
{
public:
	UserAuthLobby(Networking::ServerListener* listener);
	virtual ~UserAuthLobby();

	virtual void onReceivedMessage(const std::string& message);
	virtual void onDisconnected(int userId);

private:

	Networking::ServerListener* _listener;
	int nextUserId_ = 0;

	typedef std::unordered_map<std::string, User*> AuthUsersContainer;
	typedef std::unordered_map<int, std::unique_ptr<User>> UsersContainer;

	AuthUsersContainer authentificatedUsers_;
	UsersContainer users_;

	// Connection reception treatment
	void HookToListenerEvents(Networking::ServerListener* listener);
	void UnhookFromListenerEvents(Networking::ServerListener* listener);

	void handleConnection(Networking::Connection* handleConnection);
};

}


#endif