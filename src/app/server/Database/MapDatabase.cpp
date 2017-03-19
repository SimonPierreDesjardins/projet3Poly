#include "MapDatabase.h"
#include "IdGenerator.h"

server::MapInfo::MapInfo()
{
	//TODO: build this from string eventually
	mapName = GetId();
}

void server::MapInfo::WritePropertiesToBSON(bsoncxx::builder::basic::document & docBuilder)
{
	using bsoncxx::builder::basic::kvp;

	docBuilder.append(kvp("mapName", mapName));
	docBuilder.append(kvp("mapType", mapType));
	docBuilder.append(kvp("isPrivate", isPrivate));
}

std::string server::MapDatabase::GetCollectionName()
{
	return "MapInfos";
}

void server::MapDatabase::GetObjectPropertiesFromBSON(bsoncxx::document::view docView, MapInfo* mapInfo)
{
	mapInfo->mapName = docView["mapName"].get_utf8().value.to_string();
	mapInfo->mapName = docView["mapType"].get_utf8().value.to_string();
	mapInfo->mapName = docView["isPrivate"].get_bool();

}
