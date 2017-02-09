#include "ChatSession.hpp"
#include <iostream>

bool ChatSession::Join(User * user)
{
	std::string username = user->GetName();
	// try to add user
	if (_users.count(username) == 0){
		_users.insert({ username, user });
		HookUserEvents(user);
		std::cout << "Added user " << username << " to chat." << std::endl;
		OnReceivedMessage(SerializeUserList());
		return true;
	}
	return false;
}

void ChatSession::Leave(User * user)
{
	std::string username = user->GetName();

	if (_users.count(username) > 0) {
		_users.erase(username);
		OnReceivedMessage(SerializeUserList());
		std::cout << "User " << username << " left chat." << std::endl;
	}
}

bool ChatSession::DoesUsernameExist(std::string & username)
{
	return _users.count(username) > 0;
}

void ChatSession::HookUserEvents(User * user)
{
	__hook(&User::UserSentMessage, user, &ChatSession::OnReceivedMessage);
}

void ChatSession::UnhookUserEvents(User * user)
{
	__unhook(&User::UserSentMessage, user, &ChatSession::OnReceivedMessage);
}

void ChatSession::OnReceivedMessage(std::string & message)
{
	_messageQueue.push(message);

	if (_messageQueue.size() == 1) {
		DistributeMessages();
	}
}

void ChatSession::DistributeMessages()
{
	std::string message = _messageQueue.front();
	std::cout << message << std::endl;
	while (_messageQueue.size() > 0) {
		for each (auto user in _users) {
			user.second->Message(message);
		}
		_messageQueue.pop();
	}
}

std::string ChatSession::SerializeUserList()
{
	std::string userList = "r";
	for each (auto user in _users) {
		userList += user.first + ";";
	}
	userList.erase(userList.size() - 1);
	return userList;
}
