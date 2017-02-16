#include "Networking.h"
#include <iostream>

using asio::ip::tcp;
using namespace Networking;

Connection::Connection(asio::ip::tcp::socket* socket) {
	_socket = socket;
	_sendQueue = std::queue<std::string>();
}

Connection::~Connection()
{
	CloseConnection();
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
			Logger::LogError(ec);
			// End of connection
			CheckIfDisconnect(ec);
		}
	});
	_connectionLock.unlock();
}

void Connection::SendData(std::string data) {
	data = std::to_string(data.size()) + ";" + data;

	_sendQueue.push(std::move(data));

	// if this new message is alone in the queue, start writing
	if (_sendQueue.size() == 1) {
		WriteData();
	}
}

void Networking::Connection::CloseConnection()
{
	if (_socket != NULL) {
		_socket->cancel();
		_socket->close();
		delete _socket;
	}
}

void Networking::Connection::CheckIfDisconnect(std::error_code error)
{
	switch (error.value()) {
	case asio::error::eof:
	case asio::error::connection_aborted:
	case asio::error::connection_reset:
		//_socket -> close();
		OnConnectionLost();
		break;
	}
}

void Connection::WriteData()
{
	std::string data = std::move(_sendQueue.front());
	_sendQueue.pop();
	strncpy_s(_buffer, 1024, data.c_str(), data.size());

	_socket->async_write_some(asio::buffer(_buffer, data.size()),
	//_socket -> async_write_some(asio::buffer(_buffer, length),
	[this](asio::error_code ec, std::size_t /*length*/)
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
			Logger::LogError(ec);
		}
	});
}

std::mutex Connection::_connectionLock;