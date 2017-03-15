#include "UserDatabase.h"


void server::UserDatabase::WriteObject(DatalistElement & element)
{
	//Use the writer to save individual user objects
}

server::UserDatabase::UserDatabase(const std::string basePath):BaseDatalist(basePath) {
	// normally Base Datalist builds list of users
}