#include "UserDatabase.h"

std::string server::UserDatabase::GetCollectionName()
{
	return std::string("Users");
}

server::UserDatabase::UserDatabase(Database* db):BaseDatalist(db) {
	// normally Base Datalist builds list of users
}

void server::UserInformation::WritePropertiesToBSON(bsoncxx::builder::stream::document & docBuilder)
{
	//Use the writer to save individual user objects
	docBuilder << "Username" << UserName;
	auto inArray = docBuilder << "PrivateMaps" << bsoncxx::builder::stream::open_array;
	for (auto map : PrivateMaps) {
		docBuilder << map;
	}
	inArray << bsoncxx::builder::stream::close_array;
}
