#include "Database.h"

#include <mongocxx\uri.hpp>

server::Database::Database()
{

	if (!_mongoInstantiated) {
		_mongoInstance = new mongocxx::instance();
		_mongoInstantiated = true;
	}
	
	_mongoClient = mongocxx::client(mongocxx::uri("mongodb://runtime_server:projet3db@ds145118.mlab.com:45118"));

	mongocxx::database db = _mongoClient.database("projet3");
	
	_userDatabase = new UserDatabase("insert path here");
}

server::Database::~Database()
{
	if (_mongoInstantiated) {
		delete _mongoInstance;
	}
}

server::UserDatabase* server::Database::GetUserDatabase()
{
	return _userDatabase;
}

mongocxx::instance* server::Database::_mongoInstance = nullptr; // need single instance of this running for client to work

bool server::Database::_mongoInstantiated = false;
