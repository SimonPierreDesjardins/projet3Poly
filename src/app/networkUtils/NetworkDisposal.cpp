#include "include\NetworkDisposal.h"

using namespace Networking;

void NetworkDisposal::Dispose(Connection * connection)
{
	_disposer.Dispose(connection);
}

void NetworkDisposal::Dispose(ConnectionResolver * resolver)
{
	_disposer.Dispose(resolver);
}

void NetworkDisposal::Dispose(ServerListener * listener)
{
	_disposer.Dispose(listener);
}

void NetworkDisposal::Disposer::Dispose(Connection * connection)
{
	_queueLock.lock();
	_connectionsToDelete.push(connection);
	StartThread();
	_queueLock.unlock();
}

void NetworkDisposal::Disposer::Dispose(ConnectionResolver * resolver)
{
	_queueLock.lock();
	_resolversToDelete.push(resolver);
	StartThread();
	_queueLock.unlock();
}

void NetworkDisposal::Disposer::Dispose(ServerListener * listener)
{
	_queueLock.lock();
	_listenersToDelete.push(listener);
	StartThread();
	_queueLock.unlock();
}

void NetworkDisposal::Disposer::StartThread()
{
	if (_disposalThread != NULL) {
		return;
	}
	_disposalThread = new std::thread([this]() {
		int deletionCount = 0;

		while (_runDisposal) {
			_queueLock.lock();

			deletionCount = 0;

			// check for connections
			if (_connectionsToDelete.size() > 0) {
				Connection* deletedOne = _connectionsToDelete.front();
				if (deletedOne != NULL) {
					delete deletedOne;
					deletedOne = NULL;
					deletionCount++;
				}
			}

			// check for resolvers
			if (_resolversToDelete.size() > 0) {
				ConnectionResolver* deletedOne = _resolversToDelete.front();
				if (deletedOne != NULL) {
					delete deletedOne;
					deletedOne = NULL;
					deletionCount++;
				}
			}

			// check for resolvers
			if (_listenersToDelete.size() > 0) {
				ServerListener* deletedOne = _listenersToDelete.front();
				if (deletedOne != NULL) {
					delete deletedOne;
					deletedOne = NULL;
					deletionCount++;
				}
			}

			_queueLock.unlock();

			for (; deletionCount > 0; deletionCount--) {
				NetworkFactory::IOServiceHandler::DecrementUserCount();
			}

		}
	});
}
