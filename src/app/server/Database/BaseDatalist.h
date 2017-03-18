#ifndef __BASE_DATALIST_H
#define __BASE_DATALIST_H

#include "IdGenerator.h"
#include <unordered_map>
#include <mongocxx\collection.hpp>
#include <bsoncxx\builder\stream\document.hpp>
#include "Database\Database.h"
//#include <bsoncxx\view_or_value.hpp>

namespace server {

	///<summary>Base implementation for lists of data in databases where elements extend DatalistElement</summary>
	template<class EType> class BaseDatalist{
		static_assert(std::is_base_of<DatalistElement, EType>::value, "Datalist template class is not derived from DatalistElement");
		
		typedef std::unordered_map<uint32_t, EType*> ElementMap;

	public:
		BaseDatalist(Database* database) {
			_database = database;
			// build list from contents of collection
			/*for (int i = 0; i < _collection.count(); i++) {
				_collection[1]
			}*/
		}
		
		//Adds elements to the database
		//Should save information on change
		void CreateEntry(EType* newEntry) {
			_infoList.insert_or_assign(newEntry -> GetId(), newEntry);
			// Write new entry to db
			_database->ReplaceEntry(GetCollectionName(), newEntry);
		}

		ElementMap& GetElements() {
			return _infoList;
		}

	protected:

		virtual std::string GetCollectionName() = 0;

		//virtual DatalistElement& GetObject(rapidjson::Value value) = 0;
		
		//Saves user information into file
		void SaveDataList() {

			for each (auto element in _infoList)
			{
				_database->ReplaceEntry(GetCollectionName(), element.second);
			}
		}

		// Map of info
		ElementMap _infoList;

		Database* _database;
	};
}

#endif // !__BASE_DATALIST_H