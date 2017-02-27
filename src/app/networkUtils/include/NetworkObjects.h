#ifndef __NETWORK_FACTORY_H
#define __NETWORK_FACTORY_H


#include "Networking.h"

namespace Networking {

	class NetworkObjects{
		// Added Listener and resolver as friends since they are responsible for getting connection objects
		friend class ConnectionResolver;
		friend class ServerListener;

	public:

		/*
		NETWORK OBJECT CREATION
		*/
		///<summary>Builds a network resolver that can be used to connect to a given ip and port</summary>
		///<returns>An instance of a Resolver</returns>
		static ConnectionResolver* BuildResolver();

		///<summary>Builds a network listener that can listen for incomming connctions on a given port</summary>
		///<returns>An instance of a Listener</returns>
		static ServerListener* BuildListener(short port);

		/*
		NETWORK OBJECT DISPOSAL
		*/
		///<summary>Cleanly closes and deletes a connection and updates the associated io_service accordingly</summary>
		///<param>Pointer to the connection to be closed</param>
		static void Dispose(Connection* connection);

		///<summary>Cleanly closes and deletes a ConnectionResolver and updates the associated io_service accordingly</summary>
		///<param>Pointer to the ConnectionResolver to be closed</param>
		static void Dispose(ConnectionResolver* resolver);

		///<summary>Cleanly closes and deletes a ServerListener and updates the associated io_service accordingly</summary>
		///<param>Pointer to the ServerListener to be closed</param>
		static void Dispose(ServerListener* listener);


	private:

		static Connection* BuildConnection(tcp::socket* socket);

		// Object used to handle the IO Service thread
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


		// Object used to handle object disposal thread
		class Disposer {
		public:

			~Disposer();

			// Add a connection to ensure deletion at the end
			void AddConnectionToWatch(Connection* connection);

			void Dispose(Connection* connection);

			void Dispose(ConnectionResolver* resolver);

			void Dispose(ServerListener* listener);
		private:
			void StartThread();

			bool ObjectsLeftToDispose();

			std::queue<ServerListener*> _listenersToDelete;
			std::queue<ConnectionResolver*> _resolversToDelete;
			std::queue<Connection*> _connectionsToDelete;

			std::thread* _disposalThread;

			std::mutex _queueLock;

			bool _runDisposal = false;
		
			std::vector<Connection*> _liveConnections;
		};

		static Disposer _disposer;

		// Maintains list of live connections in order to dispose of them on termination
	};
}


#endif // !__NETWORK_FACTORY_H