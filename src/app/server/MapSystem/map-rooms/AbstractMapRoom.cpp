#include <cassert>

#include "NetworkStandard.h"
#include "AbstractMapRoom.h"
#include "TypeSerializerDeserializer.h"

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
	Networking::serialize((uint32_t)(67), message);
	message.append("ec");
	message.append(1, entity->entityType_);
	Networking::serialize(entity->getParent()->entityId_, message);
	Networking::serialize(entity->absolutePosition_, message);
	Networking::serialize(entity->relativePosition_, message);
	Networking::serialize(entity->rotation_, message);
	Networking::serialize(entity->scale_, message);
	Networking::serialize(entity->entityId_, message);
	Networking::serialize(entity->userId_, message);
}

void AbstractMapRoom::handleEntityCreationMessage(User* sender, const std::string& message)
{
	uint32_t size = Networking::deserializeInteger(message.data());
	char entityType = message[Networking::MessageStandard::DATA_START];
	uint32_t parentId = Networking::deserializeInteger(message.data() + Networking::MessageStandard::DATA_START + 1);
	Entity* newEntity = tree_.createEntity(entityType, parentId);

	newEntity->userId_ = sender->Info.GetId();

	newEntity->absolutePosition_.x() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 5);
	newEntity->absolutePosition_.y() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 9);
	newEntity->absolutePosition_.z() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 13);

	newEntity->relativePosition_.x() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 17);
	newEntity->relativePosition_.y() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 21);
	newEntity->relativePosition_.z() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 25);

	newEntity->rotation_.x() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 29);
	newEntity->rotation_.y() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 33);
	newEntity->rotation_.z() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 37);

	newEntity->scale_.x() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 41);
	newEntity->scale_.y() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 45);
	newEntity->scale_.z() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 49);

	std::string response(message);

	std::string newSize;
	Networking::serialize((uint32_t)(size + 8), newSize);
	response.replace(0, newSize.size(), newSize);
	Networking::serialize(newEntity->entityId_, response);
	Networking::serialize(newEntity->userId_, response);

	broadcastMessage(response);
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

