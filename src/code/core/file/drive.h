// core::Drive (RTTI name; vftables 0x10E47ED4 for the interface at 0, 0x10E47ECC for Object at 4, 0x10E47EBC for
// SafeRefCount at 0xC): the abstract base of the drives (Win32Drive, RamDrive). Unit 0x1064FA90 - 0x10650290
// (file/common/drive.cpp, name guessed). Member names guessed.
#ifndef CORE_FILE_DRIVE_H
#define CORE_FILE_DRIVE_H

#include "code/core/memory/imemoryallocator.h"
#include "code/core/object.h"

namespace core
{
	class Request;
	class FileCache;

	// core::IMutable (RTTI name; two slots): the lock interface of files and drives
	struct IMutable
	{
		virtual void Lock() = 0;
		virtual void Unlock() = 0;
	};

	// core::SafeRefCount (RTTI name; vftable 0x10E47EAC): a reference count under the object's own lock
	class SafeRefCount : public IMutable
	{
	public:
		SafeRefCount(int initial)
			: count(initial)
		{
		}
		virtual ~SafeRefCount()
		{
		}
		void AddRef()
		{
			Lock();
			count++;
			Unlock();
		}
		// The count is parked at 500000 while the object destroys itself
		void Release()
		{
			Lock();
			if (--count == 0)
			{
				count = 500000;
				Unlock();
				delete this;
				return;
			}
			Unlock();
		}

		int count;
	};

	// The drive description GetInfo returns (84 bytes; +0xC is copied into open files)
	struct DriveInfo
	{
		int data[21];
	};

	// The list of file caches a drive keeps, walked in two passes (0x3C bytes; methods 0x10650540 - 0x10650670)
	class FileCacheList
	{
	public:
		// 0x10650B60 / 0x10650540
		FileCacheList();
		~FileCacheList();
		// 0x10650580 / 0x106505D0
		void Add(FileCache* cache);
		void Remove(FileCache* cache);
		void Begin(int pass);
		FileCache* Next();
		void End();

		unsigned char data[0x3C];
	};

	// The request queue a drive submits to (methods 0x106524C0 - 0x10652670, not reconstructed)
	class RequestQueue
	{
	public:
		int Submit(Request* request, int key, int flags);
		void Cancel(void* owner, int key);
		void Flush();
		void Restart(int value);
	};

	// Told when a faulted drive is updated while held exclusively (slot 0)
	struct IDriveFaultHandler
	{
		virtual int OnFault(int error, int id, int a, int b, int value) = 0;
	};

	// What a drive fault carries (slots 5 and 6 read by Configure and Update)
	struct IDriveFault
	{
		virtual void Slot0() = 0;
		virtual void Slot1() = 0;
		virtual void Slot2() = 0;
		virtual void Slot3() = 0;
		virtual void Slot4() = 0;
		virtual int GetB() = 0;
		virtual int GetA() = 0;
	};

	// The drive (24 virtual slots on IRefCount; the pure ones are the concrete drives')
	class Drive : public IRefCount, public Object, public SafeRefCount
	{
	public:
		Drive();
		virtual ~Drive();
		virtual void AddRef();
		virtual void Release();
		// Runs the finished completion requests of the calling thread and reports a fault to the holder
		virtual void Update();
		virtual int GetId() = 0;
		virtual int Slot5(int a, int b);
		virtual int CanCreateFile(int a, int b);
		virtual bool Slot7(int a, int b);
		// Bit 0: space checks; bit 7: the drive hides its file names
		virtual unsigned char GetFlags() = 0;
		// Makes the drive usable (the requests' default preparation step)
		virtual int Mount() = 0;
		virtual int Open(const char* path, int mode, bool flag, int* handle, unsigned int* size);
		virtual int OpenSaveGame(const char* path, int mode, bool flag, int a, int b, int* handle, unsigned int* size);
		virtual void Close(int handle, const char* path) = 0;
		virtual int Commit(int handle, const char* path);
		virtual int Read(int handle, const char* path, unsigned int a, unsigned int position, void* buffer, unsigned int size, unsigned int* done, int b) = 0;
		virtual int Write(int handle, const char* path, unsigned int a, unsigned int position, const void* buffer, unsigned int size, unsigned int* done, unsigned int* fileSize, int b);
		virtual int Format();
		virtual int CreateDirectory(const char* path);
		virtual int DestroyDirectory(const char* path);
		virtual int DestroyFile(const char* path);
		virtual int FindFirst(void* data, int a, int* handle, bool restart);
		virtual int FindNext(int* handle, void* data);
		virtual int FindClose(int* handle);
		virtual void Slot23(int value);

		// The last error
		int GetError();
		void SetState(int state);
		DriveInfo* GetInfo();
		// Appends a completion request to the drive's queue
		void Queue(Request* request);
		// Hands a request to the drive's request queue (flags 1: ahead of the others); null requests are allowed
		int Submit(Request* request, int key, int flags);
		// Cancels the requests of one file or drive instance
		void CancelRequests(void* owner, int key);
		void FlushRequests();
		bool HasCompletions();
		void AddCache(FileCache* cache);
		void RemoveCache(FileCache* cache);
		FileCacheList* GetCacheList();
		// The state calls drive instances forward (names guessed from the fields they set)
		void BeginExclusive(IDriveFaultHandler* handler, int value);
		void EndExclusive(int a);
		void Suspend(void* semaphore);
		void Resume(void* semaphore);
		void SetMode(int mode);
		int GetMode();
		void ClearFault(int value);
		bool IsFaulted();
		void SetFault(IDriveFault* fault);
		bool Configure(int* a, int* b);
		void SetFlag(bool flag);
		bool GetFlag();

		FileCacheList caches;
		Request* first;
		Request* last;
		int mode;
		void* semaphore;
		int thread;
		IDriveFaultHandler* handler;
		int value;
		bool faulted;
		IDriveFault* fault;
		bool flag;
		bool busy;
		DriveInfo info;
		int error;
		RequestQueue* queue;
	};
}

#endif
