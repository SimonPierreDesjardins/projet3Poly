#include "MapDatabase.h"
#include "IdGenerator.h"

server::MapInfo::MapInfo():DatalistElement()
{
	//TODO: build this from string eventually
	mapName = GetId();
}

server::MapInfo::MapInfo(unsigned int id):DatalistElement(id)
{
}

void server::MapInfo::WritePropertiesToBSON(bsoncxx::builder::basic::document & docBuilder)
{
	using bsoncxx::builder::basic::kvp;
	docBuilder.append(kvp("mapName", mapName));
	docBuilder.append(kvp("mapType", mapType));
	docBuilder.append(kvp("isPrivate", isPrivate));
	docBuilder.append(kvp("nbPoteaux", static_cast<int>(nbPoteaux)));
	docBuilder.append(kvp("nbLignes", static_cast<int>(nbLignes)));
	docBuilder.append(kvp("nbMurs", static_cast<int>(nbMurs)));
	docBuilder.append(kvp("nbTeleporteurs", static_cast<int>(nbTeleporteurs)));
	docBuilder.append(kvp("password", password));
	docBuilder.append(kvp("Admin", static_cast<int>(Admin)));
	docBuilder.append(kvp("MapId", static_cast<int>(MapId)));
}

server::MapInfoDatabase::MapInfoDatabase(Database * database):BaseDatalist(database)
{
	BuildDatabaseFromCollection(GetCollectionName());
}

std::string server::MapInfoDatabase::GetCollectionName()
{
	return "MapInfos";
}

void server::MapInfoDatabase::GetObjectPropertiesFromBSON(bsoncxx::document::view docView, MapInfo* mapInfo)
{
	mapInfo->mapName = GetStringFromDoc(docView, "mapName");// .get_utf8().value.;
	mapInfo->mapType = docView["mapType"].get_int32();
	mapInfo->isPrivate = docView["isPrivate"].get_bool();
	mapInfo->nbPoteaux = docView["nbPoteaux"].get_int32();
	mapInfo->nbLignes = docView["nbLignes"].get_int32();
	mapInfo->nbMurs = docView["nbMurs"].get_int32();
	mapInfo->nbTeleporteurs = docView["nbTeleporteurs"].get_int32();
	mapInfo->password = GetStringFromDoc(docView, "password");
	mapInfo->Admin = docView["Admin"].get_int32();
	mapInfo->MapId = docView["MapId"].get_int32();
}
