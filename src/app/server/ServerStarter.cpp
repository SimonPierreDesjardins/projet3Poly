#include "UserManagement\UserAuthLobby.h"
#include <iostream>

void SetupServer() {

	std::cout << "Setting up server" << std::endl;

	Networking::Logger::SetDebugLevel(Networking::Logger::ALL);

	// create listener
	Networking::ServerListener* listener = Networking::NetworkFactory::BuildListener(5000);

	// create User auth system
	server::UserAuthLobby UserLobby(listener);

	// create UserLobby

	// create ChatSystem

	// create MapSystem

	std::cout << "Starting listener" << std::endl;
	listener->StartAccepting();

	//listen for server commands
	std::string command = "";

	while (command != "exit") {
		std::getline(std::cin, command);
	}

	Networking::NetworkDisposal::Dispose(listener);
}


// builds a resolver for connections purely intended for testing
void SetupTestClient() {
	std::cout << "Setting up resolver" << std::endl;

	Networking::ConnectionResolver* res = Networking::NetworkFactory::BuildResolver();
	res->Resolve("localhost", "5000");

	// listen for commands
	std::string command = "";

	while (command != "exit") {
		std::getline(std::cin, command);
	}

	Networking::NetworkDisposal::Dispose(res);
}

int main(int argc, char* argv[]) {

	if (argc > 1 && std::string(argv[1]) == "-r") {
		// create a resolver on the port for testing purposes
		SetupTestClient();
	}
	else {
		// build the server
		SetupServer();
	}
}