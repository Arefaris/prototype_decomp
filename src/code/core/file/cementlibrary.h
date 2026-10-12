// core::CementLibrary (RTTI name; vftables 0x10E48000 for ICementLibrary at 0, 0x10E47FEC for IFileCompletionCallback
// at 4, 0x10E47FE4 for Object at 8, 0x10E47FD4 for SafeRefCount at 0x10): an open Cement archive ("ATG CORE CEMENT
// LIBRARY"), a directory of files found by the hash of their path. Unit 0x10650290 - 0x10650DB4
// (code/core/src/file/common/cementer.cpp, assert path); member and method names guessed, apart from m_pDrive and
// m_pRegistrationDrive (assert text).
//
// Opening reads the header and the directory through the archive file's completion callback (steps 0 - 2), then
// registers the library on the registration drive (the drive's CementLibraryList), whose file opens look their path
// up in it; a found entry makes the opened file read through the archive's handle (FileCache::Open), packed
// entries through the list's shared unpack buffer.
#ifndef CORE_FILE_CEMENTLIBRARY_H
#define CORE_FILE_CEMENTLIBRARY_H

#include "code/core/file/file.h"

namespace core
{
	// core::ICementLibrary (RTTI name; 9 slots)
	struct ICementLibrary : IRefCount
	{
		// 0 while opening, 1 open, 2 failed
		virtual int GetState() = 0;
		// Pumps the file system until the library is no longer opening
		virtual void Wait() = 0;
		// Told (once) when the library has opened or failed
		virtual void SetCallback(IFileCompletionCallback* callback, void* userData) = 0;
		virtual bool IsOpen() = 0;
		// Opens the entry with the given path hash (named "0x<hash>") on the library's drive
		virtual void OpenFile(IFile** file, unsigned int hash, int key, int unused1, int unused2, int unused3) = 0;
		virtual void OpenFileWait(IFile** file, unsigned int hash, int key, int unused1, int unused2, int unused3) = 0;
	};

	// The archive header (0x3C bytes, read from offset 0)
	struct CementHeader
	{
		char magic[0x18];
		unsigned int unknown18;
		unsigned int unknown1C;
		unsigned char version;
		// 12-byte entries without packing (else 20-byte ones); a packed library must be read from its own drive
		unsigned char compact;
		unsigned char unknown22;
		unsigned char unknown23;
		unsigned int directoryOffset;
		unsigned int directorySize;
		unsigned int unknown2C;
		unsigned int unknown30;
		// Non-zero when entries are packed (the library then shares the drive's unpack buffer)
		unsigned int packed;
		unsigned int count;
	};

	// A directory entry, sorted by key (the hash of the path); compact entries end after size
	struct CementEntry
	{
		unsigned int key;
		unsigned int offset;
		unsigned int size;
		unsigned int unpackedSize;
		int mode;
	};

	// What a library can be opened from instead of reading the archive (header and directory already in memory)
	struct CementPreload
	{
		CementHeader* header;
		void* directory;
		int heap;
	};

	class CementLibrary : public ICementLibrary, public IFileCompletionCallback, public Object, public SafeRefCount
	{
	public:
		CementLibrary(Drive* drive, File* file, int pass, CementPreload* preload, Drive* registrationDrive);
		virtual ~CementLibrary();
		virtual void AddRef();
		virtual void Release();
		virtual int GetState();
		virtual void Wait();
		virtual void SetCallback(IFileCompletionCallback* callback, void* userData);
		virtual bool IsOpen();
		virtual void OpenFile(IFile** file, unsigned int hash, int key, int unused1, int unused2, int unused3);
		virtual void OpenFileWait(IFile** file, unsigned int hash, int key, int unused1, int unused2, int unused3);
		// The archive file's completion callback: userData is the opening step
		virtual void OnComplete(void* userData);
		virtual void Lock();
		virtual void Unlock();

		bool IsValid();
		// Sets the state and tells the callback
		void Finish(int state);
		int GetPass();
		// Whether the library holds the entry `key` (and then attaches `cache` to it)
		bool Find(int key, FileCache* cache);
		// The same for a path ("\" in front ignored)
		bool Matches(const char* path, FileCache* cache);

		Drive* m_pDrive;
		Drive* m_pRegistrationDrive;
		File* file;
		int state;
		CementHeader header;
		void* directory;
		// The next library of the registration drive's list
		CementLibrary* next;
		int pass;
		IFileCompletionCallback* callback;
		void* userData;
		bool preloaded;
		// The heap of the directory (the preload's, else the library's own)
		int directoryHeap;
	};

	// 0x10650D20: opens the archive at path on drive; its entries serve the file opens on registrationDrive
	void CreateCementLibrary(ICementLibrary** library, Drive* drive, const char* path, int pass, int heap, int preload,
		Drive* registrationDrive);
}

#endif
