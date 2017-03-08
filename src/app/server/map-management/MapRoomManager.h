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

	virtual void onReceivedMessage(const std::string& message);

	void createRoom(RoomType roomType);
	void removeRoom(uint32_t roomid);

private:
	int nextRoomId_ = 0;
	std::unordered_map<uint32_t, std::unique_ptr<AbstractMapRoom>> rooms_;
};

}

#endif // MAP_ROOM_MANAGER_H