#include "MapDatabase.h"
#include "IdGenerator.h"

server::MapInfo::MapInfo()
{
	_mapId = IdGenerator::GenerateId();
	mapName = _mapId;
}

const std::string & server::MapInfo::GetId()
{
	return _mapId;
	// TODO: insert return statement here
}

void server::MapDatabase::WriteObject(DatalistElement & element)
{

}

