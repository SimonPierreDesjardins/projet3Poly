#ifndef EDITION_ROOM_H
#define EDITION_ROOM_H

#include "AbstractMapRoom.h"

namespace server
{

class EditionRoom : public AbstractMapRoom
{
public:
	EditionRoom() = default;
	virtual ~EditionRoom() = default;

};

}

#endif // EDITION_ROOM_H