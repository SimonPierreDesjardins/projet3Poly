#include "IdGenerator.h"

unsigned int server::IdGenerator::GenerateId()
{
	nextId++;

	return nextId;
}

unsigned int server::IdGenerator::nextId = 1;