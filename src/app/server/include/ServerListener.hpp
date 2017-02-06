#pragma once
#include "asio.hpp"
#include "Networking.h"

using asio::ip::tcp;

namespace  Networking {

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