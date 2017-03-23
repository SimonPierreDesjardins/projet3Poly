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
	const int BUFFER_SIZE = 64000; //hueg buffer for hueg filez swiggidy

	//Index of the system indicator byte in the message
	const int LENGTH_END = 0;
	const int LENGTH_BEGIN = 3;
	const int SYSTEM = 4;
	const int COMMAND = 5;
	const int DATA_START = 6;

	std::string AddMessageLengthHeader(const std::string& message);
	void AddMessageLengthHeader(size_t size, std::string& message);

	int GetMessageLength(std::string& message);

	namespace ItemTypes{
		enum EntityType
		{
			TABLE_ENTITY,
			START_ENTITY,
			DUPLICATION_ENTITY,
			POST_ENTITY,
			WALL_ENTITY,
			BLACK_LINE_ENTITY,
			SEGMENT_ENTITY,
			JUNCTION_ENTITY,
			WHEEL_ENTITY,
			ROBOT_ENTITY,
			F1_ENTITY,
			TRUCK_ENTITY,
			VOLKS_ENTITY,
			AUDI_ENTITY,
			TELEPORT_ENTITY
		};
	}
}

}

#endif //!__NETWORK_STANDARD_H
