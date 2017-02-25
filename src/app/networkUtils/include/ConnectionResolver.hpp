#pragma once

#ifndef __CONNECTION_RESOLVER_HPP__
#define __CONNECTION_RESOLVER_HPP__

#include "asio.hpp"
#include "Connection.h"

using asio::ip::tcp;

namespace Networking{

	class ConnectionResolver{
		friend class NetworkFactory;
		friend class NetworkDisposal;

	public:

		///<summary>Attempts to resolve connection to the given ip and port. Calls OnConnectionResolved when it does.</summary>
		///<param name='ipAdress'>The ip adress to connect to</param>
		///<param name='port'>the port to connect to </param>
		void Resolve(std::string ipAdress, std::string port);




		///<summary>Hook onto this event to receive resolved connections or errors in doing so</summary>
		///<param name='ipAdress'>The pointer to a new connection if successful</param>
		///<param name='port'>the errorCode, check if 0 to verify success</param>
		__event void OnConnection(Connection* connection, asio::error_code errorCode);

	private:
		ConnectionResolver(asio::io_service & ioService);

		~ConnectionResolver();

		///<summary>Closes the connection and clears it for further use later</summary>
		void Close();
		
		///<param>The OS' io service used for socket interfacing</param>
		tcp::resolver _resolver;

		bool _connectionEstablished; // true if polling has revealed that the player is currently online

		std::mutex _resolverLock;
		
	};
}

#endif
















		//hi i love u boo