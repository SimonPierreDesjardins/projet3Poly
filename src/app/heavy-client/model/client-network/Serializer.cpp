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

uint32_t Serializer::deserializeInteger(char data[4])
{
	uint32_t* deserialized = reinterpret_cast<uint32_t*>(data);
	return *deserialized;
}

float Serializer::deserializeFloat(char data[4])
{
	float* deserialized = reinterpret_cast<float*>(data);
	return *deserialized;
}

uint8_t Serializer::deserializeChar(char data)
{
	uint8_t* deserialized = reinterpret_cast<uint8_t*>(&data);
	return *deserialized;
}

}
