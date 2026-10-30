// content::MemoryReadStream, MemoryWriteStream, NullWriteStream and CRCWriteStream (RTTI names; unit 0x1060E4D0 -
// 0x1060E690, member names guessed).
#include "code/content/metastream.h"
#include "code/content/streams.h"
#include "code/core/crc32.h"
#include <string.h>

namespace content
{
	// FUNCTION: ENGINE 0x1060E4D0
	void MemoryReadStream::Transfer(void* buffer, unsigned int length)
	{
		memcpy(buffer, (const unsigned char*)data + position, length);
		position += length;
	}

	// FUNCTION: ENGINE 0x1060E500
	unsigned int MemoryReadStream::GetPosition()
	{
		return position;
	}

	// FUNCTION: ENGINE 0x1060E510
	void MemoryReadStream::SetPosition(unsigned int newPosition)
	{
		position = newPosition;
	}

	// FUNCTION: ENGINE 0x1060E520
	unsigned int MemoryReadStream::GetSize()
	{
		return size;
	}

	// FUNCTION: ENGINE 0x1060E530
	void MemoryWriteStream::Write(const void* source, unsigned int length)
	{
		memcpy((unsigned char*)data + position, source, length);
		position += length;
	}

	// FUNCTION: ENGINE 0x1060E560
	unsigned int MemoryWriteStream::GetPosition()
	{
		return position;
	}

	// FUNCTION: ENGINE 0x1060E570
	void MemoryWriteStream::Seek(unsigned int newPosition)
	{
		position = newPosition;
	}

	// FUNCTION: ENGINE 0x1060E580
	unsigned int MemoryWriteStream::GetSize()
	{
		return size;
	}

	// FUNCTION: ENGINE 0x1060E590
	NullWriteStream::NullWriteStream()
	{
		size = 0;
		position = 0;
	}

	// FUNCTION: ENGINE 0x1060E5B0
	void NullWriteStream::Write(const void* source, unsigned int length)
	{
		position += length;
		if (position > size)
		{
			size = position;
		}
	}

	// FUNCTION: ENGINE 0x1060E5D0
	unsigned int NullWriteStream::GetPosition()
	{
		return position;
	}

	// FUNCTION: ENGINE 0x1060E5E0
	void NullWriteStream::Seek(unsigned int newPosition)
	{
		position = newPosition;
		if (newPosition > size)
		{
			size = newPosition;
		}
	}

	// FUNCTION: ENGINE 0x1060E600
	unsigned int NullWriteStream::GetSize()
	{
		return size;
	}

	// FUNCTION: ENGINE 0x1060E610
	CRCWriteStream::CRCWriteStream()
	{
		crc = 0xFFFFFFFF;
		core::BuildCrc32Table();
	}

	// FUNCTION: ENGINE 0x1060E630
	void CRCWriteStream::Write(const void* source, unsigned int length)
	{
		NullWriteStream::Write(source, length);
		crc = core::Crc32(source, length, crc);
	}

	// FUNCTION: ENGINE 0x1060E660
	unsigned int CRCWriteStream::GetCrc()
	{
		return crc;
	}

	// FUNCTION: ENGINE 0x1060E670
	MemoryReadStream::MemoryReadStream(const void* newData, unsigned int newSize)
	{
		data = newData;
		size = newSize;
		position = 0;
	}
}
