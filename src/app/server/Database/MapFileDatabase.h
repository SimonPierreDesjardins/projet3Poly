#ifndef __MAP_FILE_DB_H
#define __MAP_FILE_DB_H

#include "BaseDatalist.h"

namespace server {
	class MapFileEntry:public DatalistElement {
	public: 
		MapFileEntry(unsigned int id);
		MapFileEntry();

		std::string MapData; // contains the JSON of the map

		// Inherited via DatalistElement
		virtual void WritePropertiesToBSON(bsoncxx::builder::basic::document & docBuilder) override;
	};

	class MapFileDatabase:public BaseDatalist<MapFileEntry> {
	public:
		MapFileDatabase(Database* database);

	protected:
		// Inherited via BaseDatalist
		virtual std::string GetCollectionName() override;
		virtual void GetObjectPropertiesFromBSON(bsoncxx::document::view docView, MapFileEntry * object) override;
	};
}

#endif // !__MAP_FILE_DB_H

