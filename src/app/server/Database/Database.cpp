#include "Database.h"

#include <mongocxx\uri.hpp>

server::Database::Database()
{
	// instantiate mongo thread
	if (!_mongoInstantiated) {
		_mongoInstance = new mongocxx::instance();
		_mongoInstantiated = true;
	}

	// start the database work thread
	_doTasks = true;
	_taskThread = std::thread([this]() {
		while (_doTasks) {
			_tasksMutex.lock();
			if (_databaseTasks.size() > 0) {
				_databaseTasks.front()();
				_databaseTasks.pop();
			}
			_tasksMutex.unlock();
		}
		_databaseTasks.empty();
	});


	// connect to mongoLabs Database
	_mongoClient = mongocxx::client(mongocxx::uri("mongodb://runtime_server:projet3db@ds145118.mlab.com:45118"));
	mongocxx::database db = _mongoClient.database("projet3");
	
	_userDatabase = new UserDatabase(db.collection("Users"));
}

server::Database::~Database()
{
	if (_mongoInstantiated) {
		delete _mongoInstance;
	}

	_doTasks = false;
	while (!_taskThread.joinable()) {}
	_taskThread.join();
}

server::UserDatabase* server::Database::GetUserDatabase()
{
	return _userDatabase;
}

void server::Database::AddTask(Task newTask)
{
	_tasksMutex.lock();
	_databaseTasks.push(newTask);
	_tasksMutex.unlock();
}

mongocxx::instance* server::Database::_mongoInstance = nullptr; // need single instance of this running for client to work

bool server::Database::_mongoInstantiated = false;
