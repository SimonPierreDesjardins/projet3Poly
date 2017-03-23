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
		MapInfo(unsigned int id);

		std::string mapName;
		char mapType{ EDITION_MAP };
		bool isPrivate = false;
		unsigned int nbPoteaux = 0;
		unsigned int nbLignes = 0;
		unsigned int nbMurs = 0;
		std::string password; // password to join map if private
		unsigned int Admin = 0; // UserId of the map's creator
		unsigned int MapId = 0; // Id of the map json
		

		// Inherited via DatalistElement
		virtual void WritePropertiesToBSON(bsoncxx::builder::basic::document & docBuilder) override;
	};

	///<summary>Holds the list of users and their infos</summary>
	class MapInfoDatabase:public BaseDatalist<MapInfo>{
	
	public:
		MapInfoDatabase(Database* database);

	private:
		//Loads up map data from collection
		MapInfoDatabase(mongocxx::collection mapCollection);

		// Inherited via BaseDatalist
		virtual std::string GetCollectionName() override;
		virtual void GetObjectPropertiesFromBSON(bsoncxx::document::view docView, MapInfo* mapInfo) override;
	};
}

#endif // !__MAP_DATABASE_H