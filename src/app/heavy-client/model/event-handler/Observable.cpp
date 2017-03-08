#include "NoeudAbstrait.h"

#include "Observer.h"

#include "Observable.h"

namespace event_handler
{

Observable::~Observable()
{
}


void Observable::notifyEntityCreated(NoeudAbstrait* noeud)
{
	observer_->onEntityCreated(noeud);
}

}