#ifndef __BASE_DATALIST_H
#define __BASE_DATALIST_H

#include "rapidjson\writer.h"
#include "rapidjson\filewritestream.h"
#include "rapidjson\filereadstream.h"
#include "rapidjson\document.h"
#include <map>

namespace server {

	class DatalistElement{
	public:
		virtual const std::string& GetId() = 0;
	};

	///<summary>Base implementation for lists of data in databases where elements extend DatalistElement</summary>
	class BaseDatalist{
	public:
		BaseDatalist(std::string filePath) {
			/*
			// open file and build data list
			_filePath = filePath;
			FILE* file;
			if (fopen_s(&file, _filePath.c_str(), "r") != 0) {
				//error occured, if file absent, ignore as file will be created on save. create default doc
				return;
			}
			else {
				//file opened, build database
				char readBuffer[65536];
				rapidjson::FileReadStream is(file, readBuffer, sizeof(readBuffer));
				doc.ParseStream(is);
				fclose(file);
			}

			if (doc.HasMember("elementList")) {
				rapidjson::Value elementList = doc["elementList"];
				for (rapidjson::Value::ConstValueIterator itr = elementList.Begin(); itr != elementList.End(); ++itr) {
					printf("%d ", itr->GetInt());

				}
			}
			else {
				doc.
			}
			// read data
			*/
		}

		~BaseDatalist() {
			SaveDataList(); // Make sure to save database before closing
		};
		
		//Adds users to the database
		//Should save user information on change
		void AddElement(DatalistElement& element) {
			_infoList.insert_or_assign(element.GetId(), element);
		}

		virtual std::map<std::string, DatalistElement&>& GetElements() {
			return _infoList;
		}

	protected:

		virtual void WriteObject(DatalistElement& element) = 0;

		//virtual DatalistElement& GetObject(rapidjson::Value value) = 0;

		/// Objet pour écrire dans un fichier.
		rapidjson::Writer<rapidjson::FileWriteStream>* writer;
		rapidjson::Document doc;

		//Saves user information into file
		void SaveDataList() {
			/*
			FILE* file;
			if (fopen_s(&file, _filePath.c_str(), "w") != 0) {
				//error occured, maybe create a file at filepath?
				return;
			}
			char writeBuffer[65536];
			rapidjson::FileWriteStream os(file, writeBuffer, sizeof(writeBuffer));
			writer = new rapidjson::Writer<rapidjson::FileWriteStream>(os);
			writer->StartObject();
			writer->Key("data");
			writer->StartArray();
			for each(auto infoPair in _infoList) {
				writer->StartObject();
				WriteObject(infoPair.second);
				writer->EndObject();
			}
			writer->EndArray();
			writer->EndObject();
			fclose(file);
			*/
		}

		// Map of info
		std::map<std::string, DatalistElement&> _infoList;

		// info to keep file close by
		std::string _filePath;
	};
}

#endif // !__BASE_DATALIST_H