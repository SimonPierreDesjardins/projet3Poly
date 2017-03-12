#include "ChatSystem.h"
#include "NetworkStandard.h"

server::ChatSystem::ChatSession::ChatSession(std::string name)
{
	Name = name;
}

std::string server::ChatSystem::ChatSession::GetUserList()
{
	std::string userlistString = "";

	for (int i = 0; i < UserList.size(); ++i) {
		userlistString += UserList[i]->Info.UserName;
		if (i < UserList.size() - 1) {
			userlistString += ";";
		}
	}

	return userlistString;
}

bool server::ChatSystem::ChatSession::AddUser(User* user)
{
	UserList.push_back(user);
	return true;
}

bool server::ChatSystem::ChatSession::RemoveUser(User* user)
{
	auto end = UserList.end();

	for (auto iter = UserList.begin(); iter != end; iter++) {
		if (*iter == user) {
			UserList.erase(iter);
			return true;
		}
	}
	return false;
}

server::ChatSystem::ChatSystem()
{
	// Add the general channel to the system on creation
	_chatSessions.insert({ "General", std::move(ChatSession("General")) });
}

char server::ChatSystem::GetSystemType()
{
	return _systemType;
}

void server::ChatSystem::TreatUserJoin(User * user)
{
	// send user the channel list
	user->ForwardMessage(Networking::MessageStandard::AddMessageLengthHeader("cl" + GetChannelList()));

	// add user to general
	AddUserToChannel(user, "General");
}

void server::ChatSystem::TreatUserMessage(User * user, const std::string & message)
{
	// checkmessage at command index
	switch (message[Networking::MessageStandard::COMMAND]) {
	case 'j':
		ParseUserJoinRequest(user, message);
		break;
	case 'q':
		ParseUserLeaveRequest(user, message);
		break;
	case 'm':
		// Send message back to everyone
		for each (auto user in _connectedUserList) {
			user.second->ForwardMessage(message);
		}
		break;
	}
}

void server::ChatSystem::TreatUserDisconnect(User * user)
{
	for each (auto channelPair in _chatSessions)
	{
		if (channelPair.second.RemoveUser(user)) {
			BroadcastUserList(channelPair.first);
		}
	}
}

std::string server::ChatSystem::GetChannelList()
{
	std::string channelList = "";

	int i = 0, count = _chatSessions.size();
	for each (auto sessionNamePair in  _chatSessions) {
		channelList += sessionNamePair.first;
		if (i < count - 1) {
			channelList += ";";
		}
		++i;
	}

	return channelList;
}

void server::ChatSystem::ParseUserJoinRequest(User* user, const std::string & message)
{
	// get the channel name out of the string
	std::string channelName = message.substr(message.find(';', Networking::MessageStandard::DATA_START));
	AddUserToChannel(user, std::move(channelName));
}

void server::ChatSystem::ParseUserLeaveRequest(User * user, const std::string & message)
{
	std::string channelName = message.substr(message.find(';', Networking::MessageStandard::DATA_START));
	RemoveUserFromChannel(user, std::move(channelName));
}

void server::ChatSystem::AddUserToChannel(User * user, const std::string& channelName)
{
	// Check if channel exists
	if (_chatSessions.count(channelName) == 0) {
		// doesn't exist so create
		_chatSessions.insert({ channelName, std::move(ChatSession(channelName)) });
	}
	//add user to channel
	_chatSessions.at(channelName).AddUser(user);

	std::string userListMessage = Networking::MessageStandard::AddMessageLengthHeader("cu" + ';' + channelName + ';' + _chatSessions.at(channelName).GetUserList());

	BroadcastUserList(channelName);
}

void server::ChatSystem::RemoveUserFromChannel(User * user, const std::string& channelName)
{
	if (_chatSessions.count(channelName)>0) {
		_chatSessions.at(channelName).RemoveUser(user);
	}
	BroadcastUserList(channelName);
}

void server::ChatSystem::BroadcastUserList(std::string channelName)
{
	std::string userListMessage = Networking::MessageStandard::AddMessageLengthHeader("cu" + ';' + channelName + ';' + _chatSessions.at(channelName).GetUserList());

	// send userlist o every user in that channel
	for each (auto user in _chatSessions.at(channelName).UserList) {
		user->ForwardMessage(userListMessage);
	}
}
