#include "IdGenerator.h"

std::string & server::IdGenerator::GenerateId()
{
	std::ostringstream ostr;

	ostr << std::setfill('0') << std::setw(stringLength) << nextId;

	nextId++;

	return ostr.str();
}

unsigned int server::IdGenerator::nextId = 0;