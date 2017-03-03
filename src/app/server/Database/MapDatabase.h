#ifndef __MAP_DATABASE_H
#define __MAP_DATABASE_H

#include "../UserManagement/User.h"
#include "rapidjson\filewritestream.h"
#include "rapidjson\filereadstream.h"
#include "BaseDatalist.h"

namespace server {

	class MapInfo{
	public:
		std::string mapId;
		std::string mapName;
		bool isPrivate;
	};

	///<summary>Holds the list of users and their infos</summary>
	class MapDatabase:public BaseDatalist{
	
		//Class is built by the database class and database calls saving
		friend class Database;

	private:
		//Loads up user information from stream
		MapDatabase(std::string basePath);
	};
}

#endif // !__MAP_DATABASE_H