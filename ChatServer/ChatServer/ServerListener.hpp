#pragma once
#include "Libraries\asio-1.10.8\include\asio.hpp"
#include "Connection.h"

using asio::ip::tcp;

namespace  ServerPrototype {

	class ServerListener
	{
	public:
		ServerListener(asio::io_service & ioService, short port);

		void StartAccepting();

		__event void OnOtherConnected(Connection connectionToOther);

	private:
		tcp::acceptor _acceptor;
		tcp::socket _socket;

		void LogError(std::string errorMessage);
	};
}