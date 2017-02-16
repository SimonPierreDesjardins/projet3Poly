#ifndef __NETWORK_FACTORY_H
#define __NETWORK_FACTORY_H


#include "Networking.h"

namespace Networking {


	class NetworkFactory{
		// Added Listener and resolver as friends so that they may create connection objects
		friend class ConnectionResolver;
		friend class ServerListener;

	public:
		///<summary>Builds a network resolver that can be used to connect to a given ip and port</summary>
		///<returns>An instance of a Resolver</returns>
		static ConnectionResolver& BuildResolver();

		///<summary>Builds a network listener that can listen for incomming connctions on a given port</summary>
		///<returns>An instance of a Listener</returns>
		static ServerListener& BuildListener();

		///<summary>Cleanly closes and deletes a connection and updates the associated io_service accordingly</summary>
		///<param>Pointer to the connection to be closed<param>
		static void Dispose(Connection* connection);

		///<summary>Cleanly closes and deletes a ConnectionResolver and updates the associated io_service accordingly</summary>
		///<param>Pointer to the ConnectionResolver to be closed<param>
		static void Dispose(ConnectionResolver* resolver);

		///<summary>Cleanly closes and deletes a ServerListener and updates the associated io_service accordingly</summary>
		///<param>Pointer to the ServerListener to be closed<param>
		static void Dispose(ServerListener* listener);


	private:

		static Connection& BuildConnection(tcp::socket* socket);

		class IOServiceHandler {
		public:
			static std::shared_ptr<asio::io_service> getIOService();

			static void IncrementUserCount();

			static void DecrementUserCount();

		private:
			static void StartIOThread();

			static void StopIOThread();
			
			static std::shared_ptr<asio::io_service> aios;

			static std::thread* aiosThread;

			static int userCount;
		};
	};
}


#endif // !__NETWORK_FACTORY_H