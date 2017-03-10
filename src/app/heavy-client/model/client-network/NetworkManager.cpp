#include "NetworkManager.h"

namespace client_network
{

NetworkManager::NetworkManager(event_handler::EventHandler* eventHandler)
	: dispatcher_(eventHandler)
{
	connection_.setOnMessageReceivedHandler(&MessageDispatcher::handleReceivedMessage, &dispatcher_);
	dispatcher_.startDispatching();
}

void NetworkManager::handleServerMessage(const std::string& message)
{
}

void NetworkManager::authenticate(const std::string& username)
{
	std::string message;
	serializer_.serialize(uint32_t(username.size() + 2), message);
	message.append("ul" + username);
	connection_.sendMessage(message);
}

void NetworkManager::createProfile(const std::string& username)
{
	std::string message;
	serializer_.serialize(uint32_t(username.size() + 2), message);
	message.append("uc" + username);
	connection_.sendMessage(message);
}

void NetworkManager::requestToJoinMapSession(uint32_t mapId)
{
	std::string message;
	serializer_.serialize(uint32_t(6), message);
	message.append("mj");
	serializer_.serialize(mapId, message);
	connection_.sendMessage(message);
}

void NetworkManager::requestToleaveMapSession()
{
	std::string message;
	serializer_.serialize(uint32_t(2), message);
	message.append("ml");
	connection_.sendMessage(message);
}

void NetworkManager::requestEntityCreation(uint32_t entityId, uint8_t type, uint32_t parentId,
	const glm::vec3& absolutePosition, const glm::vec3& relativePosition)
{
	std::string message;
	serializer_.serialize(uint32_t(35), message);
	message.append("ec");
	serializer_.serialize(entityId, message);
	serializer_.serialize(type, message);
	serializer_.serialize(parentId, message);
	serializer_.serialize(absolutePosition, message);
	serializer_.serialize(relativePosition, message);
	connection_.sendMessage(message);
}

void NetworkManager::sendSizePrefixedMessage(std::string& message)
{
	std::string size;
	serializer_.serialize((uint32_t)(message.size()), size);
	sendMessage(message.insert(0, size));
}

}