#include <iostream>
#include <string>
#include "Networking.h"

using namespace Networking;


void Logger::SetDebugLevel(DebugLevel level)
{
	_debugLevel = level;
}

void Logger::Log(std::string message, DebugLevel messageLevel) {
	if (messageLevel <= _debugLevel) {
		std::cout << message << std::endl;
	}
}

void Networking::Logger::LogError( asio::error_code errorCode)
{
	if (_debugLevel >= DebugLevel::ERROR_ONLY) {
		std::cout << "Network Error: " << errorCode.value() << " : " << errorCode.message() << std::endl;
	}
}

Logger::DebugLevel Logger::_debugLevel = Logger::DebugLevel::ALL;
