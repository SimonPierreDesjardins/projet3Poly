#include "TypeSerializerDeserializer.h"

namespace Networking
{

void serialize(float data, std::string& message)
{
	char const* serialized = reinterpret_cast<char const*>(&data);
	message.append(serialized, 4);
}

void serialize(const Eigen::Vector3f& data, std::string& message)
{
	serialize(data.x(), message);
	serialize(data.y(), message);
	serialize(data.z(), message);
}

void serialize(const glm::vec3& data, std::string& message)
{
	serialize(data.x, message);
	serialize(data.y, message);
	serialize(data.z, message);
}

void serialize(uint32_t data, std::string& message)
{
	char* serialized = reinterpret_cast<char*>(&data);
	message.append(serialized, 4);
}

void serialize(uint8_t data, std::string& message)
{
	char* serialized = reinterpret_cast<char*>(&data);
	message.append(serialized, 1);
}

uint32_t deserializeInteger(char const* data)
{
	uint32_t const* deserialized = reinterpret_cast<uint32_t const*>(data);
	return *deserialized;
}

float deserializeFloat(char const* data)
{
	float const* deserialized = reinterpret_cast<float const*>(data);
	return *deserialized;
}

uint8_t deserializeChar(char data)
{
	uint8_t* deserialized = reinterpret_cast<uint8_t*>(&data);
	return *deserialized;
}

void deserialize(char const* data, Eigen::Vector3f& prop)
{
	prop.x() = deserializeFloat(data);
	prop.y() = deserializeFloat(data + 4);
	prop.z() = deserializeFloat(data + 8);
}

void deserialize(char const* data, glm::vec3& prop)
{
	prop.x = deserializeFloat(data);
	prop.y = deserializeFloat(data + 4);
	prop.z = deserializeFloat(data + 8);
}

void deserialize(char const* data, glm::dvec3& prop)
{
	prop.x = deserializeFloat(data);
	prop.y = deserializeFloat(data + 4);
	prop.z = deserializeFloat(data + 8);
}

}
