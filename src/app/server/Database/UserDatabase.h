#ifndef __USER_DATABASE_H
#define __USER_DATABASE_H

#include "rapidjson\filewritestream.h"
#include "rapidjson\filereadstream.h"
#include "BaseDatalist.h"
#include <vector>

namespace server {

	class UserInformation:public DatalistElement {
	public:
		std::string UserName;
		std::vector<std::string> privateMaps;
	};

	///<summary>Holds the list of users and their infos</summary>
	class UserDatabase:public BaseDatalist{
		friend class Database;

	protected:
		virtual void WriteObject(DatalistElement& element);

	private:
		//Loads up user information from stream
		UserDatabase(std::string basePath);
	};
}

#endif // !__USER_DATABASE_H