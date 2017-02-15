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

	void ShutdownServer() {
		for (int i = 0; i < _connectedUsers.size(); ++i) {
			delete _connectedUsers[i];
		}
		_connectedUsers.clear();
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
		std::cout << "User Disconnected!" << std::endl;
		if (user->GetAuthenticated()) {
			chatSession.Leave(user);
		}
		_connectedUsers.erase(std::remove(_connectedUsers.begin(), _connectedUsers.end(), user), _connectedUsers.end());
		//delete user;
	}

	std::vector<User*> _connectedUsers = std::vector<User*>();
	ChatSession chatSession = ChatSession();
};

void RunServer() {
	short portNumber = 5000;

	asio::io_service* aios = new asio::io_service();

	ServerListener serverListener(*aios, portNumber);
	ConnectionResolver resolver(*aios);

	UserReceiver receiver(serverListener);

	std::cout << "Starting listener" << std::endl;
	serverListener.StartAccepting();

	std::thread aiosThread([aios]() {aios->run(); });

	//take commands from server

	std::string command = "";

	while (command != "exit") {
		std::getline(std::cin, command);
	}

	//close everything
	serverListener.StopAccepting();
	receiver.ShutdownServer();

	aiosThread.join();
}

class sender {
public:
	sender(ConnectionResolver& resolver) {
		__hook(&ConnectionResolver::OnConnectionResolved, &resolver, &sender::OnConnectionEstablished);
	}

	~sender() {
		if (!_connection) {
			delete _connection;
		}
	}

	void OnConnectionEstablished(Connection* connection) {
		_connection = connection;
	}

	void Send(std::string message) {
		if (_connection) {
			_connection->SendData(message);
		}
	}

	bool IsConnected() {
		return _connection != NULL;
	}

	Connection* _connection;
};

void StartLocalListener() {

	asio::io_service* aios = new asio::io_service();

	ConnectionResolver resolver(*aios);

	sender _sender(resolver);

	resolver.Resolve("localhost", "5000");

	std::thread aiosThread([aios]() {aios->run(); });

	while (!_sender.IsConnected());

	std::string command = "";

	while (command != "exit") {
		std::getline(std::cin, command);
		_sender.Send(command);
	}

	delete &_sender;

	aiosThread.join();
}

int main(int argc, char* argv[]) {

	if (argc > 1) {
		StartLocalListener();
	}
	else {
		RunServer();
	}
}