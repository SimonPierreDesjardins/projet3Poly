#include "Serializer.h"

namespace client_network
{

void Serializer::serialize(std::string& message, const glm::vec3& data)
{
	char const* serialized = reinterpret_cast<char const*>(&data.x);
	message.append(serialized, 4);
	serialized = reinterpret_cast<char const*>(&data.y);
	message.append(serialized, 4);
	serialized = reinterpret_cast<char const*>(&data.z);
	message.append(serialized, 4);
}

void Serializer::serialize(uint32_t data, std::string& message)
{
	char* serialized = reinterpret_cast<char*>(&data);
	message.append(serialized, 4);
}

void Serializer::serialize(uint8_t data, std::string& message)
{
	char* serialized = reinterpret_cast<char*>(&data);
	message.append(serialized, 1);
}

}
