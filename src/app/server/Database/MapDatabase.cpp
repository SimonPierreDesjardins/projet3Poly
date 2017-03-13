#include "MapDatabase.h"
#include "IdGenerator.h"

server::MapInfo::MapInfo()
{
	//TODO: build this from string eventually
	mapName = GetId();
}

