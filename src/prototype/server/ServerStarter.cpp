#include "Networking.h"
#include "User.hpp"
#include "ChatSession.hpp"
#include <iostream>
#include <map>
#include <thread>

using namespace Networking;

// Class that takes care of creating or deleting users as they come in and adding them to the chat session
class UserReceiver{
public : 

	UserReceiver(ServerListener& listener) {
		HookListenerEvents(listener);
	}

private:

	void HookListenerEvents(ServerListener& listener) {
		__hook(&ServerListener::OnOtherConnected, &listener, &UserReceiver::OnNewConnection);
	}

	void HookUserEvents(User* user) {
		__hook(&User::UserNameReceived, user, &UserReceiver::OnReceivedUsername);
		__hook(&User::UserDisconnected, user, &UserReceiver::OnUserDisconnected);
	}

	void OnNewConnection(Connection* connection) {
		std::cout << "New Connection!" << std::endl;
		User* user = new User(connection);
		HookUserEvents(user);
		connection->Start();
	}

	void OnReceivedUsername(User* user, std::string& username) {
		// user does not exist
		if (!chatSession.DoesUsernameExist(username)) {
			user->SetAuthenticated(true);
			chatSession.Join(user);
		}
		// user already exists
		else {
			user->SetAuthenticated(false);
		}
	}

	void OnUserDisconnected(User* user) {
		chatSession.Leave(user);
		delete user;
	}

	std::vector<User*> _connectedUsers = std::vector<User*>();
	ChatSession chatSession = ChatSession();
};

int main(int argc, char* argv[]) {

	short portNumber = 5000;

	asio::io_service* aios = new asio::io_service();

	ServerListener serverListener(*aios, portNumber);
	ConnectionResolver resolver(*aios);

	UserReceiver connector(serverListener);

	std::cout << "Starting listener" << std::endl;;
	serverListener.StartAccepting();

	std::thread aiosThread([aios]() {aios->run(); });

	//take commands from server

	std::string command = "";

	while (command != "exit") {
		std::getline(std::cin, command);
	}
}