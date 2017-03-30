#include "MapFileLoader.h"
#include "rapidjson\filereadstream.h"
#include "rapidjson\stringbuffer.h"

server::MapFileLoader::MapFileLoader(EntityTree* tree, MapFileEntry * mapFile)
{
	_mapFile = mapFile;

	_entityTree = tree;

	if (mapFile->MapData != "") {
		//load the file
		PopulateTreeFromJSON(mapFile->MapData);
	}
	else {
		Entity* table = tree -> createEntity(0, 0); // create the table
		Entity* start = tree -> createEntity(1, table->entityId_); // create the start point
	}

	StartSaveThread();
}

server::MapFileLoader::~MapFileLoader()
{
	StopSaveThread();
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
	setEntityValues(newEntity, jsonNode);
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

void server::MapFileLoader::setEntityValues(Entity * target, const rapidjson::Value::ConstValueIterator jsonNode)
{
	// quick loading from iteration
	rapidjson::Value::ConstMemberIterator itr = jsonNode->MemberBegin() + 1;

	//Set relative position
	Eigen::Vector3f* relPos = target->getProperty(Networking::RELATIVE_POSITION);
	relPos->x() = itr->value.GetDouble(); 
	itr++;
	relPos->y() = itr->value.GetDouble(); 
	itr++;
	relPos->z() = itr->value.GetDouble(); 
	itr++;

	//Set Absolute Position
	Eigen::Vector3f* absPos = target->getProperty(Networking::ABSOLUTE_POSITION);
	Eigen::Vector3f* parentAbsPos = target->getParent()->getProperty(Networking::ABSOLUTE_POSITION);
	*absPos = *parentAbsPos + *relPos;

	target->getProperty(Networking::ROTATION)->z() = itr->value.GetDouble();
	itr++;

	auto scaleValue = itr->value.GetDouble();
	Eigen::Vector3f* scale = target->getProperty(Networking::SCALE);
	scale->x() = scaleValue;
	scale->y() = scaleValue;
	scale->z() = scaleValue;

}

void server::MapFileLoader::LoadTeleporters(const rapidjson::Value& jsonNode, Entity* parent)
{
	auto jsonItr = jsonNode.Begin();

	Entity* tp1 = _entityTree->createEntity(GetEntityType(jsonItr->FindMember("type")->value.GetString()), parent->entityId_);
	parent->addChild(tp1);
	setEntityValues(tp1, jsonItr);

	jsonItr++;

	Entity* tp2 = _entityTree->createEntity(GetEntityType(jsonItr->FindMember("type")->value.GetString()), parent->entityId_);
	parent->addChild(tp2);
	setEntityValues(tp2, jsonItr);

	// this is disgusting, either cast or deal with the code being bad
	//tp1->assignerTeleporteur(tp2);
	//tp2->assignerTeleporteur(tp1);
	
}

char server::MapFileLoader::GetEntityType(const std::string & itemType)
{
	//TODO: Implement this
	if (itemType == "poteau") {
		return Networking::MessageStandard::ItemTypes::POST_ENTITY;
	}
	if (itemType == "depart") {
		return Networking::MessageStandard::ItemTypes::START_ENTITY;
	}
	if (itemType == "ligneNoire") {
		return Networking::MessageStandard::ItemTypes::BLACK_LINE_ENTITY;
	}
	if (itemType == "segment") {
		return Networking::MessageStandard::ItemTypes::SEGMENT_ENTITY;
	}
	if (itemType == "jonction") {
		return Networking::MessageStandard::ItemTypes::JUNCTION_ENTITY;
	}
	if (itemType == "mur") {
		return Networking::MessageStandard::ItemTypes::WALL_ENTITY;
	}
	if (itemType == "teleporteur") {
		return Networking::MessageStandard::ItemTypes::TELEPORT_ENTITY;
	}
	return -1;
}

void server::MapFileLoader::StartSaveThread()
{
	// TODO: implement this
}

void server::MapFileLoader::StopSaveThread()
{
	// TODO: impleent this
}

