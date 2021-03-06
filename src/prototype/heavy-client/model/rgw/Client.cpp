#include "Client.h"
#include <iostream>

Client* Client::getClient()
{
	if (client == NULL)
		client = new Client();

	return client;
};

void Client::startConnection(std::string ipAdresse, std::string port)
{
	asio::io_service* aios = new asio::io_service();

	_resolver = new Networking::ConnectionResolver(*aios);

	__hook(&Networking::ConnectionResolver::OnConnectionResolved, _resolver, &Client::onConnectionEstablished);
	__hook(&Networking::ConnectionResolver::OnConnectionFailed, _resolver, &Client::onConnectionFailed);

	_resolver -> Resolve(ipAdresse, port);

	ioServiceThread = new std::thread([aios]() {aios->run(); });

	connectorRunning = true;
}

// Calling this 
void Client::stopConnection()
{
	if (!connectorRunning)
		return;

	//__unhook(&Networking::Connection::OnReceivedData, _connection, &Client::onMessageReceived);
	delete _connection;
	_connection = NULL;

	//__unhook(&Networking::ConnectionResolver::OnConnectionResolved, _resolver, &Client::onConnectionEstablished);
	//__unhook(&Networking::ConnectionResolver::OnConnectionFailed, _resolver, &Client::onConnectionFailed);
	delete _resolver;

	ioServiceThread -> join();
	delete ioServiceThread;

	connectorRunning = false;
}

void Client::sendMessage(std::string data)
{
	if (!connectorRunning)
		return;

	_connection->SendData(data);
}

bool Client::getConnectionFailureState()
{
	return failedConnection;
}

void Client::resetConnectionFailure()
{
	failedConnection = false;
}

bool Client::getConnectionState()
{
	return _connection != NULL;
}

int Client::getMessagesQueued()
{
	return message.size();
}

std::string Client::getMessage()
{
	std::string data;
	if (message.empty())
	{
		 data = "";
	}
	else
	{
		data = message.front();
		message.pop();
	}
	return data;
}


void Client::onMessageReceived(std::string& data)
{
	message.push(data);
}

void Client::onConnectionEstablished(Networking::Connection * connection)
{
	_connection = connection;
	__hook(&Networking::Connection::OnReceivedData, connection, &Client::onMessageReceived);
	connection->Start();
}

void Client::onConnectionFailed()
{
	// do whatever when connection fails
	failedConnection = true;
}



Client* Client::client;