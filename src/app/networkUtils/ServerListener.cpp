#include "ServerListener.hpp"
#include <iostream>

using asio::ip::tcp;
using namespace Networking;

ServerListener::ServerListener(asio::io_service & ioService) : _acceptor(ioService)
{
}

void ServerListener::StartAccepting(short port)
{
	_acceptor.bind(tcp::endpoint(tcp::v4(), port));
	tcp::socket* socket = new tcp::socket(_acceptor.get_io_service());
	_acceptor.async_accept(*socket,
	[this, port, socket](std::error_code errorCode)
	{
		if (!errorCode)
		{
			Connection* connection = new Connection(socket);
			OnOtherConnected(connection);
			connection->Start();
			StartAccepting(port); // Keep the listener going
		}
		else
		{
			if (errorCode.value() != asio::error::operation_aborted) {
				Logger::LogError(errorCode);
			}
		}
	});
}

void ServerListener::StopAccepting() {
	_acceptor.close();
}