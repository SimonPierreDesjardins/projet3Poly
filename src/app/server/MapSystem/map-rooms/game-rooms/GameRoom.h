#ifndef GAME_ROOM_H
#define GAME_ROOM_H

#include "AbstractMapRoom.h"

namespace server
{

class GameRoom : public AbstractMapRoom
{
public:
	GameRoom(MapInfo* mapInfo, MapFileEntry* mapFile);
	virtual ~GameRoom() = default;
};

}

#endif // GAME_ROOM_H
