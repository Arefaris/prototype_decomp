// core::File (vftables 0x10E47C84 / 0x10E47C78) and core::InstanceDrive (0x10E47D2C / 0x10E47D1C), RTTI names, as
// the file requests see them: the interface slots they call, the fields they touch (offsets from the requests'
// code; the rest is padding) and the non-virtual methods. Not reconstructed yet (0x1064DF30 - 0x1064F760);
// placeholder slots keep the numbering. Field names guessed.
#ifndef CORE_FILE_FILE_H
#define CORE_FILE_FILE_H

#include "code/core/file/drive.h"
#include "code/core/memory/imemoryallocator.h"

namespace core
{
	class Request;
	struct ICompletionCallback;

	// core::IFile (33 slots). The asynchronous calls queue a request on the drive and return what the drive's
	// Submit answers; the ...Wait forms queue and then wait until the file has no pending request.
	struct IFile : IRefCount
	{
		virtual int Read(void* buffer, unsigned int size, int option) = 0;
		virtual int Write(const void* buffer, unsigned int size, int option) = 0;
		virtual int SetPosition(unsigned int position) = 0;
		virtual int GetPosition(unsigned int* position) = 0;
		virtual int GetSize(unsigned int* size) = 0;
		virtual int Commit() = 0;
		virtual void ReadWait(void* buffer, unsigned int size, int option) = 0;
		virtual void WriteWait(const void* buffer, unsigned int size, int option) = 0;
		virtual void SetPositionWait(unsigned int position) = 0;
		virtual void GetPositionWait(unsigned int* position) = 0;
		virtual void GetSizeWait(unsigned int* size) = 0;
		virtual void CommitWait() = 0;
		virtual unsigned int GetCurrentSize() = 0;
		virtual int GetGranularity() = 0;
		virtual int Cancel() = 0;
		virtual int Notify(ICompletionCallback* callback, void* userData) = 0;
		virtual int Signal(void* event) = 0;
		virtual bool IsIdle() = 0;
		virtual void Wait() = 0;
		virtual void WaitSignal() = 0;
		virtual int GetError() = 0;
		virtual bool IsOpen() = 0;
		// The path, or null when the drive hides its names
		virtual const char* GetName() = 0;
		virtual const char* GetPath() = 0;
		virtual int GetDriveId() = 0;
		virtual void SetUnused(int value) = 0;
		virtual int GetKey() = 0;
		virtual bool GetFlag() = 0;
		virtual void SetField12C(unsigned int value) = 0;
		virtual class FileCache* GetCache() = 0;
	};

	// The read cache inside a file (0x30 bytes at +0x138); methods at 0x10650AB0 - 0x106511C0
	class FileCache
	{
	public:
		// 0x10650DD0 / 0x10650E00
		FileCache();
		~FileCache();
		// 0x10650E10
		bool IsActive();
		// 0x10650E20: the file whose handle the cache shares
		class File* GetSource();
		// 0x10650E40
		unsigned int GetSize();
		// 0x10650E50
		void Reset();
		// 0x10650CF0: whether this cache holds `path` (and then attaches `target` to it)
		bool Matches(const char* path, FileCache* target);
		// 0x106511C0
		int Read(Drive* drive, int handle, const char* path, unsigned int a, unsigned int position, void* buffer, unsigned int size, unsigned int* done, int b);

		unsigned char data[0x30];
	};

	// The drive's list of file caches, walked in two passes (0x10650640 - 0x10650670)
	class FileCacheList
	{
	public:
		void Begin(int pass);
		FileCache* Next();
		void End();
	};

	// The reference-counted table an open-by-key request looks its file up in
	class FileKeyTable
	{
	public:
		virtual void AddRef() = 0;
		virtual void Release() = 0;

		// 0x10650AB0
		bool Find(int key, FileCache* cache);
	};

	// core::File (vftables 0x10E47C84 / 0x10E47C78): an open file on a drive. Files come from one pool ("File",
	// 0x174-byte blocks) and are listed in a table by pool index; their IMutable lock is the global file lock.
	// Unit 0x1064DF40 - 0x1064E9DF (code/core/src/file/common/file.cpp).
	class File : public IFile, public IMutable
	{
	public:
		// Queues a save-game open
		File(Drive* drive, const char* path, bool writable, int mode, int a, int b, int key);
		// Queues an open when `open` is set
		File(Drive* drive, const char* path, bool writable, int mode, int key, int unused1, int unused2, int unused3, bool open, int option);
		virtual ~File();
		virtual void AddRef();
		virtual void Release();
		virtual int Read(void* buffer, unsigned int size, int option);
		virtual int Write(const void* buffer, unsigned int size, int option);
		virtual int SetPosition(unsigned int position);
		virtual int GetPosition(unsigned int* position);
		virtual int GetSize(unsigned int* size);
		virtual int Commit();
		virtual void ReadWait(void* buffer, unsigned int size, int option);
		virtual void WriteWait(const void* buffer, unsigned int size, int option);
		virtual void SetPositionWait(unsigned int position);
		virtual void GetPositionWait(unsigned int* position);
		virtual void GetSizeWait(unsigned int* size);
		virtual void CommitWait();
		virtual unsigned int GetCurrentSize();
		virtual int GetGranularity();
		virtual int Cancel();
		virtual int Notify(ICompletionCallback* callback, void* userData);
		virtual int Signal(void* event);
		virtual bool IsIdle();
		virtual void Wait();
		virtual void WaitSignal();
		virtual int GetError();
		virtual bool IsOpen();
		virtual const char* GetName();
		virtual const char* GetPath();
		virtual int GetDriveId();
		virtual void SetUnused(int value);
		virtual int GetKey();
		virtual bool GetFlag();
		virtual void SetField12C(unsigned int value);
		virtual FileCache* GetCache();
		virtual void Lock();
		virtual void Unlock();

		static void* operator new(unsigned int size);
		static void operator delete(void* block);

		// 0x1064E790: whether this file may share the handle of a file on `drive` (it moves to that drive when it
		// is idle and closed)
		bool CanShare(Drive* drive);
		// 0x1064E7F0 / 0x1064E810: a request starts / ends on this file
		void BeginRequest();
		void EndRequest();

		int refCount;
		Drive* drive;
		int key;
		int error;
		unsigned int pending;
		// Signalled when the last pending request ends (an event with a count, see core::EventInit)
		int event[2];
		bool hasEvent;
		bool waiting;
		bool open;
		bool writable;
		char path[0x101];
		unsigned int field12C;
		unsigned int position;
		unsigned int size;
		FileCache cache;
		int handle;
		bool flag;
		int granularity;
	};

	// The file pool and table of open files (the pool index is the table index)
	void InitFiles(unsigned int count, int heap);
	void ShutdownFiles();
	// Reports every file still open (when the pool runs dry)
	void ReportOpenFiles();

	// core::IDrive (45 slots): a drive as one owner (key) sees it; the requests and waits work like IFile's
	struct IDrive : IRefCount
	{
		virtual unsigned char GetFlags() = 0;
		virtual int GetMedia(DriveInfo* info) = 0;
		virtual int CanCreateFile(int a, int b, int* result) = 0;
		virtual int Format() = 0;
		virtual int CreateDirectory(const char* path) = 0;
		virtual int DestroyDirectory(const char* path) = 0;
		virtual int FindFirst(const char* path, int flags) = 0;
		virtual int FindNext(void* data) = 0;
		virtual int DestroyFile(const char* path) = 0;
		virtual void GetMediaWait(DriveInfo* info) = 0;
		virtual void CanCreateFileWait(int a, int b, int* result) = 0;
		virtual void FormatWait() = 0;
		virtual void CreateDirectoryWait(const char* path) = 0;
		virtual void DestroyDirectoryWait(const char* path) = 0;
		virtual void FindFirstWait(const char* path, int flags) = 0;
		virtual void FindNextWait(void* data) = 0;
		virtual void DestroyFileWait(const char* path) = 0;
		virtual int Cancel() = 0;
		virtual int Notify(ICompletionCallback* callback, void* userData) = 0;
		virtual int Signal(void* event) = 0;
		virtual bool IsIdle() = 0;
		virtual void Wait() = 0;
		virtual void WaitSignal() = 0;
		virtual int GetError() = 0;
		virtual void BeginExclusive(int a, int b) = 0;
		virtual void EndExclusive(int a) = 0;
		virtual void Suspend(int value) = 0;
		virtual void Resume(int value) = 0;
		virtual bool IsFaulted() = 0;
		virtual void ClearFault(int value) = 0;
		virtual void SetMode(int mode) = 0;
		virtual void SetFlag(bool flag) = 0;
		virtual void Configure(int a, int b) = 0;
		virtual void OpenFile(IFile** file, const char* path, bool writable, int mode, int key, int unused1, int unused2, int unused3, int option) = 0;
		virtual void OpenFileWait(IFile** file, const char* path, bool writable, int mode, int key, int unused1, int unused2, int unused3, int option) = 0;
		virtual void OpenSaveGame(IFile** file, const char* path, bool writable, int mode, int a, int b, int key) = 0;
		virtual void OpenSaveGameWait(IFile** file, const char* path, bool writable, int mode, int a, int b, int key) = 0;
		virtual void SetUnused(int value) = 0;
		virtual int GetKey() = 0;
		virtual int GetDriveId() = 0;
		virtual int GetDriveSlot5(int a, int b) = 0;
		virtual bool GetDriveSlot7(int a, int b) = 0;
	};

	// 0x10643D60: splits a path into the drive's full path, the device name and the relative and native forms
	void SplitPath(const char* path, char* full, char* device, const char** relative, const char** native);

	// core::InstanceDrive (vftables 0x10E47D2C / 0x10E47D1C): one owner's handle on a drive. Instances come from
	// one pool ("InstanceDrive", 0x30-byte blocks); their IMutable lock is the global instance lock. Unit
	// 0x1064EB00 - 0x1064F805 (file/common/instancedrive.cpp, name guessed).
	class InstanceDrive : public IDrive, public IMutable
	{
	public:
		InstanceDrive(Drive* drive, int key);
		virtual ~InstanceDrive();
		virtual void AddRef();
		virtual void Release();
		virtual unsigned char GetFlags();
		virtual int GetMedia(DriveInfo* info);
		virtual int CanCreateFile(int a, int b, int* result);
		virtual int Format();
		virtual int CreateDirectory(const char* path);
		virtual int DestroyDirectory(const char* path);
		virtual int FindFirst(const char* path, int flags);
		virtual int FindNext(void* data);
		virtual int DestroyFile(const char* path);
		virtual void GetMediaWait(DriveInfo* info);
		virtual void CanCreateFileWait(int a, int b, int* result);
		virtual void FormatWait();
		virtual void CreateDirectoryWait(const char* path);
		virtual void DestroyDirectoryWait(const char* path);
		virtual void FindFirstWait(const char* path, int flags);
		virtual void FindNextWait(void* data);
		virtual void DestroyFileWait(const char* path);
		virtual int Cancel();
		virtual int Notify(ICompletionCallback* callback, void* userData);
		virtual int Signal(void* event);
		virtual bool IsIdle();
		virtual void Wait();
		virtual void WaitSignal();
		virtual int GetError();
		virtual void BeginExclusive(int a, int b);
		virtual void EndExclusive(int a);
		virtual void Suspend(int value);
		virtual void Resume(int value);
		virtual bool IsFaulted();
		virtual void ClearFault(int value);
		virtual void SetMode(int mode);
		virtual void SetFlag(bool flag);
		virtual void Configure(int a, int b);
		virtual void OpenFile(IFile** file, const char* path, bool writable, int mode, int key, int unused1, int unused2, int unused3, int option);
		virtual void OpenFileWait(IFile** file, const char* path, bool writable, int mode, int key, int unused1, int unused2, int unused3, int option);
		virtual void OpenSaveGame(IFile** file, const char* path, bool writable, int mode, int a, int b, int key);
		virtual void OpenSaveGameWait(IFile** file, const char* path, bool writable, int mode, int a, int b, int key);
		virtual void SetUnused(int value);
		virtual int GetKey();
		virtual int GetDriveId();
		virtual int GetDriveSlot5(int a, int b);
		virtual bool GetDriveSlot7(int a, int b);
		virtual void Lock();
		virtual void Unlock();

		static void* operator new(unsigned int size);
		static void operator delete(void* block);

		// 0x1064F6B0 / 0x1064F6D0: a request starts / ends on this drive instance
		void BeginRequest();
		void EndRequest();

		int refCount;
		Drive* drive;
		int key;
		unsigned int pending;
		int event[2];
		bool hasEvent;
		bool waiting;
		int error;
		int findHandle;
		bool searching;
	};

	void InitInstanceDrives(unsigned int count, int heap);
	void ShutdownInstanceDrives();
}

#endif
