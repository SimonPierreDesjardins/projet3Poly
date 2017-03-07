#include "ChatSystem.h"
#include "NetworkStandard.h"

server::ChatSystem::ChatSession::ChatSession(std::string name)
{
	Name = name;
}

std::string server::ChatSystem::ChatSession::GetUserList()
{
	std::string userlistString = "";

	for (int i = 0; i < _userList.size(); ++i) {
		userlistString += _userList[i];
		if (i < _userList.size() - 1) {
			userlistString += ";";
		}
	}

	return std::string();
}

void server::ChatSystem::ChatSession::AddUser(std::string username)
{
	_userList.push_back(username);
}

void server::ChatSystem::ChatSession::RemoveUser(std::string username)
{
	
	auto end = _userList.end();

	for (auto iter = _userList.begin(); iter != end; iter++) {
		if (*iter == username) {
			_userList.erase(iter);
			break;
		}
	}

}

server::ChatSystem::ChatSystem()
{
	// Add the general channel to the system on creation
	_chatSessions.insert({ "General", std::move(ChatSession("General")) });
}

void server::ChatSystem::TreatUserJoin(User * user)
{
	// add user to general
	AddUserToChannel(user, "General");
}

void server::ChatSystem::TreatUserMessage(User * user, std::string & message)
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
		for each (auto user in _userList) {
			user.second->ForwardMessage(message);
		}
		break;
	}
}

void server::ChatSystem::TreatUserDisconnect(User * user)
{
	for each (auto channelPair in _chatSessions)
	{
		channelPair.second.RemoveUser(user->Info.UserName);
	}
}

void server::ChatSystem::ParseUserJoinRequest(User* user, std::string & message)
{
	// get the channel name out of the string
	std::string channelName = message.substr(message.find(';', Networking::MessageStandard::DATA_START));
	AddUserToChannel(user, std::move(channelName));
}

void server::ChatSystem::ParseUserLeaveRequest(User * user, std::string & message)
{
	std::string channelName = message.substr(message.find(';', Networking::MessageStandard::DATA_START));
	RemoveUserFromChannel(user, std::move(channelName));
}

void server::ChatSystem::AddUserToChannel(User * user, std::string channelName)
{
	// Check if channel exists
	if (_chatSessions.count(channelName) == 0) {
		// doesn't exist so create
		_chatSessions.insert({ channelName, std::move(ChatSession(channelName)) });
	}
	//add user to channel
	_chatSessions.at(channelName).AddUser(user->Info.UserName);
	user->ForwardMessage("cl" + _chatSessions.at(channelName).GetUserList());
}

void server::ChatSystem::RemoveUserFromChannel(User * user, std::string channelName)
{
	if (_chatSessions.count(channelName)>0) {
		_chatSessions.at(channelName).RemoveUser(user->Info.UserName);
	}
}
