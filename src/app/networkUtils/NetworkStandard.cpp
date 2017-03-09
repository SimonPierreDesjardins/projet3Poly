#include "include\NetworkStandard.h"

std::string Networking::MessageStandard::AddMessageLengthHeader(std::string & message)
{
	int length = message.size();
	std::string lengthHeader(static_cast<char*>(static_cast<void*>(&length)), sizeof length);
	// optimal string concatenation modified message
	return std::move(lengthHeader += message);
}

int Networking::MessageStandard::GetMessageLength(std::string & message)
{
	return int((unsigned char)(message[0]) << 24 |
		(unsigned char)(message[1]) << 16 |
		(unsigned char)(message[2]) << 8 |
		(unsigned char)(message[3]));
}
