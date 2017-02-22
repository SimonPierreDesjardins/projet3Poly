#pragma once
#ifndef __NETWORK_DISPOSAL_H
#define __NETWORK_DISPOSAL_H

#include "Networking.h"

namespace Networking {
	class NetworkDisposal {

	public:
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
		class Disposer {
		public:

			~Disposer();

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
		};

		static Disposer _disposer;
	};
}

#endif

