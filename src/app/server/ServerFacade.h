#ifndef SERVER_FACADE_H
#define SERVER_FACADE_H

#include <unordered_map>
#include <iostream>

#include "UserAuthLobby.h"
#include "MapRoomManager.h"

namespace server
{

class ServerFacade
{
public:
	ServerFacade();
	~ServerFacade();

	void initialize();

private:
	Networking::ServerListener* listener_;
	server::UserAuthLobby userLobby_;
	server::MapRoomManager mapRoomManager;
};

}

#endif // SERVER_FACADE_H
