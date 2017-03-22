#include "BaseDatalist.h"

namespace server {
	class MapFileEntry:DatalistElement {
		// Inherited via DatalistElement
		virtual void WritePropertiesToBSON(bsoncxx::builder::basic::document & docBuilder) override;
	};

	class MapFileDatabase:BaseDatalist<MapFileEntry> {
		MapFileDatabase(Database* database);

		// Inherited via BaseDatalist
		virtual std::string GetCollectionName() override;
		virtual void GetObjectPropertiesFromBSON(bsoncxx::document::view docView, MapFileEntry * object) override;
	};
}