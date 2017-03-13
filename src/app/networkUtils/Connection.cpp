#include "Networking.h"
#include "TypeSerializerDeserializer.h"
#include <iostream>

using asio::ip::tcp;
using namespace Networking;

/*
Connection::Connection(asio::ip::tcp::socket* socket) {
	_socket = socket;
	_sendQueue = std::queue<std::string>();
}
*/

Connection::~Connection()
{
	_connectionLock.lock();
	_inDeletionProcess = true;
	CloseConnection();
	_connectionLock.unlock();
}

void Connection::Start() {
	ReadData();
}

void Connection::ReadData()
{
	_socket -> async_receive(asio::buffer(_buffer),
	[this](std::error_code ec, std::size_t length)
	{
		if (_inDeletionProcess)
			return;

		if (!ec)
		{

			unsigned int messageStartIndex = 0;
			while (messageStartIndex != length) {
				uint32_t msgLength = Networking::deserializeInteger(_buffer + messageStartIndex);
				std::string data(_buffer + messageStartIndex, msgLength);
				onReceivedMessage_(data);
				messageStartIndex += msgLength;
			}
			ReadData();
		}
		else 
		{
			Logger::LogError(ec);
			// End of connection
			CheckIfDisconnect(ec);
		}
	});
}

void Connection::SendData(std::string data) {
	_sendQueue.push(std::move(data));

	// if this new message is alone in the queue, start writing
	if (_sendQueue.size() == 1) {
		WriteData();
	}
}

void Networking::Connection::CloseConnection()
{
	if (_socket != NULL) {
		asio::error_code ec;
		_socket->cancel();
		_socket->shutdown(asio::ip::tcp::socket::shutdown_both, ec);
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
		Logger::Log("Connection lost", Logger::DebugLevel::CONNECTION_EVENTS);

		onConnectionLost_();
		break;
	}
}

void Connection::WriteData()
{
	std::string data = std::move(_sendQueue.front());
	_sendQueue.pop();

	_socket->async_write_some(asio::buffer(data.c_str(), data.size()),
	//_socket -> async_write_some(asio::buffer(_buffer, length),
	[this](asio::error_code ec, std::size_t /*length*/)
	{
		if (_inDeletionProcess)
			return;

		if (!ec)
		{
			if (_sendQueue.size() >= 1) {
				WriteData();
			}
		}
		else {
			Logger::LogError(ec);
		}
	});
}

std::mutex Connection::_connectionLock;