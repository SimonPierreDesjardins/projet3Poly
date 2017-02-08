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


class Client 
{
public:
	static Client* getClient();

	void startConnection(std::string ipAdresse, std::string port);
	void stopConnection();
	void sendMessage(std::string data);

	bool getConnectionState();
	void setChatWindow(HWND chat);
	void setUserWindow(HWND user);

private:
	void onMessageReceived(std::string& data);
	void onConnectionEstablished(Networking::Connection* connection);
	bool _connected = false;
	std::string lastMessage;
	std::thread* ioServiceThread;
	Networking::Connection* _connection;
	Networking::ConnectionResolver* _resolver;
	static Client* client;

	HWND chatWindow;
	HWND userWindow;
};

#endif





