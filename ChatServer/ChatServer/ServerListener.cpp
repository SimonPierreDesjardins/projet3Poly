#include "ServerListener.hpp"
#include <iostream>

using asio::ip::tcp;
using namespace ServerPrototype;

ServerListener::ServerListener(asio::io_service & ioService, short port) : _acceptor(ioService, tcp::endpoint(tcp::v4(), port)),
_socket(ioService)
{
}

void ServerListener::StartAccepting()
{
	_acceptor.async_accept(_socket,
		[this](std::error_code errorCode)
	{
		if (!errorCode)
		{
			OnOtherConnected(Connection(&_socket));
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