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
	//mConnection.lock();
	//shutdown(socket_, SD_SEND);
	//mConnection.unlock();
	isConnected_ = false;

	/*if (listener_.joinable())
	{
		listener_.join();
	}*/


	closesocket(socket_);
}

bool Connection::openConnection(const std::string& hostName, const std::string& port)
{
	if (isConnected_) return false;

	// Initialize socket
	socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	assert(socket_ != INVALID_SOCKET && "Could not open socket.");

	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Translate strings to addrinfo structure
	addrinfo* info;
	assert(getaddrinfo(hostName.c_str(), port.c_str(), &hints, &info) == NO_ERROR && "Open connection assert");

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
	listener_.detach();

	return true;
}

void Connection::fetchSocketMessage()
{
	// Read and handle the new message.
	mConnection.lock();
	rcvBuffer_.fill(char());
	int readBytes = recv(socket_, rcvBuffer_.data(), DEFAULT_BUFF_LEN, 0);
	mConnection.unlock();

	if (readBytes > 0)
	{
		onMessageReceived_(rcvBuffer_.data(), readBytes);
	}
	else // Connection lost 
	{
		if (isConnected_)
		{
			isConnected_ = false;
			onConnectionLost_();
			closesocket(socket_);
		}
	} 
}

void Connection::listen()
{
	fd_set readfds;
	while (isConnected_)
	{
		FD_ZERO(&readfds);
		FD_SET(socket_, &readfds);
		mConnection.lock();
		// Check if there is a message on the socket q.
		int selectResult = !select(NULL, &readfds, NULL, NULL, &timeout_);
		mConnection.unlock();
		if (selectResult != SOCKET_ERROR && FD_ISSET(socket_, &readfds))
		{
			fetchSocketMessage();
		}
		else if (selectResult == SOCKET_ERROR)
		{
			if (isConnected_)
			{
				isConnected_ = false;
				onConnectionLost_();
				closesocket(socket_);
			}
		}
	}
}

void Connection::readData()
{
}

void Connection::sendMessage(const std::string& message)
{
	if (!isConnected_) return;
	send(socket_, message.c_str(), (int)(message.size()), 0);
}

void Connection::receiveMessage(char const* message, int32_t size)
{
	std::cout << message << std::endl;
}

void Connection::lostConnection()
{

}

}