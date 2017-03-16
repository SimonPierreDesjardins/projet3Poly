#ifndef __NETWORK_STANDARD_H
#define __NETWORK_STANDARD_H

#include <string>

namespace Networking {

enum PropertyType
{
	RELATIVE_POSITION = 'p',
	ABSOLUTE_POSITION = 'a',
	ROTATION = 'r',
	SCALE = 's',
	LINEAR_VELOCITY = 'v',
	ANGULAR_VELOCITY = 'w'
};

namespace MessageStandard {

	//Buffer size constant
	const int BUFFER_SIZE = 1024;

	//Index of the system indicator byte in the message
	const int LENGTH_END = 0;
	const int LENGTH_BEGIN = 3;
	const int SYSTEM = 4;
	const int COMMAND = 5;
	const int DATA_START = 6;

	std::string AddMessageLengthHeader(const std::string& message);
	void AddMessageLengthHeader(size_t size, std::string& message);
	void UpdateLengthHeader(std::string& message);

	int GetMessageLength(std::string& message);
}

}

#endif //!__NETWORK_STANDARD_H
