#ifndef RACING_ROOM_H
#define RACING_ROOM_H

#include "GameRoom.h"

namespace server
{

class RacingRoom : public GameRoom
{
public:
	RacingRoom(MapInfo* mapInfo, MapFileEntry* mapFile);
	virtual ~RacingRoom() = default;
};

}

#endif // RACING_ROOM_H
