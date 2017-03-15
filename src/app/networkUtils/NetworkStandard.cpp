#include "include\NetworkStandard.h"
#include "TypeSerializerDeserializer.h"

std::string Networking::MessageStandard::AddMessageLengthHeader(const std::string & message)
{
	std::string lengthHeader = "";
	serialize((uint32_t)(message.size() + sizeof uint32_t), lengthHeader);
	// optimal string concatenation modified message
	return std::move( lengthHeader.append(message));
}

int Networking::MessageStandard::GetMessageLength(std::string & message)
{
	return deserializeInteger(message.c_str());
}
