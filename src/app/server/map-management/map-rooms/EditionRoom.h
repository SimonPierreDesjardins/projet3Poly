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
	
	void handleEntityCreationMessage(User* sender, const std::string& message);

};

}

#endif // EDITION_ROOM_H
