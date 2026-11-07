// The om library's access to the host system (0x105E4150 - 0x105E41F2): the text of the last error and the working
// directory.
#include "code/om/filesystem.h"
#include "code/om/path.h"

// The kernel32 imports (see win32drive.cpp)
extern "C"
{
	__declspec(dllimport) unsigned long __stdcall GetLastError();
	__declspec(dllimport) unsigned long __stdcall FormatMessageA(unsigned long flags, const void* source, unsigned long message,
		unsigned long language, char* buffer, unsigned long size, void* arguments);
	__declspec(dllimport) unsigned long __stdcall GetModuleFileNameA(void* module, char* fileName, unsigned long size);
	__declspec(dllimport) int __stdcall SetCurrentDirectoryA(const char* path);
}
#pragma comment(linker, "/alternatename:__imp__GetLastError@0=__imp__GetLastError")
#pragma comment(linker, "/alternatename:__imp__FormatMessageA@28=__imp__FormatMessageA")
#pragma comment(linker, "/alternatename:__imp__GetModuleFileNameA@12=__imp__GetModuleFileNameA")
#pragma comment(linker, "/alternatename:__imp__SetCurrentDirectoryA@4=__imp__SetCurrentDirectoryA")

namespace om
{
	// FUNCTION: ENGINE 0x105E4150
	bool GetLastErrorText(char* buffer, unsigned int size)
	{
		unsigned long error = GetLastError();
		unsigned long length = FormatMessageA(0x1200, 0, error, 0x400, buffer, size, 0);
		return length > 0;
	}

	// FUNCTION: ENGINE 0x105E4180
	// NONMATCHING: the engine copies the string out of a named temporary and passes its address, ours the constructor's result (61.8 %)
#ifdef NONMATCHING
	void SetWorkingDirectoryToModule()
	{
		char buffer[256];
		GetModuleFileNameA(0, buffer, 256);
		String directory(String(buffer, true));
		GetDirectory(&directory);
		SetCurrentDirectoryA(directory.GetText());
	}
#endif
}
