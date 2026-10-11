#define _CRT_SECURE_NO_WARNINGS

#include <string.h>

#include "code/core/file/mounts.h"
#include "code/core/heap.h"
#include "code/core/strings.h"

// The kernel32 imports (see controllerdirectinput.cpp)
extern "C"
{
	__declspec(dllimport) unsigned long __stdcall GetCurrentDirectoryA(unsigned long size, char* buffer);
	__declspec(dllimport) unsigned long __stdcall GetLogicalDrives();
}
#pragma comment(linker, "/alternatename:__imp__GetCurrentDirectoryA@8=__imp__GetCurrentDirectoryA")
#pragma comment(linker, "/alternatename:__imp__GetLogicalDrives@0=__imp__GetLogicalDrives")

// The Win32 devices (all names guessed; unit 0x1064F810 - 0x1064FA88, file name guessed): drive letters, and up to
// four device names mapped to RAM drives
namespace core
{
	struct DeviceMapping
	{
		char* name;
		const char* path;
	};

	// GLOBAL: ENGINE 0x1127CAA0
	static DeviceMapping sMappings[4];

	// 0x10652320 / 0x10651CE0 (not reconstructed): a RAM drive over a mapped device, a Win32 drive over a drive letter
	void CreateRamDrive(Drive** drive, const char* device, const char* path, int heap);
	void CreateWin32Drive(Drive** drive, const char* device, int heap);

	// FUNCTION: ENGINE 0x1064F810
	void GetCurrentDevice(char* device)
	{
		char directory[0x104];
		GetCurrentDirectoryA(0x100, directory);
		strncpy(device, directory, 2);
		device[2] = 0;
		_strupr(device);
	}

	// FUNCTION: ENGINE 0x1064F860
	// Device names end in ':'; a name can be mapped once
	bool AddDeviceMapping(const char* device, const char* path, int heap)
	{
		if (device[strlen(device) - 1] != ':')
		{
			return false;
		}
		if (path == 0)
		{
			return false;
		}
		unsigned int free = 4;
		for (unsigned int i = 0; i < 4; i++)
		{
			if (sMappings[i].path != 0)
			{
				if (StrCmp(sMappings[i].name, device) == 0)
				{
					return false;
				}
			}
			else if (free == 4)
			{
				free = i;
			}
		}
		if (free == 4)
		{
			return false;
		}
		sMappings[free].path = path;
		sMappings[free].name = (char*)HeapAlloc(heap, strlen(device) + 1);
		StrCpy(sMappings[free].name, device);
		return true;
	}

	// FUNCTION: ENGINE 0x1064F920
	void RemoveDeviceMapping(const char* device)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			if (sMappings[i].path != 0 && StrCmp(sMappings[i].name, device) == 0)
			{
				Free(sMappings[i].name);
				sMappings[i].path = 0;
				return;
			}
		}
	}

	// FUNCTION: ENGINE 0x1064F980
	const char* FindDeviceMapping(const char* device)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			if (sMappings[i].path != 0 && StrCmp(sMappings[i].name, device) == 0)
			{
				return sMappings[i].path;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1064F9D0
	bool IsValidDevice(const char* device)
	{
		if (FindDeviceMapping(device) != 0)
		{
			return true;
		}
		if (strlen(device) == 2 && device[0] >= 'A' && device[0] <= 'Z')
		{
			int drive = device[0] - 'A';
			return (GetLogicalDrives() >> drive) & 1;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1064FA30
	void CreateDeviceDrive(Drive** drive, const char* device, int heap, const char* path)
	{
		const char* mapped = FindDeviceMapping(device);
		if (mapped != 0)
		{
			CreateRamDrive(drive, device, mapped, heap);
			(*drive)->Slot23((int)path);
			return;
		}
		CreateWin32Drive(drive, device, heap);
		(*drive)->Slot23((int)path);
	}
}
