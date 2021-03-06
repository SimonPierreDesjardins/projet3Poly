#pragma once
#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <queue>
#include <memory>
#include <mutex>
#include <functional>

#include "asio.hpp"
#include "Networking.h"
#include "NetworkStandard.h"

namespace Networking 
{
class Connection
{
	friend class NetworkObjects;
	friend class ConnectionResolver;
	friend class ServerListener;

public:


	///<summary>Sends the string of bytes through the connection</summary>
	///<param name='data'>The string of bytes to send.</param>
	void SendData(const std::string& data);

	template<class F, class T>
	void hookOnReceivedMessage(F&& handler, T&& instance);

	template<class F>
	void hookOnReceivedMessage(F&& handler);

	template<class F, class T>
	void hookOnConnectionLost(F&& handler, T&& instance);

	template<class F>
	void hookOnConnectionLost(F&& handler);

private:
	// Destructor that also cleans and closes the connection if necessary
	~Connection();

	//Starts the connection process to send data to eachother
	void Start();

	// Constructor taking a functionnal socket
	Connection(asio::ip::tcp::socket* socket) { _socket = socket; }

	// Connection closer
	void CloseConnection();

	void CheckIfDisconnect(std::error_code error);

	void ReadData();

	asio::ip::tcp::socket* _socket; // A reference to the currently used network socket

	// Buffer used to store data received from the client.
	char _buffer[Networking::MessageStandard::BUFFER_SIZE];

	static std::mutex _connectionLock;
	bool _inDeletionProcess = false;

	std::function<void(const std::string&)> onReceivedMessage_;
	std::function<void(void)> onConnectionLost_;

	unsigned int lengthBytesLeft_ = 4;
	char lengthBytes_[4];
	unsigned int messageBytesLeft_ = 0;
	std::string currentMessage_ = "";
};

template<class F, class T>
void Connection::hookOnReceivedMessage(F&& handler, T&& instance)
{
	onReceivedMessage_ = std::bind(handler, instance, std::placeholders::_1);
}

template<class F>
void Connection::hookOnReceivedMessage(F&& handler)
{
	onReceivedMessage_ = std::bind(handler, std::placeholders::_1);
}

template<class F, class T>
void Connection::hookOnConnectionLost(F&& handler, T&& instance)
{
	onConnectionLost_ = std::bind(handler, instance);
}

template<class F>
void Connection::hookOnConnectionLost(F&& handler)
{
	onConnectionLost_ = std::bind(handler);
}

}

#endif
