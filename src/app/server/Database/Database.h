#ifndef __DATABASE_H
#define __DATABASE_H
#include <mongocxx\client.hpp>
#include <mongocxx\instance.hpp>
#include <queue>
#include <thread>
#include <mutex>

#include "DatalistElement.h"


namespace server {
	///<summary> Instantaiates and sets up all database references</summary>
	class Database {

		typedef std::function<void()> Task;
		typedef std::queue<Task> TaskList;

	public:
		Database();

		~Database();

		mongocxx::collection GetCollection(std::string collectionName);

		// Asynchronous Replace entry method that adds replacement task to a worker
		void ReplaceEntry(std::string collectionName, DatalistElement* element);

	private:

		void AddTask(Task newTask);

		static bool _mongoInstantiated;

		static mongocxx::instance* _mongoInstance; // need single instance of this running for client to work

		mongocxx::client _mongoClient;

		mongocxx::database _database;

		// Thread in charge of performing writes into database
		TaskList _databaseTasks;
		std::thread _taskThread;
		std::mutex _tasksMutex;
		bool _doTasks = false;
	};

}
#endif //!__DATABASE_H