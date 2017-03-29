#ifndef __MAP_FILE_LOADER_H
#define __MAP_FILE_LOADER_H

#include "EntityTree.h"
#include "Database\MapFileDatabase.h"
#include "rapidjson\document.h"


namespace server
{

class MapFileLoader
{
public:	
	// Takes an entity tree and a map file and loads the tree with present objects
	MapFileLoader(EntityTree* tree, MapFileEntry* mapFile);
	~MapFileLoader();

private:
	void PopulateTreeFromJSON(const std::string& json);
	void CreateEntities(rapidjson::Value::ConstValueIterator jsonNode, Entity* parent);
	void LoadTeleporters(const rapidjson::Value& jsonNode, Entity* parent);

	static char GetEntityType(const std::string& itemType);

	void StartSaveThread();
	void StopSaveThread();

	// have thread that does saving
	std::thread _mapSavingThread;
	MapFileEntry* _mapFile;
	
	// The tree that is tracked for saving purposes
	EntityTree* _entityTree;
};

}
#endif // __MAP_FILE_LOADER_H