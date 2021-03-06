////////////////////////////////////////////////
/// @file   InterfaceNative.h
/// @author 
/// @date   2017-02-06
///
/// @addtogroup 
/// @{
////////////////////////////////////////////////
#ifndef __INTERFACE_NATIVE_H__
#define __INTERFACE_NATIVE_H__

#include <windows.h>

extern "C"
{
	__declspec(dllexport) int __cdecl getQueueSize();
	__declspec(dllexport) void __cdecl verifyForMessage(char dataUtf8[1024]);
	__declspec(dllexport) void __cdecl startConnection(const wchar_t* ipAdresse, const wchar_t* port);
	__declspec(dllexport) void __cdecl stopConnection();
	__declspec(dllexport) void __cdecl sendMessage(char* dataUtf8);
	__declspec(dllexport) bool __cdecl verifyConnection();
	__declspec(dllexport) bool verifyConnectionFailure();
	__declspec(dllexport) void __cdecl resetConnectionFailure();
}

#endif // __INTERFACE_NATIVE_H__
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////