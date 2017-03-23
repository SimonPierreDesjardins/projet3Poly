#include "MapFileDatabase.h"

server::MapFileEntry::MapFileEntry(unsigned int id):DatalistElement(id)
{
}

server::MapFileEntry::MapFileEntry():DatalistElement()
{
}

void server::MapFileEntry::WritePropertiesToBSON(bsoncxx::builder::basic::document & docBuilder)
{
	using bsoncxx::builder::basic::kvp;
	docBuilder.append(kvp("MapData", MapData));
}

server::MapFileDatabase::MapFileDatabase(Database* db) :BaseDatalist(db) {
	BuildDatabaseFromCollection(GetCollectionName());
}

std::string server::MapFileDatabase::GetCollectionName()
{
	return "Maps";
}

void server::MapFileDatabase::GetObjectPropertiesFromBSON(bsoncxx::document::view docView, MapFileEntry * object)
{
	object -> MapData = docView["MapData"].get_utf8().value.to_string();
}
