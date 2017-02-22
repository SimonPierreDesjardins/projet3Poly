#include "ServerListener.hpp"
#include <iostream>

using asio::ip::tcp;
using namespace Networking;

ServerListener::ServerListener(asio::io_service & ioService) : _acceptor(ioService)
{
}

Networking::ServerListener::~ServerListener()
{
	_acceptor.close();
}

void ServerListener::StartAccepting(short port)
{
	_acceptor.open(tcp::v4());
	_acceptor.bind(tcp::endpoint(tcp::v4(), port));
	tcp::socket* socket = new tcp::socket(_acceptor.get_io_service());
	_acceptor.async_accept(*socket,
	[this, port, socket](std::error_code errorCode)
	{
		if (!errorCode)
		{
			Connection* connection = &(NetworkFactory::BuildConnection(socket));
			OnOtherConnected(connection);
			connection->Start();
			StartAccepting(port); // Keep the listener going
		}
		else
		{
			socket->close();
			delete socket;
			if (errorCode.value() != asio::error::operation_aborted) {
				Logger::LogError(errorCode);
			}
		}
	});
}

void ServerListener::StopAccepting() {
	_acceptor.close();
}