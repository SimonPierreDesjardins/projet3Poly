#pragma once
#include <string>

namespace Networking {

	class Logger {

	public:
		static void Log(std::string message);

		static void LogError(std::error_code errorCode);

	};

}