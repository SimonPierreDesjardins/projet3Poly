#include "include\NetworkObjects.h"

using namespace Networking;

ConnectionResolver* Networking::NetworkObjects::BuildResolver()
{
	iosHandler.IncrementUserCount();
	ConnectionResolver* resolver = new ConnectionResolver(*(iosHandler.getIOService()));

	return std::move(resolver);
}

ServerListener* Networking::NetworkObjects::BuildListener(short port)
{
	iosHandler.IncrementUserCount();
	ServerListener* serverListener = new ServerListener(*(iosHandler.getIOService()), port);

	return std::move(serverListener);
}

Connection* Networking::NetworkObjects::BuildConnection(tcp::socket* socket)
{
	Connection* connection = new Connection(socket);
	NetworkObjects::_disposer.AddConnectionToWatch(connection);
	iosHandler.IncrementUserCount();
	return std::move(connection);
}

std::shared_ptr<asio::io_service> Networking::NetworkObjects::IOServiceHandler::getIOService()
{
	if (aios == NULL) {
		aios = std::make_shared<asio::io_service>();
	}

	StartIOThread();

	return aios;
}

Networking::NetworkObjects::IOServiceHandler::~IOServiceHandler()
{
	StopIOThread();
}

void Networking::NetworkObjects::IOServiceHandler::IncrementUserCount()
{
	userCount++;
}

void Networking::NetworkObjects::IOServiceHandler::DecrementUserCount()
{
	if (userCount <= 0)
		return;

	userCount--;
	if (userCount == 0) {
		StopIOThread();
	}
}

void Networking::NetworkObjects::IOServiceHandler::StartIOThread()
{
	_threadLock.lock();
	if (aiosThread == NULL) {
		aiosThread = new std::thread([this]() {
			// keep running as long as there are users of the IOThread.
			while (userCount > 0 ) {
				aios->run();
			}
		});
	}
	_threadLock.unlock();
}

void Networking::NetworkObjects::IOServiceHandler::StopIOThread()
{
	_threadLock.lock();

	if (aiosThread != NULL && aios != NULL) {
		// Stop service and thread
		aios->stop();
		while (!(aiosThread->joinable()));
		aiosThread->join();

		// Clean pointer
		delete aiosThread;
		aiosThread = NULL;
	}

	_threadLock.unlock();
}

Networking::NetworkObjects::IOServiceHandler Networking::NetworkObjects::iosHandler;



void NetworkObjects::Dispose(Connection * connection)
{
	_disposer.Dispose(connection);
}

void NetworkObjects::Dispose(ConnectionResolver * resolver)
{
	_disposer.Dispose(resolver);
}

void NetworkObjects::Dispose(ServerListener * listener)
{
	_disposer.Dispose(listener);
}

Networking::NetworkObjects::Disposer::~Disposer()
{
	for each(auto connection in _liveConnections) {
		Dispose(connection);
	}

	_runDisposal = false;
	while (!_disposalThread->joinable());
	_disposalThread->join();
}

void Networking::NetworkObjects::Disposer::AddConnectionToWatch(Connection * connection)
{
	_liveConnections.push_back(connection);
}

void NetworkObjects::Disposer::Dispose(Connection * connection)
{
	_queueLock.lock();
	_connectionsToDelete.push(connection);
	StartThread();
	_queueLock.unlock();
}

void NetworkObjects::Disposer::Dispose(ConnectionResolver * resolver)
{
	_queueLock.lock();
	_resolversToDelete.push(resolver);
	StartThread();
	_queueLock.unlock();
}

void NetworkObjects::Disposer::Dispose(ServerListener * listener)
{
	_queueLock.lock();
	_listenersToDelete.push(listener);
	StartThread();
	_queueLock.unlock();
}

void NetworkObjects::Disposer::StartThread()
{
	if (_disposalThread != NULL) {
		return;
	}

	_runDisposal = true;

	_disposalThread = new std::thread([this]() {
		int deletionCount = 0;

		while (_runDisposal) {
			_queueLock.lock();

			deletionCount = 0;

			while (ObjectsLeftToDispose()) {

				// check for connections
				if (_connectionsToDelete.size() > 0) {
					Connection* deletedOne = _connectionsToDelete.front();
					_connectionsToDelete.pop();
					if (deletedOne != nullptr) {

						//look for connection in vector to remove it
						auto connectionIterator = _liveConnections.begin();
						while (connectionIterator > _liveConnections.end()) {
							if (*connectionIterator == deletedOne) {
								connectionIterator = _liveConnections.erase(connectionIterator);
							}
							else {
								connectionIterator++;
							}
						}

						// delete object
						delete deletedOne;
						deletedOne = nullptr;
						deletionCount++;
					}
				}

				// check for resolvers
				if (_resolversToDelete.size() > 0) {
					ConnectionResolver* deletedOne = _resolversToDelete.front();
					_resolversToDelete.pop();
					if (deletedOne != NULL) {
						delete deletedOne;
						deletedOne = NULL;
						deletionCount++;
					}
				}

				// check for listeners
				if (_listenersToDelete.size() > 0) {
					ServerListener* deletedOne = _listenersToDelete.front();
					_listenersToDelete.pop();
					if (deletedOne != NULL) {
						delete deletedOne;
						deletedOne = NULL;
						deletionCount++;
					}
				}

			}

			_queueLock.unlock();

			for (; deletionCount > 0; deletionCount--) {
				NetworkObjects::iosHandler.DecrementUserCount();
			}
		}
	});
}

bool Networking::NetworkObjects::Disposer::ObjectsLeftToDispose()
{
	return (_listenersToDelete.size() | _resolversToDelete.size() | _connectionsToDelete.size()) > 0;
}


Networking::NetworkObjects::Disposer Networking::NetworkObjects::_disposer;