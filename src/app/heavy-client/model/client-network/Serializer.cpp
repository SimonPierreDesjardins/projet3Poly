#include "Serializer.h"

namespace client_network
{

void Serializer::serialize(const glm::vec3& data, std::string& message)
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

uint32_t Serializer::deserializeInteger(char const* data)
{
	uint32_t const* deserialized = reinterpret_cast<uint32_t const*>(data);
	return *deserialized;
}

float Serializer::deserializeFloat(char const* data)
{
	float const* deserialized = reinterpret_cast<float const*>(data);
	return *deserialized;
}

uint8_t Serializer::deserializeChar(char data)
{
	uint8_t* deserialized = reinterpret_cast<uint8_t*>(&data);
	return *deserialized;
}

}
