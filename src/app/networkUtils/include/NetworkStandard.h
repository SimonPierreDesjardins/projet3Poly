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

		void AddMessageLengthHeader(std::string& message) {
			int length = message.size();
			std::string lengthHeader(static_cast<char*>(static_cast<void*>(&length)), sizeof length);
			// optimal string concatenation modified message
			message = (lengthHeader += message);
		}

		int GetMessageLength(std::string& message) {
			int length = int((unsigned char)(message[0]) << 24 |
				(unsigned char)(message[1]) << 16 |
				(unsigned char)(message[2]) << 8 |
				(unsigned char)(message[3]));
			return 0;
		}
	}
}

#endif //!__NETWORK_STANDARD_H
