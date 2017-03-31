#include <cassert>
#include <queue>

#include "NetworkStandard.h"
#include "AbstractMapRoom.h"
#include "TypeSerializerDeserializer.h"

namespace server
{

AbstractMapRoom::AbstractMapRoom(MapInfo* mapInfo, MapFileEntry* mapFile)
{
	mapInfo_ = mapInfo;
	// load up the tree from the file
	mapFileLoader_ = new MapFileLoader(&tree_, mapFile);
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

	// Send user list to the new User.
	for (auto it = _connectedUserList.begin(); it != _connectedUserList.end(); ++it)
	{
		if (it->second != user)
		{
			// Send joined response to new user.
			std::string userEntry(4, '\0');
			userEntry.append("mjs");
			Networking::serialize(mapInfo_->GetId(), userEntry);
			Networking::serialize(it->second->Info.GetId(), userEntry);
			userEntry.append(it->second->Info.UserName);
			Networking::MessageStandard::UpdateLengthHeader(userEntry);
			user->ForwardMessage(userEntry);
		}
	}

	std::queue<Entity*> sendingQueue;
	Entity* table = tree_.findEntity(1);
	if (table)
	{
		sendingQueue.push(table);
	}

	// Non-recursive top-down traversale of the tree.
	while (!sendingQueue.empty())
	{
		Entity* tosend = sendingQueue.front();
		sendingQueue.pop();

		std::string message;
		buildEntityCreationMessage(tosend, message);
		user->ForwardMessage(message);

		for (auto it = tosend->begin(); it != tosend->end(); ++it)
		{
			sendingQueue.push(it->second);
		}
	}
}

void AbstractMapRoom::TreatUserDisconnect(User* user)
{
	// Unsub from physic and map edition messages.
	user->removeSystemObserver(MAP_EDITION_MESSAGE);
	
	for (auto it = tree_.begin(); it != tree_.end(); ++it)
	{
		Entity* entity = &it->second;
		if (entity->userId_ == user->Info.GetId()) 
		{
			entity->userId_ = 0;
			std::string message;
			buildEntitySelectedMessage(entity, message);
			broadcastMessage(message);
		}
	}
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

void AbstractMapRoom::updateEntityProperty(char property, Entity* entity, const Eigen::Vector3f& value)
{
	entity->updatePhysicProperty((Networking::PropertyType)(property), value);
}

void AbstractMapRoom::handlePhysicMessage(User* sender, const std::string& message)
{
	assert(message[4] == PHYSIC_MESSAGE);

	uint32_t entityId = Networking::deserializeInteger(message.data() + Networking::MessageStandard::DATA_START);
	Entity* updatedEntity = tree_.findEntity(entityId);

	// If the entity id exists and it is selected by this user.
	if (updatedEntity && updatedEntity->userId_ == sender->Info.GetId())
	{
		Eigen::Vector3f updatedPropertyValue;
		updatedPropertyValue.x() =
			Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 4);
		updatedPropertyValue.y() =
			Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 8);
		updatedPropertyValue.z() =
			Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 12);

		updateEntityProperty(message[Networking::MessageStandard::COMMAND], updatedEntity, updatedPropertyValue);

		// Update other users.
		broadcastMessage(sender, message);
	}

	// TODO: check if entity is worth noting dirty map for
	mapFileLoader_->SetMapDirty();
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
		handleEntityRemovalMessage(sender, message);
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
	Networking::serialize(*entity->getProperty(Networking::ABSOLUTE_POSITION), message);
	Networking::serialize(*entity->getProperty(Networking::RELATIVE_POSITION), message);
	Networking::serialize(*entity->getProperty(Networking::ROTATION), message);
	Networking::serialize(*entity->getProperty(Networking::SCALE), message);
	Networking::serialize(entity->entityId_, message);
	Networking::serialize(entity->userId_, message);
}

void AbstractMapRoom::buildEntitySelectedMessage(Entity* entity, std::string& message)
{
	Networking::serialize((uint32_t)(14), message);
	message.append("es");
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

	Eigen::Vector3f* absPos = newEntity->getProperty(Networking::ABSOLUTE_POSITION);
	absPos->x() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 5);
	absPos->y() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 9);
	absPos->z() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 13);

	Eigen::Vector3f* relPos = newEntity->getProperty(Networking::RELATIVE_POSITION);
	relPos->x() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 17);
	relPos->y() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 21);
	relPos->z() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 25);

	Eigen::Vector3f* rotation = newEntity->getProperty(Networking::ROTATION);
	rotation->x() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 29);
	rotation->y() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 33);
	rotation->z() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 37);

	Eigen::Vector3f* scale = newEntity->getProperty(Networking::SCALE);
	scale->x() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 41);
	scale->y() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 45);
	scale->z() = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 49);

	std::string response(message);

	std::string newSize;
	Networking::serialize((uint32_t)(size + 8), newSize);
	response.replace(0, newSize.size(), newSize);
	Networking::serialize(newEntity->entityId_, response);
	Networking::serialize(newEntity->userId_, response);

	broadcastMessage(response);

	// update mapinfo with new Item
	switch (entityType) {
	case Networking::MessageStandard::ItemTypes::POST_ENTITY:
		mapInfo_->nbPoteaux++;
		break;
	case Networking::MessageStandard::ItemTypes::WALL_ENTITY:
		mapInfo_->nbMurs++;
		break;
	case Networking::MessageStandard::ItemTypes::BLACK_LINE_ENTITY:
		mapInfo_->nbLignes++;
		break;
	}

	// TODO: discriminate object type
	mapFileLoader_->SetMapDirty();

}

void AbstractMapRoom::handleEntityRemovalMessage(User* sender, const std::string& message)
{
	uint32_t entityId = Networking::deserializeInteger(message.data() + Networking::MessageStandard::DATA_START);



	Entity* deletedEntity = tree_.findEntity(entityId);

	switch (deletedEntity->entityType_) {
	case Networking::MessageStandard::ItemTypes::POST_ENTITY:
		mapInfo_->nbPoteaux--;
		break;
	case Networking::MessageStandard::ItemTypes::WALL_ENTITY:
		mapInfo_->nbMurs--;
		break;
	case Networking::MessageStandard::ItemTypes::BLACK_LINE_ENTITY:
		mapInfo_->nbLignes--;
		break;
	}

	// If the entity exists and the user is selecting it.
	if (deletedEntity && deletedEntity->userId_ == sender->Info.GetId())
	{
		tree_.deleteEntity(entityId);
	}
	broadcastMessage(sender, message);

	// mark map as dirty
	mapFileLoader_->SetMapDirty();
}

void AbstractMapRoom::handleEntitySelectionMessage(User* sender, const std::string& message)
{
	uint32_t entityId = Networking::deserializeInteger(message.data() + Networking::MessageStandard::DATA_START);
	char selectionState = message[Networking::MessageStandard::DATA_START + 4];

	Entity* entity = tree_.findEntity(entityId);
	if (entity)
	{
		// If we want to select the object and it's not selected.
		if (selectionState && entity->userId_ == 0)
		{
			entity->userId_ = sender->Info.GetId();
			std::string response(message);
			Networking::serialize(entity->userId_, response);
			Networking::MessageStandard::UpdateLengthHeader(response);
			broadcastMessage(response);
		}
		// If we have the object selected and we want to unselect it.
		else if (!selectionState && entity->userId_ == sender->Info.GetId())
		{
			entity->userId_ = 0;
			std::string response(message);
			Networking::serialize(entity->userId_, response);
			Networking::MessageStandard::UpdateLengthHeader(response);
			broadcastMessage(response);
		}
		// Any other message is not accepted.
	}
}

}