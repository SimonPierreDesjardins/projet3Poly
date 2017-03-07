#ifndef MAP_ROOM_MANAGER_H
#define MAP_ROOM_MANAGER_H

#include "AbstractMapRoom.h"
#include "Observer.h"

#include "MultiUserSession.h"

namespace server
{

class MapRoomManager : public Observer
{

public:
	MapRoomManager();
	virtual ~MapRoomManager();

private:
	std::vector<AbstractMapRoom> rooms_;
};

}

#endif // MAP_ROOM_MANAGER_H