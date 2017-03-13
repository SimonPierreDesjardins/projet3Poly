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
	return true;
}

void Connection::fetchSocketMessage()
{
	// Read and handle the new message.
	mConnection.lock();
	rcvBuffer_.fill(char());
	int readBytes = recv(socket_, rcvBuffer_.data(), DEFAULT_BUFF_LEN, 0);

	if (readBytes > 0)
	{
		onMessageReceived_(rcvBuffer_.data(), readBytes);
	}
	else // Connection lost 
	{
		isConnected_ = false;
		// TODO: Notifier le ui de la deconnexion.
	} 
	// TODO: else pour le recv qui fail.
	mConnection.unlock();
}

void Connection::listen()
{
	fd_set readfds;
	while (isConnected_)
	{
		FD_ZERO(&readfds);
		FD_SET(socket_, &readfds);

		// Check if there is a message on the socket q.
		int selectResult = !select(NULL, &readfds, NULL, NULL, &timeout_);
		if (selectResult != SOCKET_ERROR && FD_ISSET(socket_, &readfds))
		{
			fetchSocketMessage();
		}
		else if (selectResult == SOCKET_ERROR)
		{
			isConnected_ = false;
			// TODO: Notifier le ui de la deconnexion.
		}
	}
}

void Connection::readData()
{
}

void Connection::sendMessage(const std::string& message)
{
	if (!isConnected_) return;

	mConnection.lock();
	send(socket_, message.c_str(), (int)(message.size()), 0);
	mConnection.unlock();
}

void Connection::receiveMessage(char const* message, int32_t size)
{
	std::cout << message << std::endl;
}

void Connection::lostConnection()
{

}

}