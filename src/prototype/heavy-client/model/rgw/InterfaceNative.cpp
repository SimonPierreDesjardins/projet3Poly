////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.h
/// @author 
/// @date   2017-02-06
///
/// @addtogroup 
/// @{
////////////////////////////////////////////////
#include <string>

#include "InterfaceNative.h"
#include "Client.h"

extern "C"
{
	////////////////////////////////////////////////////////////////////////
	///
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl verifyQueueSize()
	{
		return Client::getClient()->getMessagesQueued();
	}

	__declspec(dllexport) void verifyForMessage(char *str, int len)
	{
		std::string data = Client::getClient()->getMessage();
		strcpy_s(str, len, data.c_str());
	}

	__declspec(dllexport) void startConnection(const wchar_t* ipAdresse, const wchar_t* port)
	{
		std::wstring ws(ipAdresse);
		std::wstring wc(port);

		std::string arg0(ws.begin(), ws.end());
		std::string arg1(wc.begin(), wc.end());

		Client::getClient()->startConnection(arg0, arg1);
	}

	__declspec(dllexport) void stopConnection()
	{
		Client::getClient()->stopConnection();
	}

	__declspec(dllexport) void sendMessage(const wchar_t* data)
	{
		std::wstring ws(data);
		std::string arg0(ws.begin(), ws.end());

		Client::getClient()->sendMessage(arg0);
	}

	__declspec(dllexport) bool verifyConnection()
	{
		return Client::getClient()->getConnectionState();
	}

	__declspec(dllexport) bool verifyConnectionFailure()
	{
		return Client::getClient()->getConnectionFailureState();
	}
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////