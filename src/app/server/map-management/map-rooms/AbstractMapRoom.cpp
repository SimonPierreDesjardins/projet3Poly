#include "AbstractMapRoom.h"

namespace server
{

AbstractMapRoom::~AbstractMapRoom()
{
}


void AbstractMapRoom::postAddUser(User* user)
{
	// Subscribe to physic and map edition messages.
	user->addSystemObserver(this, PHYSIC_MESSAGE);
	user->addSystemObserver(this, MAP_EDITION_MESSAGE);
}

void AbstractMapRoom::postRemoveUser(User* user)
{
	// Unsub from physic and map edition messages.
	user->removeSystemObserver(PHYSIC_MESSAGE);
	user->removeSystemObserver(MAP_EDITION_MESSAGE);
}

void AbstractMapRoom::onReceivedMessage(User* sender, const std::string& message)
{
	assert(message[4] == PHYSIC_MESSAGE);

	switch (message[5])
	{
	case 'r':
		break;

	case 'v':
		break;

	case 'p':
		break;

	case 'w':
		break;

	case 's':
		break;
	}
}

}

