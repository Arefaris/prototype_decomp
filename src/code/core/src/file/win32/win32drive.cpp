// strcpy / strncpy / strcat as the original used them; the define only silences VS 2005's deprecation warning
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>

#include "code/core/criticalsection.h"
#include "code/core/file/win32drive.h"

// The kernel32 imports (see controllerdirectinput.cpp)
extern "C"
{
	struct _FILETIME
	{
		unsigned long dwLowDateTime;
		unsigned long dwHighDateTime;
	};

	struct _WIN32_FIND_DATAA
	{
		unsigned long dwFileAttributes;
		_FILETIME ftCreationTime;
		_FILETIME ftLastAccessTime;
		_FILETIME ftLastWriteTime;
		unsigned long nFileSizeHigh;
		unsigned long nFileSizeLow;
		unsigned long dwReserved0;
		unsigned long dwReserved1;
		char cFileName[260];
		char cAlternateFileName[14];
	};

	union _ULARGE_INTEGER
	{
		struct
		{
			unsigned long LowPart;
			unsigned long HighPart;
		};
		unsigned __int64 QuadPart;
	};

	__declspec(dllimport) int __stdcall CloseHandle(void* handle);
	__declspec(dllimport) int __stdcall FindClose(void* find);
	__declspec(dllimport) int __stdcall GetVolumeInformationA(const char* root, char* volumeName, unsigned long volumeNameSize,
		unsigned long* serial, unsigned long* maximumComponentLength, unsigned long* fileSystemFlags, char* fileSystemName,
		unsigned long fileSystemNameSize);
	__declspec(dllimport) int __stdcall GetDiskFreeSpaceExA(const char* directory, _ULARGE_INTEGER* available,
		_ULARGE_INTEGER* total, _ULARGE_INTEGER* free);
	__declspec(dllimport) unsigned long __stdcall GetFullPathNameA(const char* path, unsigned long size, char* buffer,
		char** filePart);
	__declspec(dllimport) unsigned long __stdcall GetLastError();
	__declspec(dllimport) unsigned int __stdcall SetErrorMode(unsigned int mode);
	__declspec(dllimport) unsigned long __stdcall GetCurrentDirectoryA(unsigned long size, char* buffer);
	__declspec(dllimport) unsigned int __stdcall GetDriveTypeA(const char* root);
	__declspec(dllimport) void* __stdcall CreateFileA(const char* path, unsigned long access, unsigned long share,
		void* security, unsigned long creation, unsigned long attributes, void* templateFile);
	__declspec(dllimport) unsigned long __stdcall GetFileSize(void* file, unsigned long* high);
	__declspec(dllimport) int __stdcall FlushFileBuffers(void* file);
	__declspec(dllimport) unsigned long __stdcall SetFilePointer(void* file, long distance, long* high, unsigned long method);
	__declspec(dllimport) int __stdcall ReadFile(void* file, void* buffer, unsigned long size, unsigned long* done,
		void* overlapped);
	__declspec(dllimport) int __stdcall WriteFile(void* file, const void* buffer, unsigned long size, unsigned long* done,
		void* overlapped);
	__declspec(dllimport) int __stdcall SetEndOfFile(void* file);
	__declspec(dllimport) void* __stdcall FindFirstFileA(const char* pattern, _WIN32_FIND_DATAA* data);
	__declspec(dllimport) int __stdcall FindNextFileA(void* find, _WIN32_FIND_DATAA* data);
	__declspec(dllimport) int __stdcall CreateDirectoryA(const char* path, void* security);
	__declspec(dllimport) int __stdcall RemoveDirectoryA(const char* path);
	__declspec(dllimport) int __stdcall DeleteFileA(const char* path);
}
#pragma comment(linker, "/alternatename:__imp__CloseHandle@4=__imp__CloseHandle")
#pragma comment(linker, "/alternatename:__imp__FindClose@4=__imp__FindClose")
#pragma comment(linker, "/alternatename:__imp__GetVolumeInformationA@32=__imp__GetVolumeInformationA")
#pragma comment(linker, "/alternatename:__imp__GetDiskFreeSpaceExA@16=__imp__GetDiskFreeSpaceExA")
#pragma comment(linker, "/alternatename:__imp__GetFullPathNameA@16=__imp__GetFullPathNameA")
#pragma comment(linker, "/alternatename:__imp__GetLastError@0=__imp__GetLastError")
#pragma comment(linker, "/alternatename:__imp__SetErrorMode@4=__imp__SetErrorMode")
#pragma comment(linker, "/alternatename:__imp__GetCurrentDirectoryA@8=__imp__GetCurrentDirectoryA")
#pragma comment(linker, "/alternatename:__imp__GetDriveTypeA@4=__imp__GetDriveTypeA")
#pragma comment(linker, "/alternatename:__imp__CreateFileA@28=__imp__CreateFileA")
#pragma comment(linker, "/alternatename:__imp__GetFileSize@8=__imp__GetFileSize")
#pragma comment(linker, "/alternatename:__imp__FlushFileBuffers@4=__imp__FlushFileBuffers")
#pragma comment(linker, "/alternatename:__imp__SetFilePointer@16=__imp__SetFilePointer")
#pragma comment(linker, "/alternatename:__imp__ReadFile@20=__imp__ReadFile")
#pragma comment(linker, "/alternatename:__imp__WriteFile@20=__imp__WriteFile")
#pragma comment(linker, "/alternatename:__imp__SetEndOfFile@4=__imp__SetEndOfFile")
#pragma comment(linker, "/alternatename:__imp__FindFirstFileA@8=__imp__FindFirstFileA")
#pragma comment(linker, "/alternatename:__imp__FindNextFileA@8=__imp__FindNextFileA")
#pragma comment(linker, "/alternatename:__imp__CreateDirectoryA@8=__imp__CreateDirectoryA")
#pragma comment(linker, "/alternatename:__imp__RemoveDirectoryA@4=__imp__RemoveDirectoryA")
#pragma comment(linker, "/alternatename:__imp__DeleteFileA@4=__imp__DeleteFileA")

namespace core
{
	const char* CoreName();

	// FUNCTION: ENGINE 0x106511E0
	Win32Drive::~Win32Drive()
	{
		queue->Release();
		queue = 0;
		CriticalSectionDelete(lock);
		SetErrorMode(errorMode);
	}

	// FUNCTION: ENGINE 0x10651240
	void Win32Drive::Lock()
	{
		CriticalSectionEnter(lock);
	}

	// FUNCTION: ENGINE 0x10651250
	void Win32Drive::Unlock()
	{
		CriticalSectionLeave(lock);
	}

	// FUNCTION: ENGINE 0x10651260
	int Win32Drive::GetFlags()
	{
		return flags;
	}

	// FUNCTION: ENGINE 0x10651270
	int Win32Drive::GetId()
	{
		return (int)name;
	}

	// FUNCTION: ENGINE 0x10651280
	int Win32Drive::Close(int handle, const char* path)
	{
		CloseHandle((void*)handle);
		openCount--;
		return 1;
	}

	// FUNCTION: ENGINE 0x106512A0
	int Win32Drive::FindClose(int* handle)
	{
		::FindClose((void*)*handle);
		*handle = -1;
		return 1;
	}

	// FUNCTION: ENGINE 0x106512C0
	// EQUIVALENT: one store scheduled elsewhere: the original clears the serial before the state stores of the
	// failure branch, ours after them (every order of the four stores tried)
	unsigned int Win32Drive::RefreshInfo()
	{
		char root[4];
		unsigned long serial;
		strcpy(root, name);
		strcat(root, "\\");
		char* volumeName = (char*)&info.data[4];
		if (GetVolumeInformationA(root, volumeName, 0x41, &serial, 0, 0, 0, 0))
		{
			_ULARGE_INTEGER available;
			_ULARGE_INTEGER total;
			_ULARGE_INTEGER free;
			((char*)&info)[0x50] = 0;
			info.data[0] = 0;
			error = 0;
			GetDiskFreeSpaceExA(root, &available, &total, &free);
			if (available.HighPart != 0)
			{
				info.data[1] = -1;
			}
			else
			{
				info.data[1] = available.LowPart;
			}
		}
		else
		{
			serial = 0;
			info.data[0] = 4;
			error = 4;
			info.data[1] = 0;
			volumeName[0] = 0;
		}
		info.data[3] = 0x200;
		info.data[2] = (unsigned int)info.data[1] >> 9;
		return serial;
	}

	// FUNCTION: ENGINE 0x106513A0
	void Win32Drive::MakePath(const char* path, char* out, unsigned int size)
	{
		char* filePart = 0;
		char full[0x101];
		if (directory[0] != 0 && path[0] != '\\')
		{
			strcpy(full, directory);
		}
		else
		{
			strcpy(full, name);
		}
		unsigned int length = strlen(full);
		strncpy(full + length, path, 0x100 - length);
		full[0x100] = 0;
		GetFullPathNameA(full, size - 1, out, &filePart);
		out[size - 1] = 0;
	}

	// FUNCTION: ENGINE 0x10651460
	int Win32Drive::MapError(unsigned long error)
	{
		switch (error)
		{
		case 0:
			return 0;
		case 2:
		case 3:
		case 0xF:
			return 1;
		case 0x11:
		case 0x22:
			return 3;
		case 0x15:
			return 2;
		case 0xB:
		case 0x1B:
			return 5;
		case 0x70:
			return 7;
		case 0x1A:
			return 0xB;
		case 0x3ED:
			return 6;
		case 0x48F:
			return 4;
		}
		return 8;
	}

	// FUNCTION: ENGINE 0x10651570
	int Win32Drive::FillFindData(DriveFindData* out, _WIN32_FIND_DATAA* data, int* handle)
	{
		if (*handle == -1)
		{
			unsigned long code = GetLastError();
			if (code == 0x12 || code == 2 || code == 0xF || code == 3)
			{
				out->name[0] = 0;
				out->directory = 2;
				return 0;
			}
			return MapError(code);
		}
		strncpy(out->name, data->cFileName, 0x100);
		out->name[0x100] = 0;
		out->directory = ((unsigned char)data->dwFileAttributes >> 4) & 1;
		return 0;
	}

	// FUNCTION: ENGINE 0x10651610
	Win32Drive::Win32Drive(const char* name, int heap)
		: openCount(0), serial(0)
	{
		CoreName();
		errorMode = SetErrorMode(0x8001);
		CriticalSectionInit(lock);
		queue = new (heap) DriveThread(lock, heap);
		strncpy(this->name, name, 0x10);
		unknownF0 = false;
		if (GetCurrentDirectoryA(0x101, directory) != 0 && directory[0] == name[0])
		{
			strcat(directory, "\\");
		}
		else
		{
			directory[0] = 0;
		}
		unsigned int type = GetDriveTypeA(name);
		if (type == 5)
		{
			flags = 0x26;
		}
		else
		{
			flags = type == 2 ? 0x37 : 0x33;
		}
	}

	// FUNCTION: ENGINE 0x10651770
	int Win32Drive::Mount()
	{
		if (openCount != 0)
		{
			if (RefreshInfo() != serial)
			{
				if (error != 4)
				{
					error = 3;
					info.data[0] = 3;
				}
				return 0;
			}
		}
		else
		{
			RefreshInfo();
			serial = 0;
		}
		return error == 0;
	}

	// FUNCTION: ENGINE 0x106517C0
	int Win32Drive::Open(const char* path, int mode, bool writable, int* handle, unsigned int* size)
	{
		unsigned long creation;
		char full[0x101];
		MakePath(path, full, 0x101);
		unsigned long access = writable ? 0xC0000000 : 0x80000000;
		unsigned long share = writable ? 3 : 1;
		switch (mode)
		{
		case 0:
			creation = 3;
			break;
		case 1:
			creation = 4;
			break;
		case 3:
			creation = 2;
			break;
		}
		*handle = (int)CreateFileA(full, access, share, 0, creation, 0x80, 0);
		if (*handle != -1)
		{
			if (openCount == 0)
			{
				serial = RefreshInfo();
			}
			openCount++;
			*size = GetFileSize((void*)*handle, 0);
			error = 0;
			return 1;
		}
		error = MapError(GetLastError());
		return 0;
	}

	// FUNCTION: ENGINE 0x106518D0
	int Win32Drive::Commit(int handle, const char* path)
	{
		if (FlushFileBuffers((void*)handle))
		{
			error = 0;
			return 1;
		}
		error = MapError(GetLastError());
		return 0;
	}

	// FUNCTION: ENGINE 0x10651910
	int Win32Drive::Read(int handle, const char* path, unsigned int a, unsigned int position, void* buffer,
		unsigned int size, unsigned int* done, int b)
	{
		if (SetFilePointer((void*)handle, position, 0, 0) == position
			&& ReadFile((void*)handle, buffer, size, (unsigned long*)done, 0))
		{
			*done = size;
			error = 0;
			return 1;
		}
		error = MapError(GetLastError());
		return 0;
	}

	// FUNCTION: ENGINE 0x10651980
	int Win32Drive::Write(int handle, const char* path, unsigned int a, unsigned int position, const void* buffer,
		unsigned int size, unsigned int* done, unsigned int* fileSize, int b)
	{
		if ((flags & 1) == 0)
		{
			return 0;
		}
		if (position + size > *fileSize)
		{
			SetFilePointer((void*)handle, position + size, 0, 0);
			SetEndOfFile((void*)handle);
		}
		if (SetFilePointer((void*)handle, position, 0, 0) == position
			&& WriteFile((void*)handle, buffer, size, (unsigned long*)done, 0))
		{
			*fileSize = GetFileSize((void*)handle, 0);
			error = 0;
			return 1;
		}
		error = MapError(GetLastError());
		return 0;
	}

	// FUNCTION: ENGINE 0x10651A40
	int Win32Drive::FindFirst(void* path, int out, int* handle, bool keep)
	{
		char full[0x101];
		_WIN32_FIND_DATAA data;
		MakePath((const char*)path, full, 0x101);
		if (!keep && *handle != -1)
		{
			::FindClose((void*)*handle);
		}
		*handle = (int)FindFirstFileA(full, &data);
		int result = FillFindData((DriveFindData*)out, &data, handle);
		error = result;
		return result == 0;
	}

	// FUNCTION: ENGINE 0x10651AD0
	int Win32Drive::FindNext(int* handle, void* out)
	{
		if (*handle == -1)
		{
			error = 1;
			return 0;
		}
		_WIN32_FIND_DATAA data;
		if (!FindNextFileA((void*)*handle, &data))
		{
			int none = -1;
			error = FillFindData((DriveFindData*)out, &data, &none);
		}
		else
		{
			error = FillFindData((DriveFindData*)out, &data, handle);
		}
		return error == 0;
	}

	// FUNCTION: ENGINE 0x10651B60
	int Win32Drive::CreateDirectory(const char* path)
	{
		char full[0x101];
		MakePath(path, full, 0x101);
		if (CreateDirectoryA(full, 0))
		{
			error = 0;
			return 1;
		}
		if (GetLastError() == 0xB7)
		{
			error = 0;
			return 1;
		}
		error = MapError(GetLastError());
		return 0;
	}

	// FUNCTION: ENGINE 0x10651C00
	int Win32Drive::DestroyDirectory(const char* path)
	{
		char full[0x101];
		MakePath(path, full, 0x101);
		if (RemoveDirectoryA(full))
		{
			error = 0;
			return 1;
		}
		error = MapError(GetLastError());
		return 0;
	}

	// FUNCTION: ENGINE 0x10651C70
	int Win32Drive::DestroyFile(const char* path)
	{
		char full[0x101];
		MakePath(path, full, 0x101);
		if (DeleteFileA(full))
		{
			error = 0;
			return 1;
		}
		error = MapError(GetLastError());
		return 0;
	}

	// FUNCTION: ENGINE 0x10651CE0
	void CreateWin32Drive(Drive** drive, const char* device, int heap)
	{
		*drive = new (heap) Win32Drive(device, heap);
	}
}
