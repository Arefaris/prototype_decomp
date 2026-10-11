#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h>
#include <string.h>

#include "code/core/crc32.h"
#include "code/core/criticalsection.h"
#include "code/core/file/mounts.h"
#include "code/core/file/request.h"

namespace core
{
	// GLOBAL: ENGINE 0x1127ABF0
	static Mount sMounts[27];
	// GLOBAL: ENGINE 0x1127C9E4
	static unsigned char sMountLock[0x18];
	// GLOBAL: ENGINE 0x1127C9FC
	static char sDefaultDevice[17];
	// GLOBAL: ENGINE 0x1127CA0D
	static bool sMountsReady;
	// GLOBAL: ENGINE 0x1127CA10
	static int sMountsHeap;
	// GLOBAL: ENGINE 0x1127CA14
	static int sMountsValue;
	// GLOBAL: ENGINE 0x1127CA18
	static unsigned int sMountCount;
	// GLOBAL: ENGINE 0x110BD24C
	static int sFileTimeout = 30000;
	// GLOBAL: ENGINE 0x110BD250
	static bool sAutoMount = true;

	// FUNCTION: ENGINE 0x10649F60
	static void ToUpper(char* text)
	{
		for (; *text != 0; text++)
		{
			*text = toupper(*text);
		}
	}

	// FUNCTION: ENGINE 0x10649F90
	void InitMounts(unsigned int requests, unsigned int files, int value, int heap, unsigned int instances)
	{
		sMountsValue = value;
		GetCurrentDevice(sDefaultDevice);
		InitRequests(requests, heap);
		InitInstanceDrives(instances, heap);
		InitFiles(files, heap);
		InitMountsHook();
		CriticalSectionInit(sMountLock);
		for (unsigned int i = 0; i < 27; i++)
		{
			sMounts[i].drive = 0;
			sMounts[i].path[0] = 0;
		}
		sMountsHeap = heap;
		sMountsReady = true;
		BuildCrc32Table();
	}

	// FUNCTION: ENGINE 0x1064A010
	void LockMounts()
	{
		CriticalSectionEnter(sMountLock);
	}

	// FUNCTION: ENGINE 0x1064A020
	void UnlockMounts()
	{
		CriticalSectionLeave(sMountLock);
	}

	// FUNCTION: ENGINE 0x1064A030
	void UpdateMounts()
	{
		LockMounts();
		for (unsigned int i = 0; i < sMountCount; i++)
		{
			Drive* drive = sMounts[i].drive;
			if (drive != 0)
			{
				drive->AddRef();
				UnlockMounts();
				drive->Update();
				drive->Release();
				LockMounts();
			}
		}
		UnlockMounts();
	}

	// FUNCTION: ENGINE 0x1064A090
	bool SetDefaultDevice(const char* device)
	{
		char name[17];
		strncpy(name, device, 16);
		name[16] = 0;
		ToUpper(name);
		if (IsValidDevice(name))
		{
			LockMounts();
			strncpy(sDefaultDevice, name, 16);
			sDefaultDevice[16] = 0;
			UnlockMounts();
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1064A100
	void GetDefaultDevice(char* device)
	{
		LockMounts();
		strcpy(device, sDefaultDevice);
		UnlockMounts();
	}

	// FUNCTION: ENGINE 0x1064A130
	int GetMountsValue()
	{
		return sMountsValue;
	}

	// FUNCTION: ENGINE 0x1064A140
	void SetFileTimeout(int timeout)
	{
		sFileTimeout = timeout;
	}

	// FUNCTION: ENGINE 0x1064A150
	int GetFileTimeout()
	{
		return sFileTimeout;
	}

	// FUNCTION: ENGINE 0x1064A160
	void SetAutoMount(bool on)
	{
		LockMounts();
		sAutoMount = on;
		UnlockMounts();
	}

	// FUNCTION: ENGINE 0x1064A180
	bool MapDevice(const char* device, const char* path, int heap)
	{
		char name[17];
		strncpy(name, device, 16);
		name[16] = 0;
		ToUpper(name);
		LockMounts();
		bool mapped = AddDeviceMapping(name, path, heap);
		UnlockMounts();
		return mapped;
	}

	// FUNCTION: ENGINE 0x1064A1D0
	void UnmapDevice(const char* device)
	{
		char name[17];
		strncpy(name, device, 16);
		name[16] = 0;
		ToUpper(name);
		LockMounts();
		RemoveDeviceMapping(name);
		UnlockMounts();
	}

	// FUNCTION: ENGINE 0x1064A210
	int GetMountsSlot()
	{
		return GetMountsSlotValue();
	}

	// FUNCTION: ENGINE 0x1064A220
	int FindMount(const char* device)
	{
		for (unsigned int i = 0; i < sMountCount; i++)
		{
			if (strcmp(device, sMounts[i].name) == 0)
			{
				return i;
			}
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x1064A290
	bool MountDevice(Drive** drive, const char* device, int heap)
	{
		int index = FindMount(device);
		*drive = 0;
		Mount* mount;
		if (index != -1)
		{
			mount = &sMounts[index];
			if (mount->drive != 0)
			{
				*drive = mount->drive;
				return false;
			}
		}
		else
		{
			if (sMountCount >= 27)
			{
				*drive = 0;
				return true;
			}
			mount = &sMounts[sMountCount];
		}
		if (!IsValidDevice(device))
		{
			return true;
		}
		CreateDeviceDrive(drive, device, heap, mount->path);
		if (*drive == 0)
		{
			return true;
		}
		if (index == -1)
		{
			strncpy(mount->name, device, 16);
			sMountCount++;
			mount->name[16] = 0;
		}
		mount->drive = *drive;
		return true;
	}

	// FUNCTION: ENGINE 0x1064A350
	// An unknown device or a full table returns with the lock held (kept as in the original)
	void SetMountPath(const char* device, const char* path)
	{
		char name[17];
		strncpy(name, device, 16);
		name[16] = 0;
		ToUpper(name);
		LockMounts();
		int index = FindMount(name);
		if (index == -1)
		{
			if (!IsValidDevice(name) || sMountCount >= 27)
			{
				return;
			}
			Mount* mount = &sMounts[sMountCount];
			strncpy(mount->name, name, 16);
			mount->name[16] = 0;
			strncpy(mount->path, path, 0x100);
			sMountCount++;
			UnlockMounts();
			return;
		}
		Mount* mount = &sMounts[index];
		strncpy(mount->path, path, 0x100);
		Drive* drive = mount->drive;
		UnlockMounts();
		drive->Slot23((int)path);
	}

	// FUNCTION: ENGINE 0x1064A430
	void GetMountPath(const char* device, char* path)
	{
		char name[17];
		strncpy(name, device, 16);
		name[16] = 0;
		ToUpper(name);
		LockMounts();
		int index = FindMount(name);
		if (index == -1)
		{
			*path = 0;
			UnlockMounts();
			return;
		}
		strcpy(path, sMounts[index].path);
		UnlockMounts();
	}

	// FUNCTION: ENGINE 0x1064A4B0
	bool MountDrive(const char* device, int heap)
	{
		char name[17];
		LockMounts();
		if (device == 0)
		{
			strncpy(name, sDefaultDevice, 16);
		}
		else
		{
			strncpy(name, device, 16);
			name[16] = 0;
			ToUpper(name);
		}
		Drive* drive;
		MountDevice(&drive, name, heap);
		UnlockMounts();
		return drive != 0;
	}

	// FUNCTION: ENGINE 0x1064A520
	// Waits for the drive's pending requests before releasing it
	bool UnmountDrive(const char* device)
	{
		char name[17];
		LockMounts();
		if (device == 0)
		{
			strcpy(name, sDefaultDevice);
		}
		else
		{
			strncpy(name, device, 16);
			name[16] = 0;
			ToUpper(name);
		}
		int index = FindMount(name);
		if (index == -1)
		{
			UnlockMounts();
			return false;
		}
		Drive* drive = sMounts[index].drive;
		if (drive == 0)
		{
			UnlockMounts();
			return false;
		}
		sMounts[index].drive = 0;
		UnlockMounts();
		while (drive->FlushRequests())
		{
			FileSystemUpdate();
			ThreadSleep(0);
		}
		drive->Release();
		return true;
	}

	// FUNCTION: ENGINE 0x1064A5E0
	void ShutdownMounts()
	{
		if (sAutoMount)
		{
			for (unsigned int i = 0; i < 27; i++)
			{
				if (sMounts[i].drive != 0)
				{
					UnmountDrive(sMounts[i].name);
				}
			}
		}
		ShutdownMountsHook();
		ShutdownFiles();
		ShutdownInstanceDrives();
		ShutdownRequests();
		CriticalSectionDelete(sMountLock);
		sMountsReady = false;
	}

	// FUNCTION: ENGINE 0x1064A640
	void OpenFileAsync(IFile** file, const char* path, bool writable, int mode, int key, int unused1, int unused2, int unused3, int option)
	{
		const char* native = 0;
		const char* relative = 0;
		char device[0x14];
		char full[0x104];
		SplitPath(path, full, device, &relative, &native);
		LockMounts();
		int index = FindMount(device);
		Drive* drive = 0;
		if (index != -1)
		{
			drive = sMounts[index].drive;
		}
		if (drive == 0)
		{
			if (sAutoMount)
			{
				UnlockMounts();
				MountDrive(device, sMountsHeap);
				LockMounts();
				index = FindMount(device);
				if (index > -1)
				{
					drive = sMounts[index].drive;
				}
			}
			if (drive == 0)
			{
				*file = 0;
				UnlockMounts();
				return;
			}
		}

		const char* name = relative;
		if (drive->GetFlags() & 0x80)
		{
			name = native;
		}
		*file = new File(sMounts[index].drive, name, writable, mode, key, unused1, unused2, unused3, true, option);
		UnlockMounts();
	}

	// FUNCTION: ENGINE 0x1064A7B0
	void OpenFile(IFile** file, const char* path, bool writable, int mode, int key, int unused1, int unused2, int unused3, int option)
	{
		OpenFileAsync(file, path, writable, mode, key, unused1, unused2, unused3, option);
		if (*file != 0)
		{
			(*file)->Wait();
		}
	}

	// FUNCTION: ENGINE 0x1064A800
	void OpenSaveGameAsync(IFile** file, const char* path, bool writable, int mode, int a, int b, int key)
	{
		const char* native = 0;
		const char* relative = 0;
		char device[0x14];
		char full[0x104];
		SplitPath(path, full, device, &relative, &native);
		LockMounts();
		int index = FindMount(device);
		Drive* drive = 0;
		if (index != -1)
		{
			drive = sMounts[index].drive;
		}
		if (drive == 0)
		{
			if (sAutoMount)
			{
				UnlockMounts();
				MountDrive(device, sMountsHeap);
				LockMounts();
				index = FindMount(device);
				if (index > -1)
				{
					drive = sMounts[index].drive;
				}
			}
			if (drive == 0)
			{
				*file = 0;
				UnlockMounts();
				return;
			}
		}
		const char* name = relative;
		if (drive->GetFlags() & 0x80)
		{
			name = native;
		}
		*file = new File(sMounts[index].drive, name, writable, mode, a, b, key);
		UnlockMounts();
	}

	// FUNCTION: ENGINE 0x1064A960
	void OpenSaveGame(IFile** file, const char* path, bool writable, int mode, int a, int b, int key)
	{
		OpenSaveGameAsync(file, path, writable, mode, a, b, key);
		if (*file != 0)
		{
			(*file)->Wait();
		}
	}

	// FUNCTION: ENGINE 0x1064A9A0
	void OpenDriveAsync(IDrive** drive, const char* device, int key, int unused)
	{
		LockMounts();
		if (device == 0 || *device == 0)
		{
			device = sDefaultDevice;
		}
		char name[17];
		strncpy(name, device, 16);
		name[16] = 0;
		ToUpper(name);
		int index = FindMount(name);
		Drive* mounted = 0;
		if (index != -1)
		{
			mounted = sMounts[index].drive;
		}
		if (mounted == 0)
		{
			if (sAutoMount)
			{
				UnlockMounts();
				MountDrive(name, sMountsHeap);
				LockMounts();
				index = FindMount(name);
				if (index > -1)
				{
					mounted = sMounts[index].drive;
				}
			}
			if (mounted == 0)
			{
				*drive = 0;
				UnlockMounts();
				return;
			}
		}
		*drive = new InstanceDrive(sMounts[index].drive, key);
		UnlockMounts();
	}

	// FUNCTION: ENGINE 0x1064AAA0
	void OpenDrive(IDrive** drive, const char* device, int key, int unused)
	{
		OpenDriveAsync(drive, device, key, unused);
		if (*drive != 0)
		{
			(*drive)->Wait();
		}
	}

	// FUNCTION: ENGINE 0x1064AAD0
	void OpenCementLibraryAsync(ICementLibrary** library, const char* path, int a, int b, int heap, const char* source)
	{
		const char* native = 0;
		const char* relative = 0;
		char device[0x14];
		char full[0x104];
		SplitPath(path, full, device, &relative, &native);
		LockMounts();
		int index = FindMount(device);
		Drive* drive = 0;
		if (index != -1)
		{
			drive = sMounts[index].drive;
		}
		if (drive == 0)
		{
			if (sAutoMount)
			{
				UnlockMounts();
				MountDrive(device, sMountsHeap);
				LockMounts();
				index = FindMount(device);
				if (index > -1)
				{
					drive = sMounts[index].drive;
				}
			}
			if (drive == 0)
			{
				*library = 0;
				UnlockMounts();
				return;
			}
		}
		Drive* sourceDrive = drive;
		if (source != 0 && strcmp(source, device) != 0)
		{
			int sourceIndex = FindMount(source);
			Drive* other = 0;
			if (sourceIndex != -1)
			{
				other = sMounts[sourceIndex].drive;
			}
			if (other == 0)
			{
				if (sAutoMount)
				{
					UnlockMounts();
					MountDrive(source, sMountsHeap);
					LockMounts();
					sourceIndex = FindMount(source);
					if (sourceIndex > -1)
					{
						other = sMounts[sourceIndex].drive;
					}
				}
				if (other == 0)
				{
					*library = 0;
					UnlockMounts();
					return;
				}
			}
			sourceDrive = other;
		}
		const char* name = relative;
		if (sMounts[index].drive->GetFlags() & 0x80)
		{
			name = native;
		}
		CreateCementLibrary(library, sMounts[index].drive, name, a, b, heap, sourceDrive);
		UnlockMounts();
	}

	// FUNCTION: ENGINE 0x1064ACB0
	void OpenCementLibrary(ICementLibrary** library, const char* path, int a, int b, int heap, const char* source)
	{
		OpenCementLibraryAsync(library, path, a, b, heap, source);
		if (*library != 0)
		{
			(*library)->Wait();
		}
	}
}
