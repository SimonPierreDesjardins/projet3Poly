#include "LocalEvent.h"

void LocalEvent::buildUserJoinedRoomMessage(uint32_t roomId)
{
	std::string joinMessage = "mj" + std::to_string(roomId) + ";";
	joinMessage.insert(0, std::to_string(joinMessage.size()));
}

void LocalEvent::buildEntitySelectedMessage(uint32_t entityId)
{

}

void LocalEvent::buildEntityMovedRelativeMessage(int entityId, const glm::vec3& position)
{
	message_ = "pr" + std::to_string(entityId) + ";" + std::to_string(position.x) + ";" + std::to_string(position.y) + ";" + std::to_string(position.z);
	message_.insert(0, std::to_string(message_.size()));
}

void LocalEvent::buildEntityMovedAbsoluteMessage(int entityId, const glm::vec3& position)
{
	message_ = "pa" + std::to_string(entityId) + ";" + std::to_string(position.x) + ";" + std::to_string(position.y) + ";" + std::to_string(position.z);
	message_.insert(0, std::to_string(message_.size()));
}

void LocalEvent::buildEntityResizedMessage(int entityId, const glm::vec3& resize)
{

}

void LocalEvent::buildEntityRotatedMessage(int entityId, const glm::vec3& rotation)
{

}

void LocalEvent::buildEntityCreatedMessage(uint32_t entityId, uint8_t type, uint32_t parentId, const glm::vec3& position)
{
	message_.clear();
	size_t messageSize = 32;
	serializer_.serialize((uint32_t)messageSize, message_);
	message_.append("pc");
	serializer_.serialize(entityId, message_);
	serializer_.serialize(parentId, message_);
	serializer_.serialize(message_, position);
}

void LocalEvent::buildEntityDeletedMessage(uint32_t entityId)
{

}
