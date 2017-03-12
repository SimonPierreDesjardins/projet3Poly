#include "AbstractMapRoom.h"
#include "TypeSerializerDeserializer.h"
#include <cassert>

namespace server
{

AbstractMapRoom::AbstractMapRoom()
{
	Entity* table = tree_.createEntity(0, 0);
	Entity* start = tree_.createEntity(1, table->entityId_);
}

AbstractMapRoom::~AbstractMapRoom()
{
}

char AbstractMapRoom::GetSystemType()
{
	return systemType_;
}

void AbstractMapRoom::TreatUserJoin(User* user)
{
	// Subscribe to physic and map edition messages.
	user->addSystemObserver(this, MAP_EDITION_MESSAGE);

	// Send all the entities except the first one (which is the root).
	for (auto it = ++tree_.begin(); it != tree_.end(); ++it)
	{
		std::string message;
		buildEntityCreationMessage(&it->second, message);
		user->ForwardMessage(message);
	}
}

void AbstractMapRoom::TreatUserDisconnect(User* user)
{
	// Unsub from physic and map edition messages.
	user->removeSystemObserver(MAP_EDITION_MESSAGE);
}

void AbstractMapRoom::TreatUserMessage(User* sender, const std::string& message)
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

void AbstractMapRoom::buildEntityCreationMessage(Entity* entity, std::string& message)
{
	message.clear();
	Networking::serialize((uint32_t)(79), message);
	message.append("ec");
	message.append(1, entity->entityType_);
	Networking::serialize(entity->getParent()->entityId_, message);
	Networking::serialize(entity->absolutePosition_, message);
	Networking::serialize(entity->relativePosition_, message);
	Networking::serialize(entity->rotation_, message);
	Networking::serialize(entity->scale_, message);
	Networking::serialize(entity->entityId_, message);
	message.append(entity->selectingUserId_);
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

