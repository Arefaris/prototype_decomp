#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h>
#include <string.h>

#include "code/core/file/filesystem.h"
#include "code/core/file/mounts.h"
#include "code/core/hash.h"
#include "code/core/strings.h"

namespace core
{
	// FUNCTION: ENGINE 0x10643C00
	void FileSystemInit(unsigned int requests, unsigned int files, int value, int heap, unsigned int instances)
	{
		InitMounts(requests, files, value, heap, instances);
	}

	// FUNCTION: ENGINE 0x10643C10
	void FileSystemShutdown()
	{
		ShutdownMounts();
	}

	// FUNCTION: ENGINE 0x10643C20
	void FileSystemUpdate()
	{
		UpdateMounts();
	}

	// FUNCTION: ENGINE 0x10643C30
	void FileSystemSetMountPath(const char* device, const char* path)
	{
		SetMountPath(device, path);
	}

	// FUNCTION: ENGINE 0x10643C40
	void FileSystemGetMountPath(const char* device, char* path)
	{
		GetMountPath(device, path);
	}

	// FUNCTION: ENGINE 0x10643C50
	void FileSystemOpenFileAsync(IFile** file, const char* path, bool writable, int mode, int key, int unused1, int unused2, int unused3, int option)
	{
		OpenFileAsync(file, path, writable, mode, key, unused1, unused2, unused3, option);
	}

	// FUNCTION: ENGINE 0x10643C60
	void FileSystemOpenFile(IFile** file, const char* path, bool writable, int mode, int key, int unused1, int unused2, int unused3, int option)
	{
		OpenFile(file, path, writable, mode, key, unused1, unused2, unused3, option);
	}

	// FUNCTION: ENGINE 0x10643C70
	void FileSystemOpenSaveGameAsync(IFile** file, const char* path, bool writable, int mode, int a, int b, int key)
	{
		OpenSaveGameAsync(file, path, writable, mode, a, b, key);
	}

	// FUNCTION: ENGINE 0x10643C80
	void FileSystemOpenSaveGame(IFile** file, const char* path, bool writable, int mode, int a, int b, int key)
	{
		OpenSaveGame(file, path, writable, mode, a, b, key);
	}

	// FUNCTION: ENGINE 0x10643C90
	void FileSystemOpenDriveAsync(IDrive** drive, const char* device, int key, int unused)
	{
		OpenDriveAsync(drive, device, key, unused);
	}

	// FUNCTION: ENGINE 0x10643CA0
	void FileSystemOpenDrive(IDrive** drive, const char* device, int key, int unused)
	{
		OpenDrive(drive, device, key, unused);
	}

	// FUNCTION: ENGINE 0x10643CB0
	bool FileSystemSetDefaultDevice(const char* device)
	{
		return SetDefaultDevice(device);
	}

	// FUNCTION: ENGINE 0x10643CC0
	void FileSystemGetDefaultDevice(char* device)
	{
		GetDefaultDevice(device);
	}

	// FUNCTION: ENGINE 0x10643CD0
	void FileSystemOpenCementLibraryAsync(ICementLibrary** library, const char* path, int pass, int heap, int preload, const char* source)
	{
		OpenCementLibraryAsync(library, path, pass, heap, preload, source);
	}

	// FUNCTION: ENGINE 0x10643CE0
	void FileSystemOpenCementLibrary(ICementLibrary** library, const char* path, int pass, int heap, int preload, const char* source)
	{
		OpenCementLibrary(library, path, pass, heap, preload, source);
	}

	// FUNCTION: ENGINE 0x10643CF0
	void FileSystemSetTimeout(int timeout)
	{
		SetFileTimeout(timeout);
	}

	// FUNCTION: ENGINE 0x10643D00
	bool FileSystemMount(const char* device, int heap)
	{
		return MountDrive(device, heap);
	}

	// FUNCTION: ENGINE 0x10643D10
	bool FileSystemUnmount(const char* device)
	{
		return UnmountDrive(device);
	}

	// FUNCTION: ENGINE 0x10643D20
	void FileSystemSetAutoMount(bool on)
	{
		SetAutoMount(on);
	}

	// FUNCTION: ENGINE 0x10643D30
	bool FileSystemMapDevice(const char* device, const char* path, int heap)
	{
		return MapDevice(device, path, heap);
	}

	// FUNCTION: ENGINE 0x10643D40
	void FileSystemUnmapDevice(const char* device)
	{
		UnmapDevice(device);
	}

	// FUNCTION: ENGINE 0x10643D50
	int FileSystemGetSlot()
	{
		return GetMountsSlot();
	}

	// FUNCTION: ENGINE 0x10643D60
	// "DEV:rest" (or the default device when the path names none): the device in upper case, the full path
	// "DEV:\rest" with back slashes, normalised; relative and native point into it and into the path
	void SplitPath(const char* path, char* full, char* device, const char** relative, const char** native)
	{
		// A ternary through a local: the plain if becomes a cmove
		char* target = device == 0 ? full : device;
		device = target;
		const char* colon = strchr(path, ':');
		const char* rest;
		unsigned int length;
		if (colon != 0)
		{
			length = colon - path + 1;
			if (length <= 16)
			{
				strncpy(device, path, length);
				device[length] = 0;
				rest = path + length;
			}
			else
			{
				GetDefaultDevice(device);
				length = strlen(device);
				rest = path;
			}
		}
		else
		{
			GetDefaultDevice(device);
			length = strlen(device);
			rest = path;
		}
		if (native != 0)
		{
			*native = rest;
		}
		for (char* c = device; *c != 0; c++)
		{
			*c = toupper(*c);
		}
		if (full != 0)
		{
			strcpy(full, device);
			if (relative != 0)
			{
				*relative = full + length;
			}
			char* c = full + length;
			strcpy(c, rest);
			for (; *c != 0; c++)
			{
				if (*c == '/')
				{
					*c = '\\';
				}
			}
			NormalisePath(full + length);
		}
	}

	// FUNCTION: ENGINE 0x10643E70
	// Whether two paths name the same file (compared as full paths, case ignored)
	int FileSystemSamePath(const char* a, const char* b)
	{
		char fullA[0x104];
		char fullB[0x104];
		SplitPath(a, fullA, 0, 0, 0);
		SplitPath(b, fullB, 0, 0, 0);
		return StrICmp(fullA, fullB) == 0;
	}

	// FUNCTION: ENGINE 0x10643ED0
	unsigned int FileSystemHashPath(const char* path)
	{
		if (*path == '\\')
		{
			path++;
		}
		return Hash32NoCase(path, 0);
	}
}
