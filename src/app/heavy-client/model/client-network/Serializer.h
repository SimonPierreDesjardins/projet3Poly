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

	void serialize(const glm::vec3& data, std::string& message);
	void serialize(uint32_t data, std::string& message);
	void serialize(uint8_t data, std::string& message);

	uint32_t deserializeInteger(char const* data);
	float deserializeFloat(char const* data);
	uint8_t deserializeChar(char data);
};

}

#endif // CLIENT_NETWORK_NETWORK_MANAGER_H
