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


class Client 
{
public:
	Client();

	void startConnection(std::string ipAdresse, std::string port);
	void stopConnection();
	void sendMessage(std::string data);

	void setString(std::string data);
private:
	void onMessageReceived(std::string& data);


	
	std::string someRandomShit;
};


void Client::setString(std::string data)
{
	someRandomShit = data;
}

