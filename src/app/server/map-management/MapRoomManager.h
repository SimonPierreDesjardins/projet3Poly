#ifndef MAP_ROOM_MANAGER_H
#define MAP_ROOM_MANAGER_H

#include <memory>
#include <unordered_map>

#include "AbstractMapRoom.h"
#include "Observer.h"

#include "MultiUserSession.h"

namespace server
{

enum RoomType
{
	EDITION_ROOM,
	SIMULATION_ROOM
};

class MapRoomManager : public MultiUserSession
{

public:
	MapRoomManager();
	virtual ~MapRoomManager();

	virtual void onReceivedMessage(User* sender, const std::string& message);
	virtual void onDisconnected(User* disconnectedUser);

	void createRoom(RoomType roomType);
	void removeRoom(uint32_t roomId);

private:

	void handleJoinMapSessionRequest(User* sender, const std::string& message);
	void handleLeaveMapSessionRequest(User* sender, const std::string& message);

	int nextRoomId_ = 0;
	std::unordered_map<uint32_t, std::unique_ptr<AbstractMapRoom>> rooms_;

	// Rooms mapped by user id. This is used for fast removal of users from rooms.
	std::unordered_map<uint32_t, AbstractMapRoom*> roomsByUserId_;
};

}

#endif // MAP_ROOM_MANAGER_H