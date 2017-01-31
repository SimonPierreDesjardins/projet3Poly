#include "ConnectionResolver.hpp"
#include "ServerListener.hpp"
#include <iostream>

typedef ServerPrototype::ConnectionResolver ConnectionResolver;
typedef ServerPrototype::ServerListener ServerListener;

class Receiver{
	public:
		Receiver(ConnectionResolver &connection, ServerListener &listener) {
			__hook(&ServerListener::OnOtherConnected, &listener, &Receiver::OnConnectionEstablished);
			__hook(&ConnectionResolver::OnConnectionResolved, &connection, &Receiver::OnConnectionEstablished);
		}
	
		bool ReceivedEvent() {
			return _receivedEvent;
		}

	void OnConnectionEstablished(Connection connection) {
		std::cout << "Someone connected!" << std::endl;
		__hook(&Connection::OnReceivedData, &connection, &Receiver::ReceivedMessage);
		_connections.push_back(connection);
		connection.Start();
		_receivedEvent = true;
	}

	void Message(std::string message) {
		for each (auto connection in _connections)
		{
			connection.SendData(message);
		}
	}

	void ReceivedMessage(const char* data, size_t length) {
		std::cout << std::string(data, length) << std::endl;
	}

private:
	bool _receivedEvent = false;

	std::vector<Connection> _connections;
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

	ConnectionResolver connection(io_service);
	ServerListener listener(io_service, port);

	Receiver receiver(connection, listener);

	if (strcmp(argv[1], "listen") == 0) {
		listener.StartAccepting();
	}
	else {
		connection.Resolve(hostName, std::to_string(port));
	}

	io_service.run();

	while (!receiver.ReceivedEvent());

	std::string message = "";

	while (message != "exit") {
		std::cin >> message;
		receiver.Message(message);
	}

	return 0;
}

