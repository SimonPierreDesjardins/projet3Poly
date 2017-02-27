#include "ServerListener.hpp"
#include <iostream>

using asio::ip::tcp;
using namespace Networking;

ServerListener::ServerListener(asio::io_service & ioService, short port) : _acceptor(ioService, tcp::endpoint(tcp::v4(), port))
{
}

Networking::ServerListener::~ServerListener()
{
	_inDeletionProcess = true;

	_listenerLock.lock();
	_acceptor.close();
	_listenerLock.unlock();
}

void ServerListener::StartAccepting()
{
	_listenerLock.lock();
	tcp::socket* socket = new tcp::socket(_acceptor.get_io_service());
	_acceptor.async_accept(*socket,
	[this, socket](std::error_code errorCode)
	{
		if (_inDeletionProcess)
			return;

		_listenerLock.lock();

		if (!errorCode)
		{
			Logger::Log("Connection established", Logger::DebugLevel::CONNECTION_EVENTS);

			Connection* connection = NetworkObjects::BuildConnection(socket);
			OnOtherConnected(connection);
			connection->Start();

			_listenerLock.unlock();
			StartAccepting(); // Keep the listener going
		}
		else
		{
			socket->close();
			delete socket;
			if (errorCode.value() != asio::error::operation_aborted) {
				Logger::LogError(errorCode);
			}
			_listenerLock.unlock();
		}
	});
	_listenerLock.unlock();
}

void ServerListener::StopAccepting() {
	_acceptor.close();
}