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

void NetworkManager::requestMapCreation(const std::string& mapName, uint8_t mapType)
{
	std::string message;
	serializer_.serialize((uint32_t)(mapName.size() + 3), message);
	message.append("mc");
	serializer_.serialize(mapType, message);
	message.append(mapName);
	connection_.sendMessage(message);
}

void NetworkManager::requestToJoinMapSession(const std::string& mapId)
{
	if (mapId.size() != 20)
	{
		std::cout << "requestToJoinMapSession - Invalid mapId :  " << mapId  << std::endl;
		return;
	}
	std::string message;
	serializer_.serialize(uint32_t(22), message);
	message.append("mj");
	message.append(mapId);
	connection_.sendMessage(message);
}

void NetworkManager::requestToleaveMapSession()
{
	std::string message;
	serializer_.serialize(uint32_t(2), message);
	message.append("ml");
	connection_.sendMessage(message);
}

void NetworkManager::requestEntityCreation(uint8_t type, uint32_t parentId,
	const glm::vec3& absolutePosition, const glm::vec3& relativePosition,
	const glm::vec3& rotation, const glm::vec3& scale)
{
	std::string message;
	serializer_.serialize(uint32_t(55), message);
	message.append("ec");
	serializer_.serialize(type, message);
	serializer_.serialize(parentId, message);
	serializer_.serialize(absolutePosition, message);
	serializer_.serialize(relativePosition, message);
	serializer_.serialize(rotation, message);
	serializer_.serialize(scale, message);
	connection_.sendMessage(message);
}

void NetworkManager::sendSizePrefixedMessage(std::string& message)
{
	std::string size;
	serializer_.serialize((uint32_t)(message.size()), size);
	sendMessage(message.insert(0, size));
}

}