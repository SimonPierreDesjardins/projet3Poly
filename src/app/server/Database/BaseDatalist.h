#ifndef __BASE_DATALIST_H
#define __BASE_DATALIST_H

#include "IdGenerator.h"
#include <unordered_map>
#include <mongocxx\collection.hpp>
#include <bsoncxx\builder\stream\document.hpp>

namespace server {

	class DatalistElement{
	public:
		DatalistElement() {
			_id = IdGenerator::GenerateId();
		}

		uint32_t GetId() const {
			return _id;
		}

	private:
		uint32_t _id;
	};

	///<summary>Base implementation for lists of data in databases where elements extend DatalistElement</summary>
	template<class EType> class BaseDatalist{
		static_assert(std::is_base_of<DatalistElement, EType>::value, "Datalist template class is not derived from DatalistElement");
		
		typedef std::unordered_map<uint32_t, EType*> ElementMap;

	public:
		BaseDatalist(mongocxx::collection& container):_collection(container) {
			// build list from contents of collection
			/*for (int i = 0; i < _collection.count(); i++) {
				_collection[1]
			}*/
		}

		~BaseDatalist() {
			SaveDataList(); // Make sure to save database before closing
		};
		
		//Adds elements to the database
		//Should save information on change
		void CreateEntry(EType* newEntry) {
			_infoList.insert_or_assign(newEntry -> GetId(), newEntry);
		}

		ElementMap& GetElements() {
			return _infoList;
		}

	protected:

		virtual void WriteObject(const EType* element, bsoncxx::builder::stream::document& objectBuilder) = 0;

		//virtual DatalistElement& GetObject(rapidjson::Value value) = 0;
		
		//Saves user information into file
		void SaveDataList() {
			
			std::vector<bsoncxx::document::value> documents;

			bsoncxx::builder::stream::document docStream;

			for each (auto element in _infoList)
			{
				docStream << "ID" << static_cast<int>(element.first);
				WriteObject(element.second, docStream);
				documents.push_back(docStream << bsoncxx::builder::stream::finalize);
				// TODO: enque tasks into database class
			}
		}

		// Map of info
		ElementMap _infoList;

		mongocxx::collection& _collection;
	};
}

#endif // !__BASE_DATALIST_H