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
	[this](std::error_code ec, std::size_t bytesLeft)
	{
		if (_inDeletionProcess)
			return;

		if (!ec)
		{
			unsigned int currentIndex = 0;
			unsigned int bytesToWrite = 0;

			while (bytesLeft > 0) {
				if (lengthBytesLeft_ > 0) {
					//we have length bytes to read
					bytesToWrite = (bytesLeft < lengthBytesLeft_) ? bytesLeft : lengthBytesLeft_;

					// write to length bytes
					memcpy(lengthBytes_, _buffer + currentIndex, bytesToWrite);

					if ((lengthBytesLeft_ -= bytesToWrite) == 0) {
						// if length bytes full, produce message size
						currentMessage_ = std::string(lengthBytes_, 4); // Start new message with size header
						messageBytesLeft_ = Networking::deserializeInteger(lengthBytes_) - 4;
					}
				}
				else if (messageBytesLeft_ > 0) {
					bytesToWrite = (bytesLeft < messageBytesLeft_) ? bytesLeft : messageBytesLeft_;

					// append bytes to current message;
					currentMessage_ += std::string(_buffer + currentIndex, bytesToWrite);

					// if no bytes left, perform message callback
					if ((messageBytesLeft_ -= bytesToWrite) == 0) {
						onReceivedMessage_(std::move(currentMessage_));
						lengthBytesLeft_ = 4; // we are now waiting for the next message length
					}
				}
				currentIndex += bytesToWrite;
				bytesLeft -= bytesToWrite;
			}
			// read next buffer entry
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

void Connection::SendData(const std::string& data) {
	assert(!data.empty() && "Tried to send empty string.");

	_socket->async_write_some(asio::buffer(data.c_str(), data.size()),
	[this](asio::error_code ec, std::size_t /*length*/)
	{
		if (_inDeletionProcess)
			return;

		if (ec)
		{
			Logger::LogError(ec);
		}
	});
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

std::mutex Connection::_connectionLock;