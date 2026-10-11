// strncpy as the original used it; the define only silences VS 2005's deprecation warning
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>

#include "code/core/criticalsection.h"
#include "code/core/file/ramdrive.h"
#include "code/core/hash.h"
#include "code/core/memory/memorypool.h"
#include "code/core/strings.h"

namespace core
{
	const char* CoreName();

	// The pages a size takes
	static inline unsigned int PageCount(unsigned int size)
	{
		unsigned int count = size >> 12;
		if (size & 0xFFF)
		{
			count++;
		}
		return count;
	}

	// FUNCTION: ENGINE 0x10651D20
	void RamDrive::Lock()
	{
		CriticalSectionEnter(lock);
	}

	// FUNCTION: ENGINE 0x10651D30
	void RamDrive::Unlock()
	{
		CriticalSectionLeave(lock);
	}

	// FUNCTION: ENGINE 0x10651D40
	int RamDrive::GetId()
	{
		return (int)name;
	}

	// FUNCTION: ENGINE 0x10651D50
	int RamDrive::GetFlags()
	{
		return 0x21;
	}

	// FUNCTION: ENGINE 0x10651D60
	int RamDrive::Mount()
	{
		info.data[3] = 0x1000;
		pool->GetStat(3, &info.data[1]);
		info.data[2] = 0x20 - fileCount;
		info.data[0] = 0;
		strncpy((char*)&info.data[4], name, 0x41);
		((char*)&info)[0x50] = 0;
		error = 0;
		return 1;
	}

	// FUNCTION: ENGINE 0x10651DD0
	int RamDrive::Close(int handle, const char* path)
	{
		((Entry*)handle)->file->opens--;
		error = 0;
		return 1;
	}

	// FUNCTION: ENGINE 0x10651DF0
	int RamDrive::Read(int handle, const char* path, unsigned int a, unsigned int position, void* buffer,
		unsigned int size, unsigned int* done, int b)
	{
		RamFile* file = ((Entry*)handle)->file;
		*done = size;
		unsigned int page = position >> 12;
		unsigned int offset = position & 0xFFF;
		while (size != 0)
		{
			unsigned int count = 0x1000 - offset;
			if (count > size)
			{
				count = size;
			}
			memcpy(buffer, file->pages[page] + offset, count);
			buffer = (unsigned char*)buffer + count;
			page++;
			offset = 0;
			size -= count;
		}
		error = 0;
		return 1;
	}

	// FUNCTION: ENGINE 0x10651E80
	// EQUIVALENT: same blocks and order; the original keeps size in ebx, the page index in edi and the page pointer in
	// ebp (ours edi / ebp / ebx); allocation loop forms, an end local and a source pointer tried
	int RamDrive::Write(int handle, const char* path, unsigned int a, unsigned int position, const void* buffer,
		unsigned int size, unsigned int* done, unsigned int* fileSize, int b)
	{
		RamFile* file = ((Entry*)handle)->file;
		unsigned int end = position + size;
		if (end > file->size)
		{
			unsigned int first = PageCount(file->size);
			unsigned int last = PageCount(end);
			for (unsigned int i = first; i < last; i++)
			{
				file->pages[i] = (unsigned char*)pool->AllocBlock();
				if (file->pages[i] == 0)
				{
					error = 7;
					return 0;
				}
				file->size += 0x1000;
			}
			file->size = position + size;
		}
		*done = size;
		*fileSize = file->size;
		unsigned int page = position >> 12;
		unsigned int offset = position & 0xFFF;
		const unsigned char* source = (const unsigned char*)buffer;
		while (size != 0)
		{
			unsigned int count = 0x1000 - offset;
			if (count > size)
			{
				count = size;
			}
			memcpy(file->pages[page] + offset, source, count);
			source += count;
			page++;
			offset = 0;
			size -= count;
		}
		error = 0;
		return 1;
	}

	// FUNCTION: ENGINE 0x10651F90
	void RamDrive::FreePages(RamFile* file)
	{
		unsigned int count = PageCount(file->size);
		for (unsigned int i = 0; i < count; i++)
		{
			pool->Free(file->pages[i]);
		}
		file->size = 0;
	}

	// FUNCTION: ENGINE 0x10651FE0
	RamDrive::RamDrive(const char* name, unsigned int size, int heap)
		: fileCount(0)
	{
		CoreName();
		StrNCpy(this->name, name, 0x11u);
		CriticalSectionInit(lock);
		queue = new (heap) DriveThread(lock, heap);
		CreateMemoryPool((MemoryPool**)&pool, 0x1000, size >> 12, heap, 0, 0x10);
		for (unsigned int i = 0; i < 0x20; i++)
		{
			entries[i].file = 0;
		}
	}

	// FUNCTION: ENGINE 0x106520D0
	RamDrive::~RamDrive()
	{
		pool->SetSafetyMode(0);
		for (unsigned int i = 0; i < 0x20; i++)
		{
			if (entries[i].file != 0)
			{
				FreePages(entries[i].file);
				pool->Free(entries[i].file);
			}
		}
		pool->Release();
		queue->Release();
		CriticalSectionDelete(lock);
	}

	// FUNCTION: ENGINE 0x10652160
	int RamDrive::Open(const char* path, int mode, bool writable, int* handle, unsigned int* size)
	{
		if (*path == '\\')
		{
			path++;
		}
		unsigned int hash = Hash32(path, 0);
		Entry* free = 0;
		Entry* entry = 0;
		for (unsigned int i = 0; i < 0x20; i++)
		{
			if (entries[i].file != 0)
			{
				if (entries[i].hash == hash)
				{
					entry = &entries[i];
					break;
				}
			}
			else if (free == 0)
			{
				free = &entries[i];
			}
		}
		if (entry != 0)
		{
			if (mode == 3)
			{
				FreePages(entry->file);
			}
		}
		else
		{
			if (mode == 0)
			{
				error = 1;
				return 0;
			}
			if (free == 0)
			{
				error = 0x11;
				return 0;
			}
			free->file = (RamFile*)pool->AllocBlock();
			if (free->file == 0)
			{
				error = 7;
				return 0;
			}
			free->hash = hash;
			free->file->opens = 0;
			free->file->size = 0;
			fileCount++;
			entry = free;
		}
		*handle = (int)entry;
		*size = entry->file->size;
		entry->file->opens++;
		error = 0;
		return 1;
	}

	// FUNCTION: ENGINE 0x10652270
	int RamDrive::DestroyFile(const char* path)
	{
		if (*path == '\\')
		{
			path++;
		}
		unsigned int hash = Hash32(path, 0);
		Entry* entry = 0;
		for (unsigned int i = 0; i < 0x20; i++)
		{
			if (entries[i].file != 0 && entries[i].hash == hash)
			{
				entry = &entries[i];
				break;
			}
		}
		if (entry == 0)
		{
			error = 1;
			return 0;
		}
		FreePages(entry->file);
		pool->Free(entry->file);
		entry->file = 0;
		fileCount--;
		error = 0;
		return 1;
	}

	// FUNCTION: ENGINE 0x10652320
	void CreateRamDrive(Drive** drive, const char* device, const char* size, int heap)
	{
		*drive = new (heap) RamDrive(device, (unsigned int)size, heap);
	}
}
