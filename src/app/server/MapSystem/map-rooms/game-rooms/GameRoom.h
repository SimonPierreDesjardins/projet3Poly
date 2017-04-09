#ifndef GAME_ROOM_H
#define GAME_ROOM_H

#include <chrono>

#include "AbstractMapRoom.h"

namespace server
{

class GameRoom : public AbstractMapRoom
{
public:
	GameRoom(MapInfo* mapInfo, MapFileEntry* mapFile);
	virtual ~GameRoom() = default;

protected:

	std::thread gameState_;

};

}

#endif // GAME_ROOM_H
