#pragma once
#ifndef __NETWORKLOGGER_H__
#define __NETWORKLOGGER_H__

#include <string>

namespace Networking {

	///<summary>Used to track and print networking events and issues in standard output</summary>
	class Logger {

	public:
		///<summary> Defines the verbosity of logs from the connection interface</summary>
		enum DebugLevel {
			NONE,
			ERROR_ONLY,
			CONNECTION_EVENTS,
			ALL
		};

		static void SetDebugLevel(DebugLevel level);

		///<summary>Used to track and print networking events and issues in standard output</summary>
		static void Log(std::string message, DebugLevel);

		static void LogError(asio::error_code errorCode);

	private:
		static DebugLevel _debugLevel;

	};

}

#endif