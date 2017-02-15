#include "Networking.h"
#include <iostream>

using namespace Networking;

ConnectionResolver::ConnectionResolver(asio::io_service& ioService):
	_resolver(ioService)
{
}

ConnectionResolver::~ConnectionResolver() {
	Close();
}

void ConnectionResolver::Resolve(std::string ipAddress, std::string port) {

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
		LogError(error.message());
	}
	else {
		// build a connection object and callback
		OnConnectionResolved(new Connection(socket));
	}
}

void ConnectionResolver::Close() {
	_resolver.cancel();
	//ClearBuffers();
}

void ConnectionResolver::SetDebugLevel(DebugLevel level) {
	_debugLevel = level;
}

void ConnectionResolver::Log(std::string message, DebugLevel level) {
	if (level <= _debugLevel)
		std::cout << "Connection Log: " << message << std::endl;
}

void ConnectionResolver::LogError(std::string errorMessage) {
	if (DebugLevel::ERROR_ONLY <= _debugLevel)
		std::cout << "Connection Error : " << errorMessage << std::endl;
}

ConnectionResolver::DebugLevel ConnectionResolver::_debugLevel = DebugLevel::NONE;