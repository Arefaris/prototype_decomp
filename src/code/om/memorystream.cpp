// The om library's memory stream (0x105E4630 - 0x105E4780).
#include "code/om/memorystream.h"

namespace om
{
	// FUNCTION: ENGINE 0x105E4630
	MemoryStream::MemoryStream(void* newBegin, unsigned int newSize, bool newWriting) :
		size(newSize),
		begin(static_cast<unsigned char*>(newBegin)),
		cursor(static_cast<unsigned char*>(newBegin)),
		writing(newWriting)
	{
	}

	// FUNCTION: ENGINE 0x105E4690
	bool MemoryStream::Write(const void* data, unsigned int count)
	{
		if (static_cast<unsigned int>(begin + size - cursor) < count)
		{
			return false;
		}
		const unsigned char* source = static_cast<const unsigned char*>(data);
		unsigned char* destination = cursor;
		for (unsigned int i = 0; i < count; i++)
		{
			destination[i] = source[i];
		}
		cursor += count;
		return true;
	}

	// FUNCTION: ENGINE 0x105E46E0
	bool MemoryStream::Read(void* data, unsigned int count)
	{
		if (static_cast<unsigned int>(begin + size - cursor) < count)
		{
			return false;
		}
		const unsigned char* source = cursor;
		unsigned char* destination = static_cast<unsigned char*>(data);
		for (unsigned int i = 0; i < count; i++)
		{
			destination[i] = source[i];
		}
		cursor += count;
		return true;
	}

	// FUNCTION: ENGINE 0x105E4730
	bool MemoryStream::GetSize(unsigned int* result)
	{
		*result = begin + size - cursor;
		return true;
	}

	// FUNCTION: ENGINE 0x105E4750
	bool MemoryStream::GetPosition(unsigned int* position)
	{
		*position = cursor - begin;
		return true;
	}

	// FUNCTION: ENGINE 0x105E4770
	bool MemoryStream::Seek(unsigned int position)
	{
		cursor = begin + position;
		return true;
	}

	// FUNCTION: ENGINE 0x105E4780
	String MemoryStream::GetDescription()
	{
		return String("MemoryStream (unknown name)", false);
	}
}
