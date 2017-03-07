#include "NetworkManager.h"

namespace client_network
{

void NetworkManager::joinRoom(int roomId)
{
	if (connection_.isConnected())
	{
		std::string joinMessage = "mj" + std::to_string(roomId) + ";";
		joinMessage.insert(0, std::to_string(joinMessage.size()));
		connection_.sendMessage(joinMessage);
	}
}

void NetworkManager::requestUpdateRelativePosition(int entityId, const glm::vec3& position)
{
	if (connection_.isConnected())
	{
		std::string moveMessage = "pr" + std::to_string(entityId) + ";" + std::to_string(position.x) + ";" + std::to_string(position.y) + ";" + std::to_string(position.z);
		moveMessage.insert(0, std::to_string(moveMessage.size()));
		connection_.sendMessage(moveMessage);
	}
}

void NetworkManager::requestUpdateAbsolutePosition(int entityId, const glm::vec3& position)
{
	if (connection_.isConnected())
	{
		std::string moveMessage = "pa" + std::to_string(entityId) + ";" + std::to_string(position.x) + ";" + std::to_string(position.y) + ";" + std::to_string(position.z);
		moveMessage.insert(0, std::to_string(moveMessage.size()));
		connection_.sendMessage(moveMessage);
	}
}

void NetworkManager::requestUpdateSize(int entityId, const glm::vec3& size)
{

}

void NetworkManager::requestUpdateRotation(int entityId, const glm::vec3& rotation)
{

}

void NetworkManager::requestUpdateSelected(int entityId, bool isSelected)
{

}

void NetworkManager::requestEntityCreation(const std::string& type)
{
	if (connection_.isConnected())
	{
		std::string moveMessage = "pc" + type + ";";
		moveMessage.insert(0, std::to_string(moveMessage.size()));
		connection_.sendMessage(moveMessage);
	}
}

void NetworkManager::handleServerMessage(const std::string& message)
{
}

}