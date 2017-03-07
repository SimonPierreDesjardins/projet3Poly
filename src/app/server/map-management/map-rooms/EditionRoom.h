#ifndef EDITION_ROOM_H
#define EDITION_ROOM_H

#include "AbstractMapRoom.h"
#include "Observer.h"

#include "MultiUserSession.h"

namespace server
{

class MapRoomManager : public MultiUserSession
{

public:
	MapRoomManager();
	~MapRoomManager();

private:
	std::vector<AbstractMapRoom> rooms_;
};

}

#endif // MAP_ROOM_MANAGER_H
