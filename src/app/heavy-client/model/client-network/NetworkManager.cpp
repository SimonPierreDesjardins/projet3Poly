#include "NetworkManager.h"

namespace client_network
{


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
	message.append("mj");
	connection_.sendMessage(message);
}

}