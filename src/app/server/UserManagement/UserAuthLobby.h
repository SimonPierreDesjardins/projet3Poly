#pragma once
#ifndef __USER_AUTH_LOBBY_H
#define __USER_AUTH_LOBBY_H

#include <unordered_map>
#include <memory>
#include <string>

#include "Networking.h"

#include "MultiUserSession.h"

#include "User.h"

namespace server 
{

class UserAuthLobby : public MultiUserSession
{
public:
	UserAuthLobby(Networking::ServerListener* listener);
	virtual ~UserAuthLobby();

	virtual void onReceivedMessage(const std::string& message);
	virtual void onDisconnected(uint32_t userId);

private:

	Networking::ServerListener* _listener;
	uint32_t nextUserId_ = 0;

	typedef std::unordered_map<uint32_t, User*> OwnedUsersContainer;
	OwnedUsersContainer ownedUsers_;

	// Connection reception treatment
	void HookToListenerEvents(Networking::ServerListener* listener);
	void UnhookFromListenerEvents(Networking::ServerListener* listener);

	void handleConnection(Networking::Connection* handleConnection);
};

}


#endif