#include <iostream>
#include <string>
#include "NetworkLogger.h"

using namespace Networking;


void Logger::Log(std::string message) {

	std::cout << message << std::endl;

}

void Networking::Logger::LogError(std::error_code errorCode)
{
	std::cout << "Network Error: " << errorCode.value() << " : " << errorCode.message() << std::endl;
}
