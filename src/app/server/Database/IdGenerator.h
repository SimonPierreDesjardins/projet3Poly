#ifndef __ID_GENERATOR_H
#define __ID_GENERATOR_H

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

namespace server {
	class IdGenerator {
	public:
		static std::string& GenerateId();

	private:
		static unsigned int nextId;

		static const unsigned int stringLength = 20;
	};


}

#endif // !__ID_GENERATOR_H


