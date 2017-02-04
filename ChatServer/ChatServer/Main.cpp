#include "ConnectionResolver.hpp"
#include "ServerListener.hpp"
#include <iostream>
#include <thread>

typedef NetworkPrototype::ConnectionResolver ConnectionResolver;
typedef NetworkPrototype::ServerListener ServerListener;
typedef NetworkPrototype::Connection Connection;

class Receiver{
	public:
		Receiver(ConnectionResolver &connection, ServerListener &listener) {
			__hook(&ServerListener::OnOtherConnected, &listener, &Receiver::OnConnectionEstablished);
			__hook(&ConnectionResolver::OnConnectionResolved, &connection, &Receiver::OnConnectionEstablished);
		}
	
		bool ReceivedEvent() {
			return _receivedEvent;
		}

	void OnConnectionEstablished(Connection* connection) {
		std::cout << "Connection Established" << std::endl;
		_connections.push_back(connection);
		__hook(&Connection::OnReceivedData, connection, &Receiver::ReceivedMessage);
		connection -> Start();
		_receivedEvent = true;
	}

	void Message(std::string message) {
		for each (auto connection in _connections) {
			connection -> SendData(message);
		}
	}

	void ReceivedMessage(std::string& message) {
		std::cout << std::string(message) << std::endl;
	}

private:
	bool _receivedEvent = false;

	std::vector<Connection*> _connections;
};

int main(int argc, char* argv[]) 
{

	// Set debug level

	ConnectionResolver::SetDebugLevel(ConnectionResolver::DebugLevel::ALL);

	for (int i = 0; i < argc; ++i) {
		std::cout << argv[i] << std::endl;
	}

	if (argc <= 1 || !((strcmp(argv[1] , "listen" ) == 0) || (strcmp(argv[1], "resolve") == 0))) {
		std::cout << "Must specify role by adding 'listen' or 'resolve' as program arguments" << std::endl;
		return 1;
	}

	int port = 8000;
	std::string hostName = "localhost";

	asio::io_service io_service;

	ConnectionResolver resolver(io_service);
	ServerListener listener(io_service, port);

	Receiver receiver(resolver, listener);

	if (strcmp(argv[1], "listen") == 0) {
		listener.StartAccepting();
	}
	else {
		resolver.Resolve(hostName, std::to_string(port));
	}

	asio::io_service* aios = &io_service;

	std::thread thread([aios](){aios -> run();});

	while (!receiver.ReceivedEvent());

	std::string message = "";

	while (message != "exit") {
		std::getline(std::cin, message);
		receiver.Message(message);
	}

	return 0;
}

