#include "MapDatabase.h"
#include "IdGenerator.h"

server::MapInfo::MapInfo()
{
	//TODO: build this from string eventually
	mapName = GetId();
}

void server::MapInfo::WritePropertiesToBSON(bsoncxx::builder::stream::document & docBuilder)
{
	docBuilder
		<< "mapName" << mapName
		<< "mapType" << mapType
		<< "isPrivate" << isPrivate;
}

