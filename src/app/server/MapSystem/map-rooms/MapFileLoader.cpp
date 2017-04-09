#include "MapFileLoader.h"

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
		*table->getProperty(Networking::SCALE) = { 2.0, 2.0, 1.0 };
		Entity* start = tree -> createEntity(1, table->entityId_); // create the start point
	}

	StartSaveThread();
}

server::MapFileLoader::~MapFileLoader()
{
	StopSaveThread();
}

void server::MapFileLoader::SetMapDirty()
{
	_mapDirty = true;
}

void server::MapFileLoader::PopulateTreeFromJSON(const std::string& json)
{
	rapidjson::StringStream stream(json.data());

	rapidjson::Document doc;
	doc.ParseStream(stream);

	const rapidjson::Value& tableJson = doc["table"];
	CreateEntities(tableJson, _entityTree->findEntity(0));
}

void server::MapFileLoader::CreateEntities(const rapidjson::Value& jsonNode, Entity* parent) {

	Entity* newEntity = _entityTree->createEntity(EntityTree::GetEntityType(jsonNode.FindMember("type")->value.GetString()), parent->entityId_);
	parent->addChild(newEntity);
	setEntityValues(newEntity, jsonNode);
	if (!jsonNode.HasMember("noeudsEnfants")) {
		return;
	}
	const rapidjson::Value& children = jsonNode.FindMember("noeudsEnfants")->value;
	for (rapidjson::Value::ConstValueIterator itr = children.Begin();
		itr != children.End(); ++itr) {
		CreateEntities(*itr, newEntity);
	}
}

void server::MapFileLoader::setEntityValues(Entity * target, const rapidjson::Value& jsonNode)
{
	// quick loading from iteration
	rapidjson::Value::ConstMemberIterator itr = jsonNode.MemberBegin() + 1;

	//Set relative position
	auto relPos = target->getProperty(Networking::RELATIVE_POSITION);
	relPos->x = itr->value.GetDouble(); 
	itr++;
	relPos->y = itr->value.GetDouble(); 
	itr++;
	relPos->z = itr->value.GetDouble(); 
	itr++;

	//Set Absolute Position
	auto absPos = target->getProperty(Networking::ABSOLUTE_POSITION);
	auto parentAbsPos = target->getParent()->getProperty(Networking::ABSOLUTE_POSITION);
	*absPos = *parentAbsPos + *relPos;

	target->getProperty(Networking::ROTATION)->z = itr->value.GetDouble();
	itr++;

	auto scaleValue = itr->value.GetDouble();
	auto scale = target->getProperty(Networking::SCALE);
	scale->x = scaleValue;
	scale->y = scaleValue;
	scale->z = scaleValue;

}

void server::MapFileLoader::StartSaveThread()
{
	_runSaveThread = true;
	_mapSavingThread = std::thread([this]() {
		while (_runSaveThread) {
			// I feel horrible, there must be a better way
			std::this_thread::sleep_for(std::chrono::seconds(2));
			// check again after sleep
			if (_mapDirty && _runSaveThread) {
				SaveTree();
			}
		}
	});
}

void server::MapFileLoader::StopSaveThread()
{
	_runSaveThread = false;
	while(!_mapSavingThread.joinable()){}
	_mapSavingThread.join();
}

void server::MapFileLoader::SaveTree() {
	rapidjson::StringBuffer buffer;
	auto writer = new rapidjson::Writer<rapidjson::StringBuffer>(buffer);

	writer->StartObject();
	writer->Key("table");

	_entityTree->lock();
	SaveEntityToJSON(_entityTree->findEntity(1), writer);
	_entityTree->unlock();

	writer->EndObject();

	_mapFile->MapData = buffer.GetString();
}

void server::MapFileLoader::SaveEntityToJSON(Entity * entity, rapidjson::Writer<rapidjson::StringBuffer>* writer)
{
	if (! ShouldSave(entity->entityType_)) {
		return;
	}

	writer->StartObject();

	// get type
	writer->Key("type");
	writer->String(entity->getTreeNode()->obtenirNom().c_str());

	//get positons
	auto pos = entity->getProperty(Networking::RELATIVE_POSITION);
	writer->Key("posX");
	writer->Double(pos->x);
	writer->Key("posY");
	writer->Double(pos->y);
	writer->Key("posZ");
	writer->Double(pos->z);
	// get rotation
	auto rot = entity->getProperty(Networking::ROTATION);
	writer->Key("angleRotation");
	writer->Double(rot->z);
	// get scale
	auto scale = entity->getProperty(Networking::SCALE);
	writer->Key("facteurEchelle");
	writer->Double(scale->x);
	//get children
	if (entity->getChildCount() > 0) {
		writer->Key("noeudsEnfants");
		writer->StartArray();
		for each (auto child in *entity)
		{
			SaveEntityToJSON(child.second, writer);
		}
		writer->EndArray();
	}

	writer->EndObject();
}

bool server::MapFileLoader::ShouldSave(char entityType)
{
	if ((entityType < EntityType::WHEEL_ENTITY && entityType != EntityType::DUPLICATION_ENTITY) ||
		(entityType > EntityType::AUDI_ENTITY && entityType != COIN_ENTITY)) {
		return true;
	}
	return false;
}
