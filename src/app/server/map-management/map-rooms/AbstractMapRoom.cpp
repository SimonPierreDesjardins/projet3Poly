#include "AbstractMapRoom.h"

namespace server
{

AbstractMapRoom::AbstractMapRoom()
	: MultiUserSession('p')
{
}

void AbstractMapRoom::joinRoom(User* user)
{
	addUser(user);
	user->addObserver(this);
}

void AbstractMapRoom::leaveRoom(User* user)
{
	removeUser(user);
	user->removeObserver(this);
}

void AbstractMapRoom::onReceivedMessage(User* sender, const std::string& message)
{
	assert(message[4] == 'p');

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

