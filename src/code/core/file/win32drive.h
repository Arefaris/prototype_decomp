// core::Win32Drive (RTTI name; vftables 0x10E48044 / 0x10E48038 / 0x10E48028): a drive on a Win32 volume ("c:" and
// so on; unit 0x106511E0 - 0x10651D1B, file name file/win32/win32drive.cpp and member names guessed). Files are Win32
// handles; paths are made absolute against the volume (or the current directory when it is on this volume); errors
// are mapped to the core's file error codes. The volume information (state, free space, 512-byte granularity,
// volume name) is refreshed when the first file opens and on every Mount, which fails when the volume serial changed.
#ifndef CORE_FILE_WIN32DRIVE_H
#define CORE_FILE_WIN32DRIVE_H

#include "code/core/file/drive.h"

extern "C" struct _WIN32_FIND_DATAA;

namespace core
{
	// What FindFirst / FindNext fill in (name guessed)
	struct DriveFindData
	{
		int directory;
		char name[0x101];
	};

	class Win32Drive : public Drive
	{
	public:
		Win32Drive(const char* name, int heap);
		virtual ~Win32Drive();
		virtual void Lock();
		virtual void Unlock();
		// The device name (as an int, the way the slot is declared)
		virtual int GetId();
		virtual int GetFlags();
		virtual int Mount();
		virtual int Open(const char* path, int mode, bool writable, int* handle, unsigned int* size);
		virtual int Close(int handle, const char* path);
		virtual int Commit(int handle, const char* path);
		virtual int Read(int handle, const char* path, unsigned int a, unsigned int position, void* buffer, unsigned int size, unsigned int* done, int b);
		virtual int Write(int handle, const char* path, unsigned int a, unsigned int position, const void* buffer, unsigned int size, unsigned int* done, unsigned int* fileSize, int b);
		virtual int CreateDirectory(const char* path);
		virtual int DestroyDirectory(const char* path);
		virtual int DestroyFile(const char* path);
		// path is the search pattern, out a DriveFindData (the slot's parameter types are Drive's)
		virtual int FindFirst(void* path, int out, int* handle, bool keep);
		virtual int FindNext(int* handle, void* out);
		virtual int FindClose(int* handle);

		// Reads the volume information into info; returns the volume serial
		unsigned int RefreshInfo();
		// The absolute Win32 path of a path on this drive
		void MakePath(const char* path, char* out, unsigned int size);
		int MapError(unsigned long error);
		int FillFindData(DriveFindData* out, _WIN32_FIND_DATAA* data, int* handle);

		int flags;
		unsigned int errorMode;
		int openCount;
		char name[0x10];
		bool unknownF0;
		unsigned int serial;
		// The current directory when it is on this volume (with a trailing back slash), else empty
		char directory[0x101];
		unsigned char lock[0x18];
	};
}

#endif
