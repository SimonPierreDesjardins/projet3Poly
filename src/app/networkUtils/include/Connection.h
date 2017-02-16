#pragma once
#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include "asio.hpp"
#include "Networking.h"
#include <queue>
#include <memory>
#include <mutex>

namespace Networking 
{
	class Connection{
		friend class NetworkFactory;
		friend class ConnectionResolver;
		friend class ServerListener;

	public:

		///<summary>Sends the string of bytes through the connection</summary>
		///<param name='data'>The string of bytes to send.</param>
		void SendData(std::string data);

		///<summary>Event called whenever data is received by this connection</summary>
		///<param name='data'>The string of bytes recieved.</param>
		__event void OnReceivedData(std::string& data);

		///<summary>Event called whenever the connection is lost</summary>
		__event void OnConnectionLost();

	private:
		//Starts the connection process to send data to eachother
		void Start();

		// Constructor taking a functionnal socket
		Connection(asio::ip::tcp::socket* socket);

		// Destructor that also cleans and closes the connection if necessary
		~Connection();

		// Connection closer
		void CloseConnection();

		void CheckIfDisconnect(std::error_code error);

		void ReadData();

		void WriteData();

		asio::ip::tcp::socket* _socket; // A reference to the currently used network socket

		// Buffer used to store data received from the client.
		char _buffer[1024];

		std::queue<std::string> _sendQueue;

		static std::mutex _connectionLock;

	};
}
#endif
