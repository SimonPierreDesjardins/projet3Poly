#ifndef __DATABASE_H
#define __DATABASE_H
#include "UserDatabase.h"
#include <mongocxx\client.hpp>
#include <mongocxx\instance.hpp>


namespace server {
	///<summary> Instantaiates and sets up all database references</summary>
	class Database {
	public:
		Database();

		~Database();

		UserDatabase* GetUserDatabase();


	private:
		UserDatabase* _userDatabase;


		static bool _mongoInstantiated;

		static mongocxx::instance* _mongoInstance; // need single instance of this running for client to work

		mongocxx::client _mongoClient;
	};

}
#endif //!__DATABASE_H