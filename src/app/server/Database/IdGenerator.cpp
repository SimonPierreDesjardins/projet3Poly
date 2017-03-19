#include "IdGenerator.h"

unsigned int server::IdGenerator::GenerateId()
{
	nextId++;

	return nextId;
}

void server::IdGenerator::SetNextId(unsigned int nId)
{
	if (nId > nextId) {
		nextId = nId;
	}
}

unsigned int server::IdGenerator::nextId = 1;