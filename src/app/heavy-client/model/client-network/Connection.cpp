#include <iostream>

#include <cassert>

#include <winsock2.h>
#include <ws2tcpip.h>

#include "Connection.h"



namespace client_network
{

Connection::Connection()
{
	WSADATA wsaData;
	
	// Start WSA
	assert(WSAStartup(MAKEWORD(2, 2), &wsaData) == NO_ERROR);
	
	setOnMessageReceivedHandler(&Connection::receiveMessage, this);
	setOnConnectionLostHandler(&Connection::lostConnection, this);
}

Connection::~Connection()
{
	closeConnection();
	WSACleanup();
}

void Connection::closeConnection()
{
	mConnection.lock();
	shutdown(socket_, SD_SEND);
	mConnection.unlock();
	isConnected_ = false;

	if (listener_.joinable())
	{
		listener_.join();
	}

	closesocket(socket_);
}

bool Connection::openConnection(const std::string& hostName, const std::string& port)
{
	if (isConnected_) return false;

	// Initialize socket
	socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	assert(socket_ != INVALID_SOCKET);

	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Translate strings to addrinfo structure
	addrinfo* info;
	assert(getaddrinfo(hostName.c_str(), port.c_str(), &hints, &info) == NO_ERROR);

	// Find the good info
	while (info == NULL || info->ai_family != AF_INET)
	{
		info = info->ai_next;
	}

	// Make sure the info has been found
	assert(info != NULL && info->ai_family == AF_INET);
	
	int result = connect(socket_, info->ai_addr, int(info->ai_addrlen));
	freeaddrinfo(info);
	if (result == SOCKET_ERROR)
	{
		isConnected_ = false;
		return false;
	}

	isConnected_ = true;
	listener_ = std::thread(&Connection::listen, this);
	//sendMessage(std::string("hello"));
	return true;
}

void Connection::listen()
{
	fd_set sockets{ { socket_ }, 1 };
	while (isConnected_)
	{
		// Check if there is an message on the socket q.
		if (!select(NULL, &sockets, NULL, NULL, &timeout_))
		{
			// Read and handle the new message.
			mConnection.lock();
			int readBytes = recv(socket_, rcvBuffer_.data(), DEFAULT_BUFF_LEN, 0);
			onMessageReceived_(std::string(rcvBuffer_.data()));
			if (readBytes == 0)
			{
				isConnected_ = false;
			}
			mConnection.unlock();
		}
	}
}

void Connection::readData()
{
}

void Connection::sendMessage(const std::string& message)
{
	mConnection.lock();
	send(socket_, message.data(), message.size(), MSG_OOB);
	mConnection.unlock();
}

void Connection::receiveMessage(const std::string& message)
{
	std::cout << message << std::endl;
}

void Connection::lostConnection()
{

}

}