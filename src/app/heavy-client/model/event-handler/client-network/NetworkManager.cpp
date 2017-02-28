#include "NetworkManager.h"

namespace client_network
{

void NetworkManager::requestConnection(const std::string& hostName, const std::string& port)
{
	connection_.requestConnection(hostName, port);
}

void NetworkManager::createProfile(const std::string& profileName)
{

}

void NetworkManager::authenticate(const std::string& profileName)
{

}

}