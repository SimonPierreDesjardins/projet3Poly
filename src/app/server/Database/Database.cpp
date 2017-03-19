#include "Database.h"

#include <mongocxx\uri.hpp>

server::Database::Database()
{

	// instantiate mongo thread
	if (!_mongoInstantiated) {
		_mongoInstance = new mongocxx::instance();
		_mongoInstantiated = true;
	}

	// connect to mongoLabs Database
	_mongoClient = mongocxx::client(mongocxx::uri("mongodb://runtime_server:projet3db@ds145118.mlab.com:45118/?authSource=projet3"));
	_database = _mongoClient.database("projet3");

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

mongocxx::collection server::Database::GetCollection(std::string collectionName)
{
	return _database.collection(collectionName);
}

void server::Database::ReplaceEntry(std::string collectionName, server::DatalistElement* element)
{

	AddTask(
		[this, collectionName, element]() {
		bsoncxx::builder::stream::document docBuilder;
		mongocxx::options::update up;
		up.upsert(true);
		_database.collection(collectionName).replace_one(
			docBuilder << "ID" << static_cast<int>(element->GetId()) << bsoncxx::builder::stream::finalize,
			element->GetBSON(),
			up
		);
	});
}

void server::Database::AddTask(Task newTask)
{
	_tasksMutex.lock();
	_databaseTasks.push(newTask);
	_tasksMutex.unlock();
}

mongocxx::instance* server::Database::_mongoInstance = nullptr; // need single instance of this running for client to work

bool server::Database::_mongoInstantiated = false;
