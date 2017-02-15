#pragma once
#ifndef __NETWORKLOGGER_H__
#define __NETWORKLOGGER_H__

#include <string>

namespace Networking {

	class Logger {

	public:
		static void Log(std::string message);

		static void LogError(std::error_code errorCode);

	};

}

#endif