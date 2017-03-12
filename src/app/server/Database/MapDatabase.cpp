#include "MapDatabase.h"
#include "IdGenerator.h"

server::MapInfo::MapInfo()
{
	_mapId = IdGenerator::GenerateId();
	mapName = _mapId;
}

void server::MapDatabase::WriteObject(DatalistElement & element)
{

}

