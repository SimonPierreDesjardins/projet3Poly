#include "Connection.h"
#include "Libraries\asio-1.10.8\include\asio.hpp"

using asio::ip::tcp;

Connection::Connection(tcp::socket* socket) {
	_socket = socket;
	_remoteEndpoint = socket->remote_endpoint();
}

void Connection::SendData() {
	/*
	asio::async_write(_socket, asio::buffer(data, length), )
	_socket -> 
	*/
}