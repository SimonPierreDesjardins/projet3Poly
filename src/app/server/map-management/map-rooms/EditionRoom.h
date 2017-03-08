#ifndef EDITION_ROOM_H
#define EDITION_ROOM_H

#include "AbstractMapRoom.h"
#include "Observer.h"

#include "MultiUserSession.h"

namespace server
{

class EditionRoom : public AbstractMapRoom
{
public:
	EditionRoom() = default;
	virtual ~EditionRoom() = default;

};

}

#endif // MAP_ROOM_MANAGER_H
