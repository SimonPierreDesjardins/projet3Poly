#include "LocalEvent.h"

void LocalEvent::buildUserJoinedRoomMessage(uint32_t roomId)
{
	std::string joinMessage = "mj" + std::to_string(roomId) + ";";
	joinMessage.insert(0, std::to_string(joinMessage.size()));
}

void LocalEvent::buildEntitySelectedMessage(uint32_t entityId)
{

}

void LocalEvent::buildUpdateRelativePositionMessage(int entityId, const glm::vec3& position)
{
}

void LocalEvent::buildUpdateAbsolutePositionMessage(int entityId, const glm::vec3& position)
{
}

void LocalEvent::buildUpdateScaleMessage(int entityId, const glm::vec3& resize)
{

}

void LocalEvent::buildUpdateRotationMessage(int entityId, const glm::vec3& rotation)
{

}

void LocalEvent::buildEntityCreatedMessage(uint32_t entityId, uint8_t type, uint32_t parentId, const glm::vec3& position)
{
	message_.clear();
	size_t messageSize = 32;
	serializer_.serialize((uint32_t)messageSize, message_);
	message_.append("ec");
	serializer_.serialize(type, message_);
	serializer_.serialize(entityId, message_);
	serializer_.serialize(parentId, message_);
	serializer_.serialize(message_, position);
}

void LocalEvent::buildEntityDeletedMessage(uint32_t entityId)
{

}
