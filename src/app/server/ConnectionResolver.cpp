#include "ConnectionResolver.hpp"
#include "asio.hpp"
#include <iostream>

using namespace NetworkPrototype;

ConnectionResolver::ConnectionResolver(asio::io_service& ioService):
	_socket(ioService),
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

	asio::error_code error = asio::error::host_not_found;
	while (error && endPointIterator != end) {
		_socket.close();
		_socket.connect(*endPointIterator++, error);
	}
	if (error) {
		LogError(error.message());
	}
	else {
		// build a connection object and callback
		OnConnectionResolved(new Connection(&_socket));
	}
}

void ConnectionResolver::Close() {
	_resolver.cancel();
	_socket.close();
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