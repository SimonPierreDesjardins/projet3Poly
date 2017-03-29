#include "MapFileLoader.h"
#include "rapidjson\filereadstream.h"
#include "rapidjson\stringbuffer.h"

server::MapFileLoader::MapFileLoader(EntityTree* tree, MapFileEntry * mapFile)
{
	_mapFile = mapFile;

	_entityTree = tree;

	if (mapFile->MapData != "") {
		//load the file
	}
	else {
		Entity* table = tree -> createEntity(0, 0); // create the table
		Entity* start = tree -> createEntity(1, table->entityId_); // create the start point
	}

}

void server::MapFileLoader::PopulateTreeFromJSON(const std::string& json)
{
	rapidjson::StringStream stream(json.data());

	rapidjson::Document doc;
	doc.ParseStream(stream);

	Entity* table = _entityTree->createEntity(0, 0); // create the table

	if (!doc["table"].HasMember("noeudsEnfants")) {
		return;
	}
	const rapidjson::Value& enfantsTable = doc["table"]["noeudsEnfants"];
	for (rapidjson::Value::ConstValueIterator itr = enfantsTable.Begin();
		itr != enfantsTable.End(); ++itr) {
		CreateEntities(itr, table);
	}
}

void server::MapFileLoader::CreateEntities(rapidjson::Value::ConstValueIterator jsonNode, Entity* parent) {
	if (jsonNode->HasMember("PaireTeleporteurs"))
	{
		LoadTeleporters(jsonNode->FindMember("PaireTeleporteurs")->value, parent);
		return;
	}

	Entity* newEntity = _entityTree->createEntity(GetEntityType(jsonNode->FindMember("type")->value.GetString()), parent->entityId_);
	//TODO: have method that gets settings from json newEntity->fromJson(noeudJSON);
	parent->addChild(newEntity);
	if (!jsonNode->HasMember("noeudsEnfants")) {
		return;
	}
	const rapidjson::Value& children = jsonNode->FindMember("noeudsEnfants")->value;
	for (rapidjson::Value::ConstValueIterator itr = children.Begin();
		itr != children.End(); ++itr) {
		CreateEntities(itr, newEntity);
	}
}

void server::MapFileLoader::LoadTeleporters(const rapidjson::Value& jsonNode, Entity* parent)
{
	auto heyo = jsonNode.IsArray();
	Entity* tp1 = _entityTree->createEntity(GetEntityType(jsonNode[0].FindMember("type")->value.GetString()), parent->entityId_);
	// TODO: generate item properties from JSON noeud1->fromJson(&noeudJSON[0]);
	Entity* tp2 = _entityTree->createEntity(GetEntityType(jsonNode[1].FindMember("type")->value.GetString()), parent->entityId_);
	// TODO: generate item properties from JSON noeud2->fromJson(&noeudJSON[1]);

	// this is disgusting, either cast or deal with the code being bad
	//tp1->assignerTeleporteur(tp2);
	//tp2->assignerTeleporteur(tp1);
	parent->addChild(tp1);
	parent->addChild(tp2);
}

char server::MapFileLoader::GetEntityType(const std::string & itemType)
{
	//TODO: Implement this
	if (itemType == "") {
		return 0;
	}
	return 0;
}

void server::MapFileLoader::StartSaveThread()
{
	// TODO: implement this
}

void server::MapFileLoader::StopSaveThread()
{
	// TODO: impleent this
}

