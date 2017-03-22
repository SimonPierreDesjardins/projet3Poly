#ifndef EDITION_ROOM_H
#define EDITION_ROOM_H

#include "AbstractMapRoom.h"

namespace server
{

class EditionRoom : public AbstractMapRoom
{
public:
	EditionRoom(MapInfo* mapInfo);
	virtual ~EditionRoom() = default;

};

}

#endif // EDITION_ROOM_H
