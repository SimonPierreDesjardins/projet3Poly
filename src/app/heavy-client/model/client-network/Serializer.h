#ifndef CLIENT_NETWORK_SERIALIZER_H
#define CLIENT_NETWORK_SERIALIZER_H

#include <string>
#include <glm/glm.hpp>

namespace client_network
{

class Serializer
{
public:
	Serializer() = default;
	~Serializer() = default;

	void serialize(std::string& message, const glm::vec3& data);
	void serialize(uint32_t data, std::string& message);
	void serialize(uint8_t data, std::string& message);
};

}

#endif // CLIENT_NETWORK_NETWORK_MANAGER_H
