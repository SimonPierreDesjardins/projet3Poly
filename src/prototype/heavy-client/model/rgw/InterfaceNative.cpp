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
	__declspec(dllexport) void __cdecl print_line(const char* str)
	{
	}

}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////