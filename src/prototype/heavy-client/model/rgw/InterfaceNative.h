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
	__declspec(dllexport) void __cdecl assignerHandleChat(HWND handle);
	__declspec(dllexport) void __cdecl assignerHandleUser(HWND handle);

	__declspec(dllexport) void __cdecl startConnection(const wchar_t* ipAdresse, const wchar_t* port);
	__declspec(dllexport) void __cdecl stopConnection();
	__declspec(dllexport) void __cdecl sendMessage(const wchar_t* data);
	__declspec(dllexport) bool __cdecl verifyConnection();

}

#endif // __INTERFACE_NATIVE_H__
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////