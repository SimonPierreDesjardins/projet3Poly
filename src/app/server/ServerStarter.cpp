#include "UserManagement\UserAuthLobby.h"
#include "Database\Database.h"
#include "ChatSystem\ChatSystem.h"
#include "MapSystem.h"
#include "NetworkStandard.h"
#include <iostream>

void SetupServer() {

	std::cout << "Setting up server" << std::endl;

	Networking::Logger::SetDebugLevel(Networking::Logger::ALL);

	//Load up all databases
	server::Database database;

	// create ChatSystem
	server::ChatSystem chatSystem;

	// create MapSystem
	server::MapSystem mapSystem;

	// create vector of systems to pass the user to when authenticated
	std::vector<server::MultiUserSystem*> newUserReceivers;
	newUserReceivers.push_back(&chatSystem);
	newUserReceivers.push_back(&mapSystem);

	// create listener
	Networking::ServerListener* listener = Networking::NetworkObjects::BuildListener(5000);

	// create User auth system
	server::UserAuthLobby UserLobby(listener, database.GetUserDatabase() , newUserReceivers);

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


class ResolverContainer{
public:
	ResolverContainer() {
		_resolver = Networking::NetworkObjects::BuildResolver();
		__hook(&Networking::ConnectionResolver::OnConnection, _resolver, &ResolverContainer::OnConnectionEstablished);
		_resolver->Resolve("localhost", "5000");
	}

	void SendThroughConnection(std::string message) {
		_connection->SendData(Networking::MessageStandard::AddMessageLengthHeader(message));
	}

	~ResolverContainer() {
		Networking::NetworkObjects::Dispose(_resolver);
		Networking::NetworkObjects::Dispose(_connection);
	}

private:
	void OnConnectionEstablished(Networking::Connection* connection, asio::error_code error){
		_connection = connection;
		connection->hookOnReceivedMessage(&ResolverContainer::OnMessageReceived, this);
	}

	void OnMessageReceived(const std::string& message) {
		std::cout << message.substr(Networking::MessageStandard::SYSTEM) << std::endl;
	}

	Networking::ConnectionResolver* _resolver;

	Networking::Connection* _connection;
};

// builds a resolver for connections purely intended for testing
void SetupTestClient() {
	std::cout << "Setting up resolver" << std::endl;

	ResolverContainer container;

	// listen for commands
	std::string command = "";

	while (command != "exit") {
		std::getline(std::cin, command);
		container.SendThroughConnection(command);
	}
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