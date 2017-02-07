#include "ChatSession.hpp"

bool ChatSession::Join(User * user)
{
	// try to add user
	if (_users.count(user->GetName()) == 0){
		_users.insert({ user->GetName(), user });
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

void ChatSession::OnReceivedMessage(std::string & message)
{
	_messageQueue.push(message);

	if (_messageQueue.size() == 1) {
		DistributeMessages();
	}
}

void ChatSession::DistributeMessages()
{
	while (_messageQueue.size() > 0) {
		for each (auto user in _users) {
			user.second->Message(_messageQueue.front());
		}

		_messageQueue.pop();
	}
}
