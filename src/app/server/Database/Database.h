#ifndef __DATABASE_H
#define __DATABASE_H
#include "UserDatabase.h"
#include <mongocxx\client.hpp>
#include <mongocxx\instance.hpp>
#include <queue>
#include <thread>
#include <mutex>


namespace server {
	///<summary> Instantaiates and sets up all database references</summary>
	class Database {

		typedef std::function<void()> Task;
		typedef std::queue<Task> TaskList;

	public:
		Database();

		~Database();

		UserDatabase* GetUserDatabase();

		void AddTask(Task newTask);

	private:
		UserDatabase* _userDatabase;


		static bool _mongoInstantiated;

		static mongocxx::instance* _mongoInstance; // need single instance of this running for client to work

		mongocxx::client _mongoClient;

		// Thread in charge of performing writes into database
		TaskList _databaseTasks;
		std::thread _taskThread;
		std::mutex _tasksMutex;
		bool _doTasks = false;
	};

}
#endif //!__DATABASE_H