#pragma once
#include "Libraries\asio-1.10.8\include\asio.hpp"

class Connection {

public:
	// Constructor taking a functionnal socket
	Connection(asio::ip::tcp::socket* socket);

	// Send data method
	void SendData();
	
	// Connection closer
	void CloseConnection();

	//On received data event
	void OnReceivedData();


	// ping?

	// On lost connection?

private:

	asio::ip::tcp::socket* _socket; // A reference to the currently used network socket

	asio::ip::tcp::endpoint _remoteEndpoint; // Where the connection leads to remotely.
};