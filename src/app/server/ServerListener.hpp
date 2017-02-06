#pragma once
#include "asio.hpp"
#include "Connection.h"

using asio::ip::tcp;

namespace  NetworkPrototype {

	class ServerListener
	{
	public:
		ServerListener(asio::io_service & ioService, short port);

		void StartAccepting();

		__event void OnOtherConnected(Connection* connectionToOther);

	private:
		tcp::acceptor _acceptor;

		void LogError(std::string errorMessage);
	};
}