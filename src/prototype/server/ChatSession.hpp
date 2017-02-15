#ifndef CHAT_SESSION_H
#define CHAT_SESSION_H




#include "User.hpp"
#include <map>

class ChatSession {

public:
	// Returns true if user successfully joined the chat room
	bool Join(User* user);

	void Leave(User* user);

	bool DoesUsernameExist(std::string& username);

private:

	void HookUserEvents(User* user);

	void UnhookUserEvents(User* user);

	void OnReceivedMessage(std::string& message);

	void DistributeMessages();

	std::string SerializeUserList();

	std::queue<std::string> _messageQueue = std::queue<std::string>();

	std::map<std::string, User*> _users = std::map<std::string, User*>();
};


#endif // !CHAT_SESSION_H