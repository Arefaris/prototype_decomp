// content::ChunkStream and content::ChunkReader: the reads of the chunk loaders (unit 0x105FF580 - 0x105FF690; the file
// name is guessed).
#include "code/content/chunkhandler.h"

namespace content
{
	// FUNCTION: ENGINE 0x105FF580
	unsigned int ChunkStream::ReadUInt()
	{
		unsigned int value;
		Read(&value, 1, 4, 1);
		return value;
	}

	// FUNCTION: ENGINE 0x105FF5A0
	unsigned short ChunkStream::ReadUShort()
	{
		unsigned short value;
		Read(&value, 1, 2, 1);
		return value;
	}

	// FUNCTION: ENGINE 0x105FF5C0
	unsigned char ChunkStream::ReadUChar()
	{
		unsigned char value;
		Read(&value, 1, 1, 1);
		return value;
	}

	// FUNCTION: ENGINE 0x105FF5E0
	unsigned int ChunkReader::ReadUnsigned()
	{
		unsigned int value;
		Read(&value, 1, 4, 1);
		return value;
	}

	// FUNCTION: ENGINE 0x105FF600
	unsigned short ChunkReader::ReadUShort()
	{
		unsigned short value;
		Read(&value, 1, 2, 1);
		return value;
	}

	// FUNCTION: ENGINE 0x105FF620
	char* ChunkReader::ReadString(char* buffer)
	{
		unsigned char stored;
		Read(&stored, 1, 1, 1);
		unsigned int length = stored;
		Read(buffer, length, 1, 1);
		buffer[length] = 0;
		return buffer;
	}

	// FUNCTION: ENGINE 0x105FF670
	void ChunkReader::ReadData(void* destination, unsigned int count, unsigned int size)
	{
		Read(destination, count, size, 1);
	}
}
