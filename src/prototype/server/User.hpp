#ifndef USER_H
#define USER_H

#include "Networking.h"
using namespace Networking;

class User {
public:
	User(Connection* connection);

	void SetAuthenticated(bool authenticated);

	void Message(std::string& message);

	__event void UserSentMessage(std::string& message);

	__event void UserNameReceived(User* user, std::string& message);

	__event void UserDisconnected(User* user);

	std::string GetName();

private:
	void HookConnectionEvents(Connection* connection);

	void OnUserSentData(std::string& message);

	bool _userAuthenticated = false;

	std::string _name;

	Connection* _connection;
};


#endif // !USER_H