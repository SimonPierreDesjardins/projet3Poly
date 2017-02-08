#include "ChatSession.hpp"
#include <iostream>

bool ChatSession::Join(User * user)
{
	// try to add user
	if (_users.count(user->GetName()) == 0){
		_users.insert({ user->GetName(), user });
		HookUserEvents(user);
		return true;
	}
	return false;
}

void ChatSession::Leave(User * user)
{
	if (_users.count(user->GetName()) > 0) {
		_users.erase(user->GetName());
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
