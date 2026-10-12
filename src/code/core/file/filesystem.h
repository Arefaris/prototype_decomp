// The file system entry points the engine calls (all names guessed): forwarders to the mounts (0x10643C00 -
// 0x10643D50), the path splitting the opens use, a path comparison and a path hash. Unit 0x10643C00 - 0x10643EE7
// (file name guessed; the language entry points after it may belong to the same original file).
#ifndef CORE_FILE_FILESYSTEM_H
#define CORE_FILE_FILESYSTEM_H

#include "code/core/file/mounts.h"

namespace core
{
	void FileSystemInit(unsigned int requests, unsigned int files, int value, int heap, unsigned int instances);
	void FileSystemShutdown();
	void FileSystemUpdate();
	void FileSystemSetMountPath(const char* device, const char* path);
	void FileSystemGetMountPath(const char* device, char* path);
	void FileSystemOpenFileAsync(IFile** file, const char* path, bool writable, int mode, int key, int unused1, int unused2, int unused3, int option);
	void FileSystemOpenFile(IFile** file, const char* path, bool writable, int mode, int key, int unused1, int unused2, int unused3, int option);
	void FileSystemOpenSaveGameAsync(IFile** file, const char* path, bool writable, int mode, int a, int b, int key);
	void FileSystemOpenSaveGame(IFile** file, const char* path, bool writable, int mode, int a, int b, int key);
	void FileSystemOpenDriveAsync(IDrive** drive, const char* device, int key, int unused);
	void FileSystemOpenDrive(IDrive** drive, const char* device, int key, int unused);
	bool FileSystemSetDefaultDevice(const char* device);
	void FileSystemGetDefaultDevice(char* device);
	void FileSystemOpenCementLibraryAsync(ICementLibrary** library, const char* path, int pass, int heap, int preload, const char* source);
	void FileSystemOpenCementLibrary(ICementLibrary** library, const char* path, int pass, int heap, int preload, const char* source);
	void FileSystemSetTimeout(int timeout);
	bool FileSystemMount(const char* device, int heap);
	bool FileSystemUnmount(const char* device);
	void FileSystemSetAutoMount(bool on);
	bool FileSystemMapDevice(const char* device, const char* path, int heap);
	void FileSystemUnmapDevice(const char* device);
	int FileSystemGetSlot();
	int FileSystemSamePath(const char* a, const char* b);
	unsigned int FileSystemHashPath(const char* path);
}

#endif
