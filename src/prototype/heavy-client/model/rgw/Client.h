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
	Client() {};
	void setString(std::string data);

	std::string someRandomShit;
};

void Client::setString(std::string data)
{
	someRandomShit = data;
}

