#include "MultiUserSession.h"

namespace server
{

int MultiUserSession::id_ = 0;

MultiUserSession::MultiUserSession()
{
	id_++;
}

MultiUserSession::~MultiUserSession()
{
}

}