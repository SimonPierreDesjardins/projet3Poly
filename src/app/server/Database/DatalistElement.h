#include "IdGenerator.h"
#include <bsoncxx\builder\basic\document.hpp>

namespace server{
	class DatalistElement {
	public:
		DatalistElement() {
			_id = IdGenerator::GenerateId();
		}

		DatalistElement(unsigned int id) {
			IdGenerator::SetNextId(id);
			_id = id;
		}

		uint32_t GetId() const {
			return _id;
		}

		void SetId(uint32_t value) {
			_id = value;
		}

		bsoncxx::document::view_or_value GetBSON();

	protected:

		virtual void WritePropertiesToBSON(bsoncxx::builder::basic::document& docBuilder) = 0;

	private:
		uint32_t _id;

		std::string _collectionName;
	};
}