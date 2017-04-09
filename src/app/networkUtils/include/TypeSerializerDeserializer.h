#ifndef NETWORKING_SERIALIZER_H
#define NETWORKING_SERIALIZER_H

#include <string>
#include <glm/glm.hpp>
#include "Eigen/Dense"

namespace Networking
{
	void serialize(const glm::vec3& data, std::string& message);
	void serialize(const Eigen::Vector3f& data, std::string& message);
	void serialize(float, std::string& message);
	void serialize(uint32_t data, std::string& message);
	void serialize(uint8_t data, std::string& message);

	uint32_t deserializeInteger(char const* data);
	float deserializeFloat(char const* data);
	uint8_t deserializeChar(char data);

	void deserialize(char const* data, Eigen::Vector3f& prop);
	void deserialize(char const* data, glm::vec3& prop);
	void deserialize(char const* data, glm::dvec3& prop);
}

#endif // CLIENT_NETWORK_NETWORK_MANAGER_H
