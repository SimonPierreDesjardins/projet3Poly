#include <cassert>
#include <queue>

#include "NetworkStandard.h"
#include "AbstractMapRoom.h"
#include "TypeSerializerDeserializer.h"

namespace server
{

AbstractMapRoom::AbstractMapRoom(MapInfo* info, MapFileEntry* mapFile)
{
	mapInfo = info;
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
	user->addSystemObserver(this, GAME_MESSAGE);

	// Send user list to the new User.
	for (auto it = _connectedUserList.begin(); it != _connectedUserList.end(); ++it)
	{
		if (it->second != user)
		{
			// Send joined response to new user.
			std::string userEntry(4, '\0');
			userEntry.append("mjs");
			Networking::serialize(mapInfo->GetId(), userEntry);
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
	
	// Create a MapSession for the user
	//userMapSessions_.insert(std::make_pair( user->Info.GetId(), ServerMapSession(user, (ArbreRendu*)tree_.getPhysicsTree(), this)));

	std::string mapReadyMessage;
	Networking::serialize(uint32_t(0), mapReadyMessage);
	mapReadyMessage.append("mr");
	Networking::serialize(mapInfo->GetId(), mapReadyMessage);
	Networking::MessageStandard::UpdateLengthHeader(mapReadyMessage);
	user->ForwardMessage(mapReadyMessage);
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

void AbstractMapRoom::handlePhysicMessage(User* sender, const std::string& message)
{
	assert(message[4] == PHYSIC_MESSAGE);

	if (message[Networking::MessageStandard::COMMAND] == 'e')
	{
		handleStackedPropertyMessage(sender, message);
	}
	else
	{
		handleSinglePropertyMessage(sender, message);
	}

	// TODO: check if entity is worth noting dirty map for
	mapFileLoader_->SetMapDirty();
}

void AbstractMapRoom::handleSinglePropertyMessage(User* sender, const std::string& message)
{
	uint32_t entityId = Networking::deserializeInteger(message.data() + Networking::MessageStandard::DATA_START);
	Entity* updatedEntity = tree_.findEntity(entityId);

	// If the entity id exists and it is selected by this user.
	if (updatedEntity && updatedEntity->userId_ == sender->Info.GetId())
	{
		auto property = updatedEntity->getProperty((Networking::PropertyType)message[Networking::MessageStandard::COMMAND]);
		property -> x =
			Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 4);
		property -> y =
			Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 8);
		property -> z =
			Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 12);

		// Update other users.
		broadcastMessage(sender, message);
	}
}

void AbstractMapRoom::handleStackedPropertyMessage(User* sender, const std::string& message)
{
	assert(message.size() == 70);
	uint32_t entityId = Networking::deserializeInteger(message.data() + Networking::MessageStandard::DATA_START);
	Entity* updatedEntity = tree_.findEntity(entityId);

	// If the entity id exists and it is selected by this user.
	if (updatedEntity && updatedEntity->userId_ == sender->Info.GetId())
	{
		char const* data = message.data() + Networking::MessageStandard::DATA_START + 4;
		Networking::deserialize(data, *updatedEntity->getProperty(Networking::RELATIVE_POSITION));

		data += 12;
		Networking::deserialize(data, *updatedEntity->getProperty(Networking::ABSOLUTE_POSITION));

		data += 12;
		Networking::deserialize(data, *updatedEntity->getProperty(Networking::ROTATION));

		data += 12;
		Networking::deserialize(data, *updatedEntity->getProperty(Networking::LINEAR_VELOCITY));

		data += 12;
		Networking::deserialize(data, *updatedEntity->getProperty(Networking::ANGULAR_VELOCITY));

		broadcastMessage(sender, message);
	}
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
	Networking::serialize(glm::vec3(*entity->getProperty(Networking::ABSOLUTE_POSITION)), message);
	Networking::serialize(glm::vec3(*entity->getProperty(Networking::RELATIVE_POSITION)), message);
	Networking::serialize(glm::vec3(*entity->getProperty(Networking::ROTATION)), message);
	Networking::serialize(glm::vec3(*entity->getProperty(Networking::SCALE)), message);
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

	auto absPos = newEntity->getProperty(Networking::ABSOLUTE_POSITION);
	absPos->x = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 5);
	absPos->y = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 9);
	absPos->z = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 13);


	auto relPos = newEntity->getProperty(Networking::RELATIVE_POSITION);
	relPos->x = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 17);
	relPos->y = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 21);
	relPos->z = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 25);

	auto rotation = newEntity->getProperty(Networking::ROTATION);
	rotation->x = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 29);
	rotation->y = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 33);
	rotation->z = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 37);

	auto scale = newEntity->getProperty(Networking::SCALE);
	scale->x = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 41);
	scale->y = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 45);
	scale->z = Networking::deserializeFloat(message.data() + Networking::MessageStandard::DATA_START + 49);

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
		mapInfo->nbPoteaux++;
		break;
	case Networking::MessageStandard::ItemTypes::WALL_ENTITY:
		mapInfo->nbMurs++;
		break;
	case Networking::MessageStandard::ItemTypes::BLACK_LINE_ENTITY:
		mapInfo->nbLignes++;
		break;
	case Networking::MessageStandard::ItemTypes::TELEPORT_ENTITY:
		mapInfo->nbTeleporteurs++;
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
		mapInfo->nbPoteaux--;
		break;
	case Networking::MessageStandard::ItemTypes::WALL_ENTITY:
		mapInfo->nbMurs--;
		break;
	case Networking::MessageStandard::ItemTypes::BLACK_LINE_ENTITY:
		mapInfo->nbLignes--;
		break;
	case Networking::MessageStandard::ItemTypes::TELEPORT_ENTITY:
		mapInfo->nbTeleporteurs--;
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