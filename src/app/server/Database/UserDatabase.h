#ifndef __USER_DATABASE_H
#define __USER_DATABASE_H

#include "rapidjson\filewritestream.h"
#include "rapidjson\filereadstream.h"
#include "BaseDatalist.h"
#include <vector>

namespace server {

	class UserInformation : public DatalistElement 
	{
	public:
		UserInformation();
		UserInformation(unsigned int id);
		std::string UserName;
		std::vector<std::string> ModifiedMaps; // list of maps this user modified
		std::vector<std::string> CreatedMaps; // list of maps this user created
		unsigned int NumberOfSimulations = 0; // number of simulations performed by the user
		unsigned int AchievementProgressList = 0; // id of the list holding this user's achievement progress
		float DistanceTraveled = 0.0f; // distance traveled during simulation by this user.

		// Inherited via DatalistElement
		virtual void WritePropertiesToBSON(bsoncxx::builder::basic::document & docBuilder) override;
	};

	///<summary>Holds the list of users and their infos</summary>
	class UserDatabase:public BaseDatalist<UserInformation>{
	public:
		//Loads up user information from stream
		UserDatabase(Database* database);

	protected:

		virtual std::string GetCollectionName();


		// Inherited via BaseDatalist
		virtual void GetObjectPropertiesFromBSON(bsoncxx::document::view docView, UserInformation* userInfo) override;

	};
}

#endif // !__USER_DATABASE_H