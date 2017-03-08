#include "MultiUserSession.h"

namespace server
{


MultiUserSession::MultiUserSession(char systemType)
	: Observer(systemType)
{
}

MultiUserSession::~MultiUserSession()
{
}

void MultiUserSession::addUser(User* user)
{

}

}