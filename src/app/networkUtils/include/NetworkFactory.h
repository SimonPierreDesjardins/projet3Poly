#ifndef __NETWORK_FACTORY_H
#define __NETWORK_FACTORY_H


#include "Networking.h"

namespace Networking {

	class NetworkFactory{
		// Added Listener and resolver as friends since they are responsible for creating connection objects
		friend class ConnectionResolver;
		friend class ServerListener;
		friend class NetworkDisposal;

	public:
		///<summary>Builds a network resolver that can be used to connect to a given ip and port</summary>
		///<returns>An instance of a Resolver</returns>
		static ConnectionResolver& BuildResolver();

		///<summary>Builds a network listener that can listen for incomming connctions on a given port</summary>
		///<returns>An instance of a Listener</returns>
		static ServerListener& BuildListener();


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