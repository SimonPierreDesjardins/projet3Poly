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

	_resolver -> Resolve(ipAdresse, port);

	ioServiceThread = new std::thread([aios]() {aios->run(); });
}

void Client::stopConnection()
{
	if (!_connected)
		return;

	usernameUnique = false;
	delete _connection;
	ioServiceThread -> join();
	delete _resolver;
	delete ioServiceThread;
}

void Client::sendMessage(std::string data)
{
	if (!_connected)
		return;

	_connection->SendData(data);
}

bool Client::getConnectionState()
{
	return _connected;
}

std::string Client::getMessage()
{
	return message;
}

bool Client::getUsernameUnique()
{
	return usernameUnique;
}

void Client::clearMessage()
{
	message = "";
}

void Client::onMessageReceived(std::string& data)
{
	message = data;

	if (!usernameUnique)
		usernameUnique = (message == "asuc");
}

void Client::onConnectionEstablished(Networking::Connection * connection)
{
	_connection = connection;
	__hook(&Networking::Connection::OnReceivedData, connection, &Client::onMessageReceived);
	connection->Start();
	_connected = true;
}

Client* Client::client;