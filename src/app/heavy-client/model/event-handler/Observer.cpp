#include "Observer.h"

namespace event_handler
{

int Observer::nextObservedId_ = 0;

Observer::~Observer()
{
	id_ = nextObservedId_++;
}

}