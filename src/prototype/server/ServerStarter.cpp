#include "Networking.h"
#include <iostream>
#include <vector>
#include <thread>

using namespace Networking;

class ConnectionListener{
public : 

	ConnectionListener(ServerListener& listener) {
		HookListenerEvents(listener);
	}

	void MessageConnections(std::string message) {
		for each(auto connection in _connections) {
			connection->SendData(message);
		}
	}

private:

	/*class ConnectionHandler {
	public:
		ConnectionHandler(Connection* connection) {

		}
	};*/

	void HookListenerEvents(ServerListener& listener) {
		__hook(&ServerListener::OnOtherConnected, &listener, &ConnectionListener::OnNewConnection);
	}

	void OnNewConnection(Connection* connection) {
		std::cout << "New Connection!" << std::endl;
		HookConnectionEvents(connection);
		_connections.push_back(connection);
		connection->Start();
	}

	void HookConnectionEvents(Connection* connection) {
		__hook(&Connection::OnReceivedData, connection, &ConnectionListener::OnReceivedMessage);
	}

	void OnReceivedMessage(std::string& message) {
		std::cout << message << std::endl;
		MessageConnections(message);
	}

	std::vector<Connection*> _connections = std::vector<Connection*>();
};

int main(int argc, char* argv[]) {

	short portNumber = 5000;

	asio::io_service* aios = new asio::io_service();

	ServerListener serverListener(*aios, portNumber);
	ConnectionResolver resolver(*aios);

	ConnectionListener connector(serverListener);

	std::cout << "Starting listener" << std::endl;;
	serverListener.StartAccepting();

	std::thread aiosThread([aios]() {aios->run(); });

	//take commands from server

	std::string command = "";

	while (command != "exit") {
		std::getline(std::cin, command);
	}
}