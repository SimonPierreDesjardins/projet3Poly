#include "DatalistElement.h"

using bsoncxx::builder::basic::kvp;

bsoncxx::document::view_or_value server::DatalistElement::GetBSON()
{
	bsoncxx::builder::basic::document doc;
	doc.append(kvp("ID", static_cast<int>(GetId())));
	WritePropertiesToBSON(doc);
	return doc.extract();
}
