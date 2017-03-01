#include "UserDatabase.h"


void server::UserDatabase::WriteObject(DatalistElement & element)
{
	//Use the writer to save individual user objects
}

server::UserDatabase::UserDatabase(std::string basePath):BaseDatalist(basePath) {
	// normally Base Datalist builds list of users but we will do it here instead

}

std::string server::UserInformation::GetId()
{
	return UserName;
}
