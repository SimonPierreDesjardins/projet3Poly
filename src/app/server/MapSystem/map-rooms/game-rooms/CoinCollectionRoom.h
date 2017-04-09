#ifndef COIN_COLLECTION_ROOM_H
#define COIN_COLLECTION_ROOM_H

#include "GameRoom.h"

namespace server {

class CoinCollectionRoom : public GameRoom
{
public:
	CoinCollectionRoom(MapInfo* mapInfo, MapFileEntry* mapFile);
	virtual ~CoinCollectionRoom() = default;

};

}

#endif // COIN_COLLECTION_ROOM_H
