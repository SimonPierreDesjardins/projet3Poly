#pragma once

#ifndef __CONNECTION_RESOLVER_HPP__
#define __CONNECTION_RESOLVER_HPP__

#include "asio.hpp"
#include "Connection.h"

using asio::ip::tcp;

namespace Networking{

	class ConnectionResolver {

	public:
		enum DebugLevel {
			NONE,
			ERROR_ONLY,
			CONNECTION_EVENTS,
			ALL
		};

		///<summary>Creates a connection type object to either listen to a port for connections or resolve a connection to an adress and port</summary>
		///<param>The OS' io service used for socket interfacing</param>
		///<param>the IpV4 adress to resolve too</param>
		///<param>The Port to resolve to</param>
		ConnectionResolver(asio::io_service & ioService);

		///<summary>Destroyer, takes care of closing and clearing used resources before connection object deletion</summary>
		~ConnectionResolver();

		///<summary>Attempts to resolve connection to the given ip and port. Calls OnConnectionResolved when it does.</summary>
		///<param>The ip adress to connect to</param>
		///<param>the port to connect to </param>
		void Resolve(std::string ipAdress, std::string port);


		__event void OnConnectionFailed();

		///<summary>Closes the connection and clears it for further use later</summary>
		void Close();


		//void SendData();

		static void SetDebugLevel(DebugLevel level);

		__event void OnConnectionResolved(Connection* connection);

		//__event void OnReceivedData();

	private:

		///<param>The OS' io service used for socket interfacing</param>
		tcp::resolver _resolver;

		bool _connectionEstablished; // true if polling has revealed that the player is currently online

		int _ping;



		//void ClearBuffers();

		//void SetConnectionState(bool connected);

		static DebugLevel _debugLevel;

		///<summary>Attempts to log an item according to its debug level</summary>
		///<param>The message to log</param>
		///<param>The debug level from which the message should show</param>
		void Log(std::string message, DebugLevel level);

		void LogError(std::string errorMessage);
		
	};
}

#endif
















		//hi i love u boo