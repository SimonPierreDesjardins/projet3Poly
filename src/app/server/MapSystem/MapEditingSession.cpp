#include "MapEditingSession.h"

void server::MapEditingSession::TreatUserJoin(User * user)
{
	// Send map to connected user
}

void server::MapEditingSession::TreatUserMessage(User * user, std::string & message)
{
	for each(auto mapUser in _userList) {
		if (user->Info.GetId() != mapUser.first) {
			// for now, just replicate messages
			mapUser.second->ForwardMessage(message);
		}
	}
}

void server::MapEditingSession::TreatUserDisconnect(User * user)
{
}
