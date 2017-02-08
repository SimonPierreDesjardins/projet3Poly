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
	__declspec(dllexport) void __cdecl assignerHandleChat(HWND handle)
	{
		Client::getClient()->setChatWindow(handle);
	}

	__declspec(dllexport) void __cdecl assignerHandleUser(HWND handle)
	{
		Client::getClient()->setUserWindow(handle);
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
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////