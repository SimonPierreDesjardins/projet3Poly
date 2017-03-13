#include "Database.h"

server::Database::Database()
{
	_userDatabase = new UserDatabase("internet path here");
}

server::UserDatabase* server::Database::GetUserDatabase()
{
	return _userDatabase;
}
