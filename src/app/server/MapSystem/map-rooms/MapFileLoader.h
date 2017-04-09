#ifndef __MAP_FILE_LOADER_H
#define __MAP_FILE_LOADER_H

#include "EntityTree.h"
#include "Database\MapFileDatabase.h"
#include "rapidjson\document.h"
#include "rapidjson\stringbuffer.h"
#include "rapidjson\writer.h"


namespace server
{

class MapFileLoader
{
public:	
	// Takes an entity tree and a map file and loads the tree with present objects
	MapFileLoader(EntityTree* tree, MapFileEntry* mapFile);
	~MapFileLoader();

	// tells the loader the ap as unsaved changes and will therefore save the map next time the thread wakes up
	void SetMapDirty();

private:
	void PopulateTreeFromJSON(const std::string& json);
	void CreateEntities(rapidjson::Value::ConstValueIterator jsonNode, Entity* parent);
	void setEntityValues(Entity* target, const rapidjson::Value::ConstValueIterator jsonNode);
	void LoadTeleporters(const rapidjson::Value& jsonNode, Entity* parent);

	void StartSaveThread();
	void StopSaveThread();

	void SaveTree();

	void VisiterMethod(Entity* entity, rapidjson::Writer<rapidjson::StringBuffer> * writer);
	void SaveEntityToJSON(Entity* entity, rapidjson::Writer<rapidjson::StringBuffer> * writer);
	bool EntitySavesNormally(char entityType);

	// have thread that does saving
	std::thread _mapSavingThread;
	MapFileEntry* _mapFile;

	bool _runSaveThread = false;
	bool _mapDirty = false;
	
	// The tree that is tracked for saving purposes
	EntityTree* _entityTree;

	//horrible teleporter implementation
	Entity* previousTeleporter_ = nullptr;

};

}
#endif // __MAP_FILE_LOADER_H