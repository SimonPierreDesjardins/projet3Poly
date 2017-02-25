#include "Networking.h"
#include <iostream>

using namespace Networking;

ConnectionResolver::ConnectionResolver(asio::io_service& ioService):
	_resolver(ioService)
{
}

ConnectionResolver::~ConnectionResolver() {
	_resolverLock.lock();
	Close();
	_resolverLock.unlock();
}

void ConnectionResolver::Resolve(std::string ipAddress, std::string port) {
	_resolverLock.lock();

	tcp::resolver::query query(ipAddress, port);
	auto endPointIterator = _resolver.resolve(query);
	tcp::resolver::iterator end;

	tcp::socket* socket = new tcp::socket(_resolver.get_io_service());

	asio::error_code error = asio::error::host_not_found;
	while (error && endPointIterator != end) {
		socket -> close();
		socket -> connect(*endPointIterator++, error);
	}
	if (error) {
		OnConnection(NULL, error);
		Logger::LogError(error);
	}
	else {
		Logger::Log("Connection established", Logger::DebugLevel::CONNECTION_EVENTS);

		// build a connection object and callback
		Connection* connection = NetworkFactory::BuildConnection(socket);
		OnConnection(connection, error);
		connection -> Start();
	}

	_resolverLock.unlock();
}

void ConnectionResolver::Close() {
	_resolver.cancel();
}