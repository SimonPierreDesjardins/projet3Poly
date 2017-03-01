#pragma once
#ifndef __USER_AUTH_LOBBY_H
#define __USER_AUTH_LOBBY_H

#include <unordered_map>

#include "Networking.h"
#include "User.h"

namespace server 
{
class UserAuthLobby 
{
public:

	UserAuthLobby(Networking::ServerListener* listener);
	~UserAuthLobby();

private:

	Networking::ServerListener* _listener;

	std::unordered_map<std::string, User*> authentificatedUsers_;

	// Connection reception treatment
	void HookToListenerEvents(Networking::ServerListener* listener);
	void UnhookFromListenerEvents(Networking::ServerListener* listener);
	void TreatConnection(Networking::Connection* connectionToTreat);

	void HookToUser(User* user);
	void UnhookFromUser(User* user);

	void OnReceivedMessage(User* user, std::string& message);
	void OnUserDisconnect(User* user);

};

}


#endif