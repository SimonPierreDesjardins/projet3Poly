#include "Connection.h"
#include "Libraries\asio-1.10.8\include\asio.hpp"

using asio::ip::tcp;

Connection::Connection(tcp::socket* socket) {
	_socket = socket;
	_remoteEndpoint = socket->remote_endpoint();
}

void Connection::Start() {
	ReadData();
}

void Connection::ReadData()
{
	//auto self(shared_from_this()); lock during read
	_socket -> async_read_some(asio::buffer(_buffer),
	[this](std::error_code ec, std::size_t length)
	{
		if (!ec)
		{
			OnReceivedData(_buffer.data(), length);
			ReadData();
		}
	});
}

void Connection::SendData(std::string data) {

	strncpy_s(_buffer.data(), 1024, data.c_str(), data.length()); // populate the buffer with required data

	WriteData(strlen(data.c_str()));
}

void Connection::WriteData(std::size_t length )
{
	//auto self(shared_from_this()); lock during write
	_socket -> async_write_some(asio::buffer(_buffer, length),
	[this](std::error_code ec, std::size_t /*length*/)
	{
		if (!ec)
		{
			ReadData(); // get back to reading
		}
	});
}