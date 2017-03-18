#ifndef __MAP_DATABASE_H
#define __MAP_DATABASE_H

#include "../UserManagement/User.h"
#include "rapidjson\filewritestream.h"
#include "rapidjson\filereadstream.h"
#include "BaseDatalist.h"

enum MAP_TYPE
{
	// Utiliser les mêmes enums que sur le client lourd.
	SIMULATION_MAP = 1,
	EDITION_MAP = 2,
};

namespace server {

	class MapInfo : public DatalistElement{
	public:

		MapInfo();
		std::string mapName;
		char mapType{ EDITION_MAP };
		bool isPrivate;

		// Inherited via DatalistElement
		virtual void WritePropertiesToBSON(bsoncxx::builder::stream::document & docBuilder) override;
	};

	///<summary>Holds the list of users and their infos</summary>
	class MapDatabase:public BaseDatalist<MapInfo>{
	
		//Class is built by the database class and database calls saving
		friend class Database;

	private:
		//Loads up map data from collection
		MapDatabase(mongocxx::collection mapCollection);
	};
}

#endif // !__MAP_DATABASE_H