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
		static ConnectionResolver* BuildResolver();

		///<summary>Builds a network listener that can listen for incomming connctions on a given port</summary>
		///<returns>An instance of a Listener</returns>
		static ServerListener* BuildListener(short port);


	private:

		static Connection* BuildConnection(tcp::socket* socket);

		class IOServiceHandler {
		public:
			std::shared_ptr<asio::io_service> getIOService();

			~IOServiceHandler();

			void IncrementUserCount();

			void DecrementUserCount();

		private:
			void StartIOThread();

			void StopIOThread();
			
			std::shared_ptr<asio::io_service> aios;

			std::thread* aiosThread;

			int userCount = 0;

			std::mutex _threadLock;
		};

		static IOServiceHandler iosHandler;
	};
}


#endif // !__NETWORK_FACTORY_H