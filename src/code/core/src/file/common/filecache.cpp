#include <string.h>

#include "code/core/file/file.h"
#include "code/core/memory/align.h"
#include "code/core/memory/allocatorbase.h"
#include "code/core/pack.h"

namespace core
{
	// FUNCTION: ENGINE 0x10650DC0
	unsigned short ReadUInt16(const void* data)
	{
		return *(const unsigned short*)data;
	}

	// FUNCTION: ENGINE 0x10650DD0
	FileCache::FileCache()
		: source(0), offset(0), position(0), size(0), packedPosition(0), skip(0), packedSize(0), mode(0),
		granularity(0), buffer(0), bufferSize(0)
	{
	}

	// FUNCTION: ENGINE 0x10650E00
	FileCache::~FileCache()
	{
	}

	// FUNCTION: ENGINE 0x10650E10
	bool FileCache::IsActive()
	{
		return source != 0;
	}

	// FUNCTION: ENGINE 0x10650E20
	File* FileCache::GetSource()
	{
		return source;
	}

	// FUNCTION: ENGINE 0x10650E30
	unsigned int FileCache::GetOffset()
	{
		return offset;
	}

	// FUNCTION: ENGINE 0x10650E40
	unsigned int FileCache::GetSize()
	{
		return size;
	}

	// FUNCTION: ENGINE 0x10650E50
	void FileCache::Reset()
	{
		source->Release();
		source = 0;
	}

	// FUNCTION: ENGINE 0x10650E70
	int FileCache::ReadDirect(Drive* drive, int handle, const char* path, unsigned int a, unsigned int position,
		void* buffer, unsigned int size, unsigned int* done, int b)
	{
		int result = drive->Read(handle, path, a, offset + position, buffer, size, done, b);
		this->position = *done + position;
		packedPosition = this->position;
		skip = 0;
		return result;
	}

	// FUNCTION: ENGINE 0x10650ED0
	// EQUIVALENT: the same steps in the same order; the original keeps this in ebp (spilled), the partial count in
	// ebx and the kept bytes in esi, with the read count in memory (a branch where ours has a cmovb)
	int FileCache::ReadPacked(Drive* drive, int handle, const char* path, unsigned int a, unsigned int position,
		void* buffer, unsigned int size, unsigned int* done, int b)
	{
		if (position > this->size)
		{
			*done = size;
			return 1;
		}
		unsigned int remaining = size;
		if (position + size > this->size)
		{
			remaining = this->size - position;
		}
		unsigned int logical = this->position;
		unsigned int packed = packedPosition;
		unsigned int partial = skip;
		unsigned char* out = (unsigned char*)buffer;
		unsigned int kept = 0;
		while (remaining > 0)
		{
			unsigned int base = RoundDown(packed, granularity);
			unsigned int available = packedSize - base;
			unsigned int count = bufferSize;
			if (partial > 0)
			{
				count -= RoundUp(partial, granularity);
			}
			if (available < count)
			{
				count = available;
			}
			unsigned int read;
			int result = drive->Read(handle, path, a, offset + base + kept, this->buffer + kept,
				RoundUp(count - kept, granularity), &read, 1);
			if (result != 1)
			{
				return result;
			}
			unsigned char* chunk = this->buffer - base + packed;
			unsigned char* end = this->buffer + count;
			while (remaining != 0)
			{
				if (chunk + 4 >= end)
				{
					break;
				}
				unsigned short packedBytes = *(unsigned short*)chunk;
				unsigned short unpackedBytes = *(unsigned short*)(chunk + 2);
				if ((packedBytes == 0 && chunk + 4 + unpackedBytes > end) || (packedBytes > 0 && chunk + 4 + packedBytes > end))
				{
					break;
				}
				unsigned int left = unpackedBytes - partial;
				unsigned int take = left > remaining ? remaining : left;
				unsigned char* target = partial != 0 ? end : out;
				if (packedBytes == 0)
				{
					memcpy(target, chunk + 4, take + partial);
				}
				else
				{
					Unpack(chunk + 4, packedBytes, target, take + partial, unpackedBytes);
				}
				if (partial != 0)
				{
					memcpy(out, target + partial, take);
				}
				if (take != left)
				{
					partial = take;
				}
				else
				{
					packed += packedBytes + 4;
					partial = 0;
					chunk += packedBytes + 4;
				}
				logical += take;
				out += take;
				remaining -= take;
			}
			if (remaining != 0 && chunk != end)
			{
				kept = AlignUp<unsigned int>(end - chunk, granularity);
				memcpy(this->buffer, end - kept, kept);
			}
			else
			{
				kept = 0;
			}
		}
		this->position = logical;
		packedPosition = packed;
		skip = partial;
		*done = size;
		return 1;
	}

	// FUNCTION: ENGINE 0x10651130
	void FileCache::Open(File* source, unsigned int offset, unsigned int size, unsigned int packedSize, int mode,
		void* buffer, unsigned int bufferSize, int unused)
	{
		source->AddRef();
		this->source = source;
		this->offset = offset;
		for (File* file = source; file != 0; file = file->GetCache()->GetSource())
		{
			this->offset += file->GetCache()->GetOffset();
		}
		position = 0;
		packedPosition = 0;
		skip = 0;
		this->size = size;
		this->packedSize = packedSize;
		this->mode = mode;
		granularity = source->GetGranularity();
		this->buffer = (unsigned char*)buffer;
		this->bufferSize = bufferSize;
	}

	// FUNCTION: ENGINE 0x106511C0
	int FileCache::Read(Drive* drive, int handle, const char* path, unsigned int a, unsigned int position, void* buffer,
		unsigned int size, unsigned int* done, int b)
	{
		switch (mode)
		{
		case 0:
			return ReadDirect(drive, handle, path, a, position, buffer, size, done, b);
		case 1:
			return ReadPacked(drive, handle, path, a, position, buffer, size, done, b);
		}
		return 0;
	}
}
