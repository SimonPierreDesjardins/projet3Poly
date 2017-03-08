#include "AbstractMapRoom.h"
#include <cassert>

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
	assert(message[4] == PHYSIC_MESSAGE || message[4] == MAP_EDITION_MESSAGE);

	switch (message[4])
	{
	case PHYSIC_MESSAGE:
		handlePhysicMessage(sender, message);
		break;

	case MAP_EDITION_MESSAGE:
		handleMapEditionMessage(sender, message);
		break;
	}
}

void AbstractMapRoom::handlePhysicMessage(User* sender, const std::string& message)
{
	assert(message[4] == PHYSIC_MESSAGE);

}

void AbstractMapRoom::handleMapEditionMessage(User* sender, const std::string& message)
{
	assert(message[4] == MAP_EDITION_MESSAGE);
	switch (message[5])
	{
	case 'c':
		handleEntityCreationMessage(sender, message);
		break;

	case 'd':
		handleEntityDeletionMessage(sender, message);
		break;

	case 's':
		handleEntitySelectionMessage(sender, message);
		break;
	}
}

void AbstractMapRoom::handleEntityCreationMessage(User* sender, const std::string& message)
{
}

void AbstractMapRoom::handleEntityDeletionMessage(User* sender, const std::string& message)
{
}

void AbstractMapRoom::handleEntitySelectionMessage(User* sender, const std::string& message)
{
}

void AbstractMapRoom::handleRelativePositionUpdateMessage(User* sender, const std::string& message)
{
}

void AbstractMapRoom::handleAbsolutePositionUpdateMessage(User* sender, const std::string& message)
{
}

void AbstractMapRoom::handleLinearVelocityUpdateMessage(User* sender, const std::string& message)
{
}

void AbstractMapRoom::handleAngularVelocityUpdateMessage(User* sender, const std::string& message)
{
}

void AbstractMapRoom::handleRotationUpdateMessage(User* sender, const std::string& message)
{
}

void AbstractMapRoom::handleScaleUpdateMessage(User* sender, const std::string& message)
{
}

}

