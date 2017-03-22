#include "MapFileDatabase.h"

void server::MapFileEntry::WritePropertiesToBSON(bsoncxx::builder::basic::document & docBuilder)
{
}

std::string server::MapFileDatabase::GetCollectionName()
{
	return "Maps";
}

void server::MapFileDatabase::GetObjectPropertiesFromBSON(bsoncxx::document::view docView, MapFileEntry * object)
{
}
