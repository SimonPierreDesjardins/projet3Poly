#pragma once
#include "Libraries\asio-1.10.8\include\asio.hpp"

class Connection {

public:
	// Constructor taking a functionnal socket
	Connection(asio::ip::tcp::socket* socket);

	//Starts the connection process to send data to eachother
	void Start();

	// Send data method
	void SendData(std::string data);
	
	// Connection closer
	void CloseConnection();

	//On received data event
	__event void OnReceivedData(const char* data, std::size_t length);


	// ping?

	// On lost connection?

private:

	void ReadData();

	void WriteData(std::size_t length);

	asio::ip::tcp::socket* _socket; // A reference to the currently used network socket

	asio::ip::tcp::endpoint _remoteEndpoint; // Where the connection leads to remotely.

	// Buffer used to store data received from the client.
	std::array<char, 1024> _buffer;
};