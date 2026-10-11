// core::RamDrive (RTTI name; vftables 0x10E480C4 / 0x10E480B8 / 0x10E480A8): a drive held in memory (unit
// 0x10651D20 - 0x106523A3, file name file/common/ramdrive.cpp and member names guessed). Up to 32 files, found by the
// Hash32 of their path; each file is one 4 KB block of the drive's page pool (open count, size, page pointers)
// whose pages come from the same pool. The size given to the constructor sets the pool's page count.
#ifndef CORE_FILE_RAMDRIVE_H
#define CORE_FILE_RAMDRIVE_H

#include "code/core/file/drive.h"

namespace core
{
	struct IMemoryPool;

	class RamDrive : public Drive
	{
	public:
		// A file: one pool block
		struct RamFile
		{
			int opens;
			unsigned int size;
			unsigned char* pages[0x3FE];
		};

		// A slot of the file table; a file handle points at it
		struct Entry
		{
			unsigned int hash;
			RamFile* file;
		};

		RamDrive(const char* name, unsigned int size, int heap);
		virtual ~RamDrive();
		virtual void Lock();
		virtual void Unlock();
		// The drive name (as an int, the way the slot is declared)
		virtual int GetId();
		virtual int GetFlags();
		virtual int Mount();
		virtual int Open(const char* path, int mode, bool writable, int* handle, unsigned int* size);
		virtual int Close(int handle, const char* path);
		virtual int Read(int handle, const char* path, unsigned int a, unsigned int position, void* buffer, unsigned int size, unsigned int* done, int b);
		virtual int Write(int handle, const char* path, unsigned int a, unsigned int position, const void* buffer, unsigned int size, unsigned int* done, unsigned int* fileSize, int b);
		virtual int DestroyFile(const char* path);

		// Returns a file's pages to the pool
		void FreePages(RamFile* file);

		unsigned char lock[0x18];
		char name[0x14];
		Entry entries[0x20];
		int fileCount;
		IMemoryPool* pool;
	};
}

#endif
