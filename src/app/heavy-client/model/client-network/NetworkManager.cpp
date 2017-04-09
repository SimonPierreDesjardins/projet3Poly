#include <iostream>
#include <ios>
#include <fstream>

#include "NetworkStandard.h"
#include "TypeSerializerDeserializer.h"

#include "PhysicsComponent.h"
#include "NetworkManager.h"
#include "EventHandler.h"

namespace client_network
{

NetworkManager::NetworkManager(event_handler::EventHandler* eventHandler)
	: dispatcher_(eventHandler)
{
	connection_.setOnMessageReceivedHandler(&MessageDispatcher::handleReceivedMessage, &dispatcher_);
	connection_.setOnConnectionLostHandler(&event_handler::EventHandler::onUserDisconnected, eventHandler);
	dispatcher_.startDispatching();
}

void NetworkManager::handleServerMessage(const std::string& message)
{
}

void NetworkManager::authenticate(const std::string& username)
{
	std::string message;
	serializer_.serialize(uint32_t(username.size() + 7), message);
	message.append("ul");
	message += (char)1; // signifie qu'on se log avec un client lourd.
	message.append(username);
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

void NetworkManager::uploadMap(const std::string& filePath) {
	//Forgive me, this function is gonna be a clusterfuck

	// open file
	std::ifstream mapFile(filePath, std::ios::in | std::ios::binary | std::ios::ate);
	if (!mapFile.is_open())
	{
		return;
	}

	// load file into mem block
	auto size = mapFile.tellg();
	char* memblock = new char[size];
	mapFile.seekg(0, std::ios::beg);
	mapFile.read(memblock, size);
	mapFile.close();

	// start reading through the memblock, segmenting into packets and sending them

	std::vector<std::string> packets;

	int maxPacketSize = 256;
	int bytesLeft = size;
	int currentByte = 0;

	while (bytesLeft > 0) {
		// add to an array of messages to send;
		auto packetSize = (maxPacketSize < bytesLeft) ? maxPacketSize : bytesLeft;
		packets.push_back(std::string(memblock + currentByte, packetSize));
		currentByte += packetSize;
		bytesLeft -= packetSize;
	}

	char numberOfPackets = packets.size();
	for (char i = 0; i < numberOfPackets; ++i) {
		std::string message("");
		serializer_.serialize(uint32_t(packets[i].size() + 8), message);
		message.append("mt");
		message += i + 1;
		message += numberOfPackets;
		message += packets[i];
		connection_.sendMessage(message);
	}

	delete[] memblock;
}

void NetworkManager::requestMapCreation(const std::string& mapName, const std::string& password, uint8_t mapType, uint8_t isPrivate)
{
	std::string message;
	uint32_t messageBaseSize = isPrivate ? 9 : 8;

	// on rajoute isPrivate à la taille pour symboliser l'ajout du ; entre le nom et le mot de passe
	serializer_.serialize((uint32_t)(mapName.size() + password.size() + messageBaseSize + isPrivate), message);
	message.append("mc");
	serializer_.serialize(mapType, message);
	serializer_.serialize(isPrivate, message);
	message.append(mapName);
	if (isPrivate) {
		message += ';';
		message.append(password);
	}
	connection_.sendMessage(message);
}

void NetworkManager::requestMapPermissionChange(const uint32_t mapId, uint8_t permission, const std::string & password)
{
	std::string message;
	serializer_.serialize(uint32_t(11 + password.size()), message);
	message.append("mp");
	serializer_.serialize(mapId, message);
	serializer_.serialize(permission, message);
	message.append(password);
	connection_.sendMessage(message);
}

void NetworkManager::requestToJoinMapSession(uint32_t mapId, const std::string & password)
{
	std::string message;
	serializer_.serialize(uint32_t(10 + password.size()), message);
	message.append("mj");
	serializer_.serialize(mapId, message);
	if (password.size() > 0) {
		message.append(password);
	}
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

void NetworkManager::requestStackedPropertyUpdate(uint32_t entityId, const PhysicsComponent& properties)
{
	std::string message;
	Networking::serialize(uint32_t(0), message);
	message.append(1, 'p');
	message.append(1, 'e');
	Networking::serialize(entityId, message);

	Networking::serialize(glm::vec3(properties.relativePosition), message);
	Networking::serialize(glm::vec3(properties.absolutePosition), message);
	Networking::serialize(glm::vec3(properties.rotation), message);
	Networking::serialize(glm::vec3(properties.linearVelocity), message);
	Networking::serialize(glm::vec3(properties.angularVelocity), message);

	Networking::MessageStandard::UpdateLengthHeader(message);

	connection_.sendMessage(message);
}

void NetworkManager::sendSizePrefixedMessage(std::string& message)
{
	std::string size;
	serializer_.serialize((uint32_t)(message.size() + 4), size);
	sendMessage(message.insert(0, size));
}

}