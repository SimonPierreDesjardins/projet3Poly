#include "UserDatabase.h"


void server::UserDatabase::WriteObject(const server::UserInformation* element, bsoncxx::builder::stream::document& docBuilder)
{
	//Use the writer to save individual user objects
	docBuilder	<< "Username" << element -> UserName;
	auto inArray = docBuilder << "PrivateMaps" << bsoncxx::builder::stream::open_array;
	for (auto map : element -> privateMaps) {
		docBuilder << map;
	}
	inArray << bsoncxx::builder::stream::close_array;
}

server::UserDatabase::UserDatabase(mongocxx::collection& userCollection):BaseDatalist(userCollection) {
	// normally Base Datalist builds list of users
}