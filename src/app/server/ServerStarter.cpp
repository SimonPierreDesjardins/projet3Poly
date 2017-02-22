#include "UserManagement\UserAuthLobby.h"
#include <iostream>

void SetupServer(Networking::ServerListener* listener) {

	// create User auth system

	// create UserLobby

	// create ChatSystem

	// create MapSystem

}


int main(int argc, char* argv[]) {

	// Load up DB

	// build server structure

	std::cout << "Setting up server" << std::endl;

	Networking::ServerListener* listener = Networking::NetworkFactory::BuildListener();

	server::UserAuthLobby UserLobby(listener);

	// Give DB to server structure

	// Start listener

	std::cout << "Starting listener" << std::endl;
	listener->StartAccepting(5000);

	std::string command = "";

	while (command != "exit") {
		std::getline(std::cin, command);
	}

	Networking::NetworkDisposal::Dispose(listener);
}