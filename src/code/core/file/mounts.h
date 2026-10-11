// The device mounts of the file system (all names guessed): up to 27 devices ("C:", "APP:", ...) each with a drive
// and a root path, the default device, and the file / drive / Cement library opens that look the device of a path
// up (mounting it on demand while automatic mounting is on). Unit 0x10649F60 - 0x1064ACE5 (no assert path; file
// name guessed). The engine calls these through the forwarders 0x10643C00 - 0x10643D50.
#ifndef CORE_FILE_MOUNTS_H
#define CORE_FILE_MOUNTS_H

#include "code/core/file/file.h"

namespace core
{
	// core::ICementLibrary (RTTI name; 9 slots): an open Cement archive
	struct ICementLibrary : IRefCount
	{
		virtual void Slot3() = 0;
		virtual void Wait() = 0;
	};

	struct Mount
	{
		char name[17];
		Drive* drive;
		char path[0x104];
	};

	void InitMounts(unsigned int requests, unsigned int files, int value, int heap, unsigned int instances);
	void LockMounts();
	void UnlockMounts();
	// Updates every mounted drive (outside the lock)
	void UpdateMounts();
	// A device name that IsValidDevice accepts becomes the default device
	bool SetDefaultDevice(const char* device);
	void GetDefaultDevice(char* device);
	int GetMountsValue();
	void SetFileTimeout(int timeout);
	int GetFileTimeout();
	void SetAutoMount(bool on);
	bool MapDevice(const char* device, const char* path, int heap);
	void UnmapDevice(const char* device);
	int GetMountsSlot();
	// The mount index of a device, -1 when it is not mounted
	int FindMount(const char* device);
	// The device's drive: an existing one (returns false), a new one, or none when the table is full
	bool MountDevice(Drive** drive, const char* device, int heap);
	void SetMountPath(const char* device, const char* path);
	void GetMountPath(const char* device, char* path);
	// Null mounts the default device; true when the device has a drive
	bool MountDrive(const char* device, int heap);
	bool UnmountDrive(const char* device);
	void ShutdownMounts();
	void OpenFileAsync(IFile** file, const char* path, bool writable, int mode, int key, int unused1, int unused2, int unused3, int option);
	void OpenFile(IFile** file, const char* path, bool writable, int mode, int key, int unused1, int unused2, int unused3, int option);
	void OpenSaveGameAsync(IFile** file, const char* path, bool writable, int mode, int a, int b, int key);
	void OpenSaveGame(IFile** file, const char* path, bool writable, int mode, int a, int b, int key);
	// Null or "" opens the default device
	void OpenDriveAsync(IDrive** drive, const char* device, int key, int unused);
	void OpenDrive(IDrive** drive, const char* device, int key, int unused);
	// The archive's files can come from another device (null: the archive's own)
	void OpenCementLibraryAsync(ICementLibrary** library, const char* path, int a, int b, int heap, const char* source);
	void OpenCementLibrary(ICementLibrary** library, const char* path, int a, int b, int heap, const char* source);

	// The Win32 devices (0x1064F810 - 0x1064FA88, not reconstructed): the current drive letter, the names mapped to
	// paths, whether a device exists and the drive behind it
	void GetCurrentDevice(char* device);
	bool AddDeviceMapping(const char* device, const char* path, int heap);
	void RemoveDeviceMapping(const char* device);
	bool IsValidDevice(const char* device);
	void CreateDeviceDrive(Drive** drive, const char* device, int heap, const char* path);
	// 0x10650D20 (not reconstructed)
	void CreateCementLibrary(ICementLibrary** library, Drive* drive, const char* path, int a, int b, int heap, Drive* source);
	// 0x1064C470 / 0x1064C480: empty start-up and shut-down hooks; 0x1064C490 returns 0
	void InitMountsHook();
	void ShutdownMountsHook();
	int GetMountsSlotValue();
	// 0x10643C20: the engine's entry to UpdateMounts
	void FileSystemUpdate();
}

#endif
