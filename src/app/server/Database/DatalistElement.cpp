#include "DatalistElement.h"

bsoncxx::document::view_or_value server::DatalistElement::GetBSON()
{
	bsoncxx::builder::stream::document doc;
	doc
		<< "ID" << static_cast<int>(GetId());
	WritePropertiesToBSON(doc);
	return doc << bsoncxx::builder::stream::finalize;
}
