#ifndef __BASE_DATALIST_H
#define __BASE_DATALIST_H

#include "IdGenerator.h"
#include <unordered_map>
#include <mongocxx\collection.hpp>
#include <bsoncxx\builder\stream\document.hpp>
#include "Database\Database.h"
#include <bsoncxx\json.hpp>
#include <thread>

namespace server {

	///<summary>Base implementation for lists of data in databases where elements extend DatalistElement</summary>
	template<class EType> class BaseDatalist{
		static_assert(std::is_base_of<DatalistElement, EType>::value, "Datalist template class is not derived from DatalistElement");
		
		typedef std::unordered_map<uint32_t, EType*> ElementMap;

	public:
		BaseDatalist(Database* database) {
			_database = database;
		}

		~BaseDatalist() {
			_runUpdateThread = false;
			while (!_updateThread.joinable()) {
			}
			_updateThread.join();
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

		void BuildDatabaseFromCollection(std::string CollectionName) {
			auto collection = _database->GetCollection(GetCollectionName());
			for (auto doc : collection.find((bsoncxx::builder::basic::document{}).extract())) {
				EType* obj = ObjectFromBSON(doc);
				_infoList.insert_or_assign(obj->GetId(), obj);
			}
			// Start updating thread that calls an update task for all entries once per second;
			RunDatabaseSaveThread();
		}

		virtual std::string GetCollectionName() = 0;

		// Extracts an object of template type from the document and manages Id tracking
		EType* ObjectFromBSON(bsoncxx::document::view docView) {
			unsigned int objectId = docView["ID"].get_int32();
			EType* object = new EType(objectId);
			GetObjectPropertiesFromBSON(docView, object);
			return object;
		}

		// Gets all non-Id elements from the document before adding the object to the item list
		virtual void GetObjectPropertiesFromBSON(bsoncxx::document::view docView, EType* object) = 0;
		
		//converts list of bytes to string for storage of info to avoid encoding shenanigans
		std::string GetStringFromDoc(bsoncxx::document::view docView, std::string key) {
			auto stringElement = docView[key].get_utf8().value.to_string();
			return stringElement;
		}

		//Saves user information into file
		void RunDatabaseSaveThread() {
			if (_runUpdateThread) {
				return;
			}

			_runUpdateThread = true;

			_updateThread = std::thread([this]() {
				while (_runUpdateThread) {
					// sleep thread
					std::this_thread::sleep_for(std::chrono::seconds(2));
					// update DB elements
					for each (auto element in _infoList)
					{
						if (!_runUpdateThread) {
							break;
						}

						_database->ReplaceEntry(GetCollectionName(), element.second);
					}
				}
			});
		}

		// Map of info
		ElementMap _infoList;

		Database* _database;

		std::thread _updateThread;
		bool _runUpdateThread = false;
	};
}

#endif // !__BASE_DATALIST_H