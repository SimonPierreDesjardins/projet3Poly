#ifndef ABSTRACT_MAP_ROOM_H
#define ABSTRACT_MAP_ROOM_H

#include "MultiUserSession.h"

namespace server
{

class AbstractMapRoom : public MultiUserSession
{
public:	
	AbstractMapRoom() = default;
	virtual ~AbstractMapRoom() = 0;

	virtual void onReceivedMessage(User* sender, const std::string& message);

protected:

	virtual void postAddUser(User* user);
	virtual void postRemoveUser(User* user);
};

}
#endif // ABSTRACT_MAP_ROOM