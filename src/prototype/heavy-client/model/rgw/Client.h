#pragma once
////////////////////////////////////////////////
/// @file   Client.cpp
/// @author 
/// @date   2017-02-06
///
/// @addtogroup 
/// @{
////////////////////////////////////////////////
#ifndef __CLIENT__
#define __CLIENT__

#include "Networking.h"
#include <string>
#include <windowsx.h>
#include "InterfaceNative.h"
#include <iostream>
#include <queue>

class Client 
{
public:
	static Client* getClient();

	void startConnection(std::string ipAdresse, std::string port);
	void stopConnection();
	void sendMessage(std::string data);

	bool getConnectionFailureState();
	bool getConnectionState();
	int getMessagesQueued();
	std::string getMessage();
	void resetConnectionFailure();

private:
	void onMessageReceived(std::string& data);
	void onConnectionEstablished(Networking::Connection* connection);
	void onConnectionFailed();
	bool _connected = false;
	bool failedConnection = false;
	std::string lastMessage;
	std::thread* ioServiceThread;
	Networking::Connection* _connection;
	Networking::ConnectionResolver* _resolver;
	static Client* client;

	std::queue<std::string> message = std::queue<std::string>();
};

#endif





