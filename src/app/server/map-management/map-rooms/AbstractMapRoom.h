#ifndef ABSTRACT_MAP_ROOM_H
#define ABSTRACT_MAP_ROOM_H

#include "MultiUserSession.h"

namespace server
{

class AbstractMapRoom : public MultiUserSession
{
public:	
	AbstractMapRoom();
	virtual ~AbstractMapRoom() = 0;

	virtual void onReceivedMessage(User* sender, const std::string& message);

	void joinRoom(User* user);
	void leaveRoom(User* user);

};

inline AbstractMapRoom::~AbstractMapRoom()
{
}

}
#endif // ABSTRACT_MAP_ROOM