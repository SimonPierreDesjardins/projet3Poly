#pragma once
#ifndef __SERVER_LISTENER_HPP__
#define __SERVER_LISTENER_HPP__

#include "asio.hpp"
#include "Networking.h"

using asio::ip::tcp;

namespace  Networking {

	class ServerListener
	{
		friend class NetworkFactory;
		friend class NetworkDisposal;

	public:
		void StartAccepting(short port);

		__event void OnOtherConnected(Connection* connectionToOther);

		void StopAccepting();

	private:
		ServerListener(asio::io_service & ioService);

		~ServerListener();

		tcp::acceptor _acceptor;

		void LogError(std::string errorMessage);
	};
}

#endif