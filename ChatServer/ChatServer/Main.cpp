#include "ConnectionResolver.hpp"
#include "ServerListener.hpp"
#include <iostream>

typedef ServerPrototype::ConnectionResolver ConnectionResolver;
typedef ServerPrototype::ServerListener ServerListener;

class Receiver{
	public:
		Receiver(ConnectionResolver &connection, ServerListener &listener) {
			__hook(&ServerListener::OnOtherConnected, &listener, &Receiver::OnConnectionReceived);
			__hook(&ConnectionResolver::OnConnectionResolved, &connection, &Receiver::OnConnectionResolved);
		}
	
		bool ReceivedEvent() {
			return _receivedEvent;
		}

	void OnConnectionReceived(Connection connection) {
		std::cout << "Someone connected!" << std::endl;
		_receivedEvent = true;
	}

	void OnConnectionResolved(Connection connection) {
		std::cout << "Connected!" << std::endl;
		_receivedEvent = true;
	}

private:
	bool _receivedEvent = false;

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
	}

	return 0;
}

