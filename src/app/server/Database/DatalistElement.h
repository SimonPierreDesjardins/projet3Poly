#include "IdGenerator.h"
#include <bsoncxx\builder\stream\document.hpp>

namespace server{
	class DatalistElement {
	public:
		DatalistElement() {
			_id = IdGenerator::GenerateId();
		}

		uint32_t GetId() const {
			return _id;
		}

		bsoncxx::document::view_or_value GetBSON();

	protected:

		virtual void WritePropertiesToBSON(bsoncxx::builder::stream::document& docBuilder) = 0;

	private:
		uint32_t _id;
	};
}