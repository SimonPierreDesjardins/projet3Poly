#pragma once
#include "asio.hpp"
#include <queue>
#include <memory>
#include <mutex>

namespace Networking 
{
	class Connection{

	public:
		// Constructor taking a functionnal socket
		Connection(asio::ip::tcp::socket* socket);

		// Destructor that also cleans and closes the connection if necessary
		~Connection();

		//Connection(Connection& connection);

		//Starts the connection process to send data to eachother
		void Start();

		// Send data method
		void SendData(std::string data);


		//On received data event
		__event void OnReceivedData(std::string& data);

		// ping? <-- yagni

		__event void OnConnectionLost();

	private:
		// Connection closer
		void CloseConnection();

		void ReadData();

		void WriteData();

		asio::ip::tcp::socket* _socket; // A reference to the currently used network socket

		// Buffer used to store data received from the client.
		char _buffer[1024];

		std::queue<std::string> _sendQueue;

		static std::mutex _connectionLock;

	};
}
