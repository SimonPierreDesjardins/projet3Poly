#include "User.hpp"

	User::User(Connection* connection) {
		_connection = connection;
		HookConnectionEvents(connection);
	}

	void User::SetAuthenticated(bool authenticated) {
		if (authenticated && !_userAuthenticated) {
			// User has been newly authenticated, do stuff according to that
			_connection->SendData("asuc");
		}
		else if (!authenticated) {
			//Send authentication error to user
			_connection->SendData("aerr");
		}

		_userAuthenticated = authenticated;
	}

	void User::Message(std::string & message)
	{
		_connection->SendData(message);
	}


	std::string User::GetName()
	{
		return _name;
	}

	void User::HookConnectionEvents(Connection* connection) {
		__hook(&Connection::OnReceivedData, connection, &User::OnUserSentData);
	}

	void User::OnUserSentData(std::string & message)
	{
		if (message[0] == 'u') {
			// user sent their username
			_name = message.substr(1);
			UserNameReceived(this, message.substr(1));
		}
		else if (message[0] == 'm' && _userAuthenticated) {
			// user sent a message
			UserSentMessage(message.substr(1));
		}
	}

