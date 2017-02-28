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
	
	// Initialize socket
	socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	assert(socket_ != INVALID_SOCKET);

	setOnMessageReceivedHandler(&Connection::receiveMessage, this);
	setOnConnectionLostHandler(&Connection::lostConnection, this);
}

Connection::~Connection()
{
	closesocket(socket_);
	WSACleanup();
}

bool Connection::requestConnection(const std::string& hostName, const std::string& port)
{
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
		// Handle connection error here.
	}

	
	listener_ = std::thread(&Connection::listen, this);
	return true;
}

void Connection::listen()
{
	int readBytes = recv(socket_, rcvBuffer_.data(), DEFAULT_BUFF_LEN, 0);
	onMessageReceived_(std::string(rcvBuffer_.data()));
}


void Connection::sendMessage(const std::string& message)
{
	
}

void Connection::receiveMessage(const std::string& message)
{
	std::cout << message << std::endl;
}

void Connection::lostConnection()
{
	std::cout << "Lost connection" << std::endl;

}

}