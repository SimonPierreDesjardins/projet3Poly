#include "ServerListener.hpp"
#include <iostream>

using asio::ip::tcp;
using namespace Networking;

ServerListener::ServerListener(asio::io_service & ioService, short port) : _acceptor(ioService, tcp::endpoint(tcp::v4(), port))
{
}

void ServerListener::StartAccepting()
{
	tcp::socket* socket = new tcp::socket(_acceptor.get_io_service());
	_acceptor.async_accept(*socket,
	[this, socket](std::error_code errorCode)
	{
		if (!errorCode)
		{
			OnOtherConnected(new Connection(socket));
			StartAccepting(); // Keep the listener going
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