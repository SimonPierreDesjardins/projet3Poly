#include "UserManagement\UserAuthLobby.h"
#include "ChatSystem\ChatSystem.h"
#include "MapSystem\MapListLobby.h"
#include <iostream>

void SetupServer() {

	std::cout << "Setting up server" << std::endl;

	Networking::Logger::SetDebugLevel(Networking::Logger::ALL);

	// create listener
	Networking::ServerListener* listener = Networking::NetworkObjects::BuildListener(5000);

	//Make map system

	// create ChatSystem
	server::ChatSystem chatSystem;

	// create MapSystem

	// create vector of systems to pass the user to when authenticated
	std::vector<server::MultiUserSystem*> newUserReceivers;
	newUserReceivers.push_back(&chatSystem);

	// create User auth system
	server::UserAuthLobby UserLobby(listener, newUserReceivers);

	// create UserLobby

	std::cout << "Starting listener" << std::endl;
	listener->StartAccepting();

	//listen for server commands
	std::string command = "";

	while (command != "exit") {
		std::getline(std::cin, command);
	}

	Networking::NetworkObjects::Dispose(listener);
}


// builds a resolver for connections purely intended for testing
void SetupTestClient() {
	std::cout << "Setting up resolver" << std::endl;

	Networking::ConnectionResolver* res = Networking::NetworkObjects::BuildResolver();
	res->Resolve("localhost", "5000");

	// listen for commands
	std::string command = "";

	while (command != "exit") {
		std::getline(std::cin, command);
	}

	Networking::NetworkObjects::Dispose(res);
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