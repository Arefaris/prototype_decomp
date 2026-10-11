// core::Drive (RTTI name; vftable 0x10E47ED4, 24 slots, IRefCount at 0, SafeRefCount at 4, IMutable at 12) as the
// file requests use it: only the virtual slots and non-virtual methods they call are named; the others are
// placeholders that keep the slot numbers. Nothing here is reconstructed yet (0x1064FB30 - 0x10650140).
#ifndef CORE_FILE_DRIVE_H
#define CORE_FILE_DRIVE_H

namespace core
{
	class Request;
	class FileCacheList;

	// core::IMutable (RTTI name; two slots): the lock interface of files and drives
	struct IMutable
	{
		virtual void Lock() = 0;
		virtual void Unlock() = 0;
	};

	// The drive description GetInfo returns (84 bytes; +0xC is copied into open files)
	struct DriveInfo
	{
		int data[21];
	};

	class Drive
	{
	public:
		virtual void AddRef() = 0;
		virtual void Release() = 0;
		virtual ~Drive();
		virtual void Slot3() = 0;
		virtual void Slot4() = 0;
		virtual void Slot5() = 0;
		virtual int CanCreateFile(int a, int b) = 0;
		virtual void Slot7() = 0;
		virtual void Slot8() = 0;
		// Makes the drive usable (the requests' default preparation step)
		virtual int Mount() = 0;
		virtual int Open(const char* path, int mode, bool flag, int* handle, unsigned int* size) = 0;
		virtual int OpenSaveGame(const char* path, int mode, bool flag, int a, int b, int* handle, unsigned int* size) = 0;
		virtual void Close(int handle, const char* path) = 0;
		virtual int Commit(int handle, const char* path) = 0;
		virtual int Read(int handle, const char* path, unsigned int a, unsigned int position, void* buffer, unsigned int size, unsigned int* done, int b) = 0;
		virtual int Write(int handle, const char* path, unsigned int a, unsigned int position, const void* buffer, unsigned int size, unsigned int* done, unsigned int* fileSize, int b) = 0;
		virtual int Format() = 0;
		virtual int CreateDirectory(const char* path) = 0;
		virtual int DestroyDirectory(const char* path) = 0;
		virtual int DestroyFile(const char* path) = 0;
		virtual int FindFirst(void* data, int a, int* handle, bool restart) = 0;
		virtual int FindNext(int* handle, void* data) = 0;
		virtual void FindClose(int* handle) = 0;
		virtual void Slot23() = 0;

		// 0x1064FB90: the last error
		int GetError();
		// 0x1064FBC0
		void SetState(int state);
		// 0x1064FBF0
		DriveInfo* GetInfo();
		// 0x1064FC00: hands a completion request to the drive's queue
		void Queue(Request* request);
		// 0x1064FEC0: cancels the requests of one file or drive instance
		void CancelRequests(void* owner, int key);
		// 0x1064FF10
		FileCacheList* GetCacheList();
	};
}

#endif
