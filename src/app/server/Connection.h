#pragma once
#include "asio.hpp"
#include <queue>
#include <memory>
#include <mutex>

namespace NetworkPrototype 
{
	class Connection{

	public:
		// Constructor taking a functionnal socket
		Connection(asio::ip::tcp::socket* socket);

		Connection(Connection& connection);

		//Starts the connection process to send data to eachother
		void Start();

		// Send data method
		void SendData(std::string data);

		// Connection closer
		void CloseConnection();

		//On received data event
		__event void OnReceivedData(std::string& data);


		// ping?

		// On lost connection?

	private:

		void ReadData();

		void WriteData();

		asio::ip::tcp::socket* _socket; // A reference to the currently used network socket

		// Buffer used to store data received from the client.
		char _buffer[1024];
		//std::shared_ptr<std::array<char, 1024>> _buffer;

		std::queue<std::string> _sendQueue;

		static std::mutex _connectionLock;

	};
}
