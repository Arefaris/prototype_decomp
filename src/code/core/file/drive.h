// core::Drive (RTTI name; vftables 0x10E47ED4 for the interface at 0, 0x10E47ECC for Object at 4, 0x10E47EBC for
// SafeRefCount at 0xC): the abstract base of the drives (Win32Drive, RamDrive). Unit 0x1064FA90 - 0x10650290
// (file/common/drive.cpp, name guessed). Member names guessed.
#ifndef CORE_FILE_DRIVE_H
#define CORE_FILE_DRIVE_H

#include "code/core/memory/imemoryallocator.h"
#include "code/core/object.h"
#include "code/core/thread.h"

namespace core
{
	class Request;
	class Drive;
	class FileCache;
	class CementLibrary;

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

	// The Cement libraries registered on a drive, in two lists (by the library's pass: the file opens search list 0
	// before trying the drive itself and list 1 after it), and the buffer the packed library entries unpack through
	// (shared, reference counted). 0x3C bytes; methods 0x10650540 - 0x10650716 and 0x10650B60 (cementer.cpp).
	class CementLibraryList
	{
	public:
		CementLibraryList();
		~CementLibraryList();
		void Add(CementLibrary* library);
		void Remove(CementLibrary* library);
		// Locks the list and starts a walk over one of the two lists
		void Begin(int pass);
		CementLibrary* Next();
		// Ends the walk and unlocks the list
		void End();
		void GetBuffer(void** buffer, unsigned int* size);
		// The first reference allocates the buffer (the mounts' buffer size rounded up to `round`)
		void AcquireBuffer(int heap, unsigned int align, unsigned int round);
		void ReleaseBuffer();

		CementLibrary* heads[2];
		CementLibrary* tails[2];
		CementLibrary* cursor;
		unsigned char section[0x18];
		void* buffer;
		unsigned int bufferSize;
		int bufferRefs;
		int bufferHeap;
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

	// core::DriveThread (RTTI name; vftables 0x10E48140 / 0x10E48138 / 0x10E48128): the thread that executes a
	// drive's requests from three queues (by key, the first non-empty one first) under the drive's lock (0x100 bytes;
	// unit 0x106523B0 - 0x10652A83, file name file/common/drivethread.cpp and member names guessed). A request that
	// finds the drive faulted waits (with the drive told about it) until ClearFault restarts the thread.
	class DriveThread : public IRefCount, public Object, public SafeRefCount
	{
	public:
		DriveThread(void* lock, int heap);
		virtual ~DriveThread();
		virtual void AddRef();
		virtual void Release();
		virtual void Lock();
		virtual void Unlock();

		// Queues a request (front: ahead of the others of its key) and wakes the thread
		int Submit(Request* request, int key, bool front);
		void Cancel(void* owner, int key);
		// Whether requests are still queued
		bool Flush();
		// Wakes the thread that waits on a fault (retry: run the request again)
		void Restart(int retry);
		void WaitFault(Drive* drive, Request* request);
		// Takes the next request off the queues (the current one from now on)
		Request* Next(int* key);
		bool IsCancelled();
		// Deletes the current request
		void FinishCurrent();
		static int Run(void* thread);

		void* lock;
		Thread thread;
		bool quit;
		void* semaphore;
		Request* heads[3];
		Request* tails[3];
		void* faultSemaphore;
		unsigned char retry;
		int pending;
		Request* current;
		bool cancelled;
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
		virtual int GetFlags() = 0;
		// Makes the drive usable (the requests' default preparation step)
		virtual int Mount() = 0;
		virtual int Open(const char* path, int mode, bool flag, int* handle, unsigned int* size);
		virtual int OpenSaveGame(const char* path, int mode, bool flag, int a, int b, int* handle, unsigned int* size);
		virtual int Close(int handle, const char* path) = 0;
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
		int Submit(Request* request, int key, bool front);
		// Cancels the requests of one file or drive instance
		void CancelRequests(void* owner, int key);
		// Whether requests are still queued
		bool FlushRequests();
		bool HasCompletions();
		void AddLibrary(CementLibrary* library);
		void RemoveLibrary(CementLibrary* library);
		CementLibraryList* GetLibraries();
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

		CementLibraryList libraries;
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
		DriveThread* queue;
	};
}

#endif
