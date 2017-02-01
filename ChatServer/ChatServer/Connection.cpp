#include "Connection.h"
#include "Libraries\asio-1.10.8\include\asio.hpp"
#include "NetworkLogger.h"

using asio::ip::tcp;
using namespace NetworkPrototype;

Connection::Connection(std::shared_ptr<asio::ip::tcp::socket> socket) {
	_socket = socket;
}

void Connection::Start() {
	ReadData();
}

void Connection::ReadData()
{
	//auto self(shared_from_this()); lock during read
	_socket -> async_receive(asio::buffer(_buffer),
	[this](std::error_code ec, std::size_t length)
	{
		if (!ec)
		{
			OnReceivedData(_buffer.data(), length);
			ReadData();
		}
		else 
		{
			Logger::Log(ec.message());
		}
	});
}

void Connection::SendData(std::string data) {

	// Change to add to queue

	WriteData(data);
}

void Connection::WriteData(std::string message )
{
	//auto self(shared_from_this()); lock during write
	_socket->async_write_some(asio::buffer(message),
	//_socket -> async_write_some(asio::buffer(_buffer, length),
	[this](std::error_code ec, std::size_t /*length*/)
	{
		if (!ec)
		{
			ReadData(); // get back to reading
		}
		else {
			Logger::Log(ec.message());
		}
	});
}