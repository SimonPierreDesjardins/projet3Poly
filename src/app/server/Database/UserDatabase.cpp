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
	for (auto element : docView["PrivateMaps"].get_array().value) {
		userInfo-> PrivateMaps.push_back(element.get_utf8().value.to_string());
	}
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
	docBuilder.append(kvp("PrivateMaps" ,
		[&docBuilder, this](bsoncxx::builder::basic::sub_array child) {
		for (auto map : PrivateMaps) {
			child.append(map);
		}
	}
	));
}
