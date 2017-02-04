#include "Connection.h"
#include "Libraries\asio-1.10.8\include\asio.hpp"
#include "NetworkLogger.h"
#include <iostream>

using asio::ip::tcp;
using namespace NetworkPrototype;

Connection::Connection(asio::ip::tcp::socket* socket) {
	_socket = socket;
	_sendQueue = std::queue<std::string>();
}

Connection::Connection(Connection& connection) {
	_socket = connection._socket;
	_sendQueue = std::queue<std::string>();
}

void Connection::Start() {
	ReadData();
}

void Connection::ReadData()
{
	_connectionLock.lock();
	_socket -> async_receive(asio::buffer(_buffer),
	[this](std::error_code ec, std::size_t length)
	{
		if (!ec)
		{
			auto data = std::string(_buffer, length);
			OnReceivedData(data);
			ReadData();
		}
		else 
		{
			Logger::Log(ec.message());
		}
	});
	_connectionLock.unlock();
}

void Connection::SendData(std::string data) {
	_sendQueue.push(std::move(data));

	// if this new message is alone in the queue, start writing
	if (_sendQueue.size() == 1) {
		WriteData();
	}
}

void Connection::WriteData()
{
	std::string data = std::move(_sendQueue.front());
	_sendQueue.pop();
	strncpy_s(_buffer, 1024, data.c_str(), data.size());

	_socket->async_write_some(asio::buffer(_buffer, data.size()),
	//_socket -> async_write_some(asio::buffer(_buffer, length),
	[this](std::error_code ec, std::size_t /*length*/)
	{
		if (!ec)
		{
			if (_sendQueue.size() >= 1) {
				WriteData();
			}
			else {
				ReadData(); // get back to reading
			}
		}
		else {
			Logger::Log(ec.message());
		}
	});
}

std::mutex Connection::_connectionLock;