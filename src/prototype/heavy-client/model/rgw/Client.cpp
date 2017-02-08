#include "Client.h"

void Client::startConnection(std::string ipAdresse, std::string port)
{
	asio::io_service* aios = new asio::io_service();

	Networking::ConnectionResolver resolver(*aios);

	__hook(&Networking::ConnectionResolver::OnConnectionResolved, &resolver, &Client::onConnectionEstablished);

	resolver.Resolve(ipAdresse, port);

	ioServiceThread = std::thread([aios]() {aios->run(); });
}

void Client::stopConnection()
{
	if (!_connected)
		return;

	delete _connection;

	ioServiceThread.join();
}

void Client::sendMessage(std::string data)
{
	if (!_connected)
		return;

	_connection->SendData(data);
}

void Client::onMessageReceived(std::string & data)
{
	// Call your mom
}

void Client::onConnectionEstablished(Networking::Connection * connection)
{
	_connection = connection;
	__hook(&Networking::Connection::OnReceivedData, connection, &Client::onMessageReceived);
	_connected = true;
}
