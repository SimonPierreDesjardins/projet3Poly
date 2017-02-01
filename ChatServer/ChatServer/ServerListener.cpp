#include "ServerListener.hpp"
#include <iostream>

using asio::ip::tcp;
using namespace NetworkPrototype;

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
			OnOtherConnected(Connection(std::shared_ptr<tcp::socket>(socket)));
			StartAccepting(); // Keep the listener going
		}
		else
		{
			LogError(errorCode.message());
		}
	});
}

void ServerListener::LogError(std::string errorMessage) {
		std::cout << "Connection Error : " << errorMessage << std::endl;
}