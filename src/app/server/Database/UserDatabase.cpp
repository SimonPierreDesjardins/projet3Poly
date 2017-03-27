#include "UserDatabase.h"

using bsoncxx::builder::basic::kvp;

std::string server::UserDatabase::GetCollectionName()
{
	return std::string("Users");
}

void server::UserDatabase::GetObjectPropertiesFromBSON(bsoncxx::document::view docView, UserInformation* userInfo)
{
	userInfo -> UserName = docView["Username"].get_utf8().value.to_string();
	
	// populate array
	for (auto element : docView["ModifiedMaps"].get_array().value) {
		userInfo-> ModifiedMaps.insert(element.get_int32());
	}
	for (auto element : docView["CreatedMaps"].get_array().value) {
		userInfo->CreatedMaps.insert(element.get_int32());
	}

	userInfo->AchievementProgressList = docView["AchievementProgressList"].get_int32();
	userInfo->NumberOfSimulations = docView["AchievementProgressList"].get_int32();
	userInfo->DistanceTraveled = docView["DistanceTraveled"].get_int32();

}

server::UserDatabase::UserDatabase(Database* db):BaseDatalist(db) {
	// Builds list of users
	BuildDatabaseFromCollection(GetCollectionName());
}

server::UserInformation::UserInformation():DatalistElement()
{
}

server::UserInformation::UserInformation(unsigned int id):DatalistElement(id)
{
}

void server::UserInformation::WritePropertiesToBSON(bsoncxx::builder::basic::document & docBuilder)
{
	//Use the writer to save individual user objects
	docBuilder.append(kvp("Username", UserName));
	// moded maps
	docBuilder.append(kvp("ModifiedMaps" ,
		[&docBuilder, this](bsoncxx::builder::basic::sub_array child) {
		for (auto map : ModifiedMaps) {
			child.append(static_cast<int>(map));
		}
	}
	));
	// created maps
	docBuilder.append(kvp("CreatedMaps",
		[&docBuilder, this](bsoncxx::builder::basic::sub_array child) {
		for (auto map : CreatedMaps) {
			child.append(static_cast<int>(map));
		}
	}
	));
	docBuilder.append(kvp("NumberOfSimulations", static_cast<int>(NumberOfSimulations)));
	docBuilder.append(kvp("AchievementProgressList", static_cast<int>(AchievementProgressList)));
	docBuilder.append(kvp("DistanceTraveled", static_cast<int>(DistanceTraveled)));
}
