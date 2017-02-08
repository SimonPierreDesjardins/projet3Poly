#pragma once
////////////////////////////////////////////////
/// @file   Client.cpp
/// @author 
/// @date   2017-02-06
///
/// @addtogroup 
/// @{
////////////////////////////////////////////////

#include <string>
#include "Networking.h"

class Client 
{
public:

	void startConnection(std::string ipAdresse, std::string port);
	void stopConnection();
	void sendMessage(std::string data);

	void setString(std::string data);
private:
	void onMessageReceived(std::string& data);

	void onConnectionEstablished(Networking::Connection* connection);

	bool _connected = false;

	std::thread ioServiceThread;

	Networking::Connection* _connection;
	
	std::string someRandomShit;
};


void Client::setString(std::string data)
{
	someRandomShit = data;
}

