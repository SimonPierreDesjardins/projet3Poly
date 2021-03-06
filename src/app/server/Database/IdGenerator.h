#ifndef __ID_GENERATOR_H
#define __ID_GENERATOR_H

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

namespace server {
	class IdGenerator {
	public:
		static unsigned int GenerateId();

		static void SetNextId(unsigned int nId);

	private:
		static unsigned int nextId;
	};


}

#endif // !__ID_GENERATOR_H


