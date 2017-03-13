#ifndef __DATABASE_H
#define __DATABASE_H
#include "UserDatabase.h"

namespace server {
	///<summary> Instantaiates and sets up all database references</summary>
	class Database {
	public:
		Database();

		UserDatabase* GetUserDatabase();


	private:
		UserDatabase* _userDatabase;
	};


}
#endif //!__DATABASE_H