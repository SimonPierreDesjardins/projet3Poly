#include "MapFileLoader.h"
#include "rapidjson\stringbuffer.h"
#include "rapidjson\writer.h"

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

void server::MapFileLoader::SetMapDirty()
{
	_mapDirty = true;
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
	
}

char server::MapFileLoader::GetEntityType(const std::string & itemType)
{
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

std::string server::MapFileLoader::GetEntityType(char itemType)
{
	//TODO: Implement this
	if (itemType == Networking::MessageStandard::ItemTypes::POST_ENTITY) {
		return "poteau";
	}
	if (itemType == Networking::MessageStandard::ItemTypes::START_ENTITY) {
		return "depart";
	}
	if (itemType == Networking::MessageStandard::ItemTypes::BLACK_LINE_ENTITY) {
		return "ligneNoire";
	}
	if (itemType == Networking::MessageStandard::ItemTypes::SEGMENT_ENTITY) {
		return "segment";
	}
	if (itemType == Networking::MessageStandard::ItemTypes::JUNCTION_ENTITY) {
		return "jonction";
	}
	if (itemType == Networking::MessageStandard::ItemTypes::WALL_ENTITY) {
		return "mur";
	}
	if (itemType == Networking::MessageStandard::ItemTypes::TELEPORT_ENTITY) {
		return "teleporteur";
	}
	return "";
}

void server::MapFileLoader::StartSaveThread()
{
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
	_runSaveThread = true;
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
	
	
	// visit tree with this method.
	std::function<void(Entity*)> visiterLambda;
	// save objects and continue visiting with this one
	std::function<void(Entity*)> saveObjectLambda;

	saveObjectLambda = [saveObjectLambda, visiterLambda, writer](Entity* entity) -> void{

		writer->StartObject();
		
		// get type
		writer -> Key("type");
		writer -> String(GetEntityType(entity->entityType_).c_str());

		//get positons
		auto pos = entity->getProperty(Networking::RELATIVE_POSITION);
		writer->Key("posX");
		writer->Double(pos->x());
		writer->Key("posY");
		writer->Double(pos->y());
		writer->Key("posZ");
		writer->Double(pos->z());
		// get rotation
		auto rot = entity->getProperty(Networking::ROTATION);
		writer->Key("angleRotation");
		writer->Double(rot -> z());
		// get scale
		auto scale = entity->getProperty(Networking::ROTATION);
		writer->Key("facteurEchelle");
		writer->Double(scale -> x());
		//get children
		if (entity->getChildCount() > 0) {
			writer->Key("noeudsEnfants");
			writer->StartArray();
			for each (auto child in *entity)
			{
				visiterLambda(child.second);
			}
			writer->EndArray();
		}

		writer->EndObject();
	};

	
	visiterLambda = [visiterLambda, saveObjectLambda, writer](Entity* entity) -> void {
		static Entity* previousTeleporter = nullptr;

		// check for teleporter, otherwise save normally
		if (entity->entityType_ != Networking::MessageStandard::ItemTypes::TELEPORT_ENTITY) {
			saveObjectLambda(entity);
		}
		// Teleporter saving methodology
		else {
			if (previousTeleporter == nullptr) {
				// save to previous teleporter
				previousTeleporter = entity;
			}
			else {
				//save both items in pairTeleporteurs
				writer->StartObject();
				writer->Key("PaireTeleporteurs");
				writer->StartArray();
				saveObjectLambda(previousTeleporter);
				saveObjectLambda(entity);
				writer->EndArray();
				writer->EndObject();
				previousTeleporter = nullptr;
			}
		}
	};

	writer->StartObject();
	visiterLambda(&(_entityTree->begin()->second));
	writer->EndObject();

	_mapFile->MapData = buffer.GetString();
}
