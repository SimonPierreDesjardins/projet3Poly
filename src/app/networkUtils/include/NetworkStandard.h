#ifndef __NETWORK_STANDARD_H
#define __NETWORK_STANDARD_H
namespace Networking {
	namespace MessageStandard {
		//Index of the system indicator byte in the message
		const int LENGTH_END = 0;
		const int LENGTH_BEGIN = 3;
		const int SYSTEM = 4;
		const int COMMAND = 5;
		const int DATA_START = 6;
	}
}

#endif //!__NETWORK_STANDARD_H
