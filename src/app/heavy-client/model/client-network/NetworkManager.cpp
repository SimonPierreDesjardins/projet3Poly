#include <iostream>

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
	serializer_.serialize(uint32_t(username.size() + 6), message);
	message.append("ul" + username);
	connection_.sendMessage(message);
}

void NetworkManager::createProfile(const std::string& username)
{
	std::string message;
	serializer_.serialize(uint32_t(username.size() + 6), message);
	message.append("uc");
	message.append(username);
	connection_.sendMessage(message);
}

void NetworkManager::requestMapCreation(const std::string& mapName, uint8_t mapType)
{
	std::string message;
	serializer_.serialize((uint32_t)(mapName.size() + 7), message);
	message.append("mc");
	serializer_.serialize(mapType, message);
	// TODO: pass privacy and password, currently public by default
	message.append(0x00);
	message.append(mapName);
	connection_.sendMessage(message);
}

void NetworkManager::requestToJoinMapSession(uint32_t mapId)
{
	std::string message;
	serializer_.serialize(uint32_t(10), message);
	message.append("mj");
	serializer_.serialize(mapId, message);
	connection_.sendMessage(message);
}

void NetworkManager::requestToQuitMapSession()
{
	std::string message;
	serializer_.serialize(uint32_t(6), message);
	message.append("mq");
	connection_.sendMessage(message);
}

void NetworkManager::requestEntityCreation(uint8_t type, uint32_t parentId,
	const glm::vec3& absolutePosition, const glm::vec3& relativePosition,
	const glm::vec3& rotation, const glm::vec3& scale)
{
	std::string message;
	serializer_.serialize(uint32_t(59), message);
	message.append("ec");
	serializer_.serialize(type, message);
	serializer_.serialize(parentId, message);
	serializer_.serialize(absolutePosition, message);
	serializer_.serialize(relativePosition, message);
	serializer_.serialize(rotation, message);
	serializer_.serialize(scale, message);
	connection_.sendMessage(message);
}

void NetworkManager::requestEntityRemoval(uint32_t entityId)
{
	std::string message;
	serializer_.serialize(uint32_t(10), message);
	message.append("ed");
	serializer_.serialize(entityId, message);
	connection_.sendMessage(message);
}

void NetworkManager::requestEntitySelection(uint32_t entityId, char selectionState)
{
	std::string message;
	serializer_.serialize(uint32_t(11), message);
	message.append("es");
	serializer_.serialize(entityId, message);
	message.append(1, selectionState);
	connection_.sendMessage(message);
}

void NetworkManager::requestEntityPropertyUpdate(uint32_t entityId, char propertyType, const::glm::vec3& propertyValue)
{
	std::string message;
	serializer_.serialize(uint32_t(22), message);
	message.append(1, 'p');
	message.append(1, propertyType);
	serializer_.serialize(entityId, message);
	serializer_.serialize(propertyValue, message);
	connection_.sendMessage(message);
}

void NetworkManager::sendSizePrefixedMessage(std::string& message)
{
	std::string size;
	serializer_.serialize((uint32_t)(message.size() + 4), size);
	sendMessage(message.insert(0, size));
}

}