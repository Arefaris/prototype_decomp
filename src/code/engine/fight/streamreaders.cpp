// The sources a fight reader takes its text and its bytes from (part of the unit 0x105A2440 - 0x105B3680; the
// declarations are in streamreaders.h).
#include "code/engine/fight/streamreaders.h"
#include <string.h>

namespace fight
{
	// ---- Text ------------------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105AB040
	BufferStringReader::BufferStringReader(const char* newBuffer, unsigned int newSize, const char* newName)
		: buffer(newBuffer), name(newName), size(newSize), position(0)
	{
	}

	// FUNCTION: ENGINE 0x105AB080
	BufferStringReader::~BufferStringReader()
	{
	}

	// FUNCTION: ENGINE 0x105AB070
	const char* BufferStringReader::GetName()
	{
		return name;
	}

	// FUNCTION: ENGINE 0x105AB090
	char BufferStringReader::Peek()
	{
		return position < size ? buffer[position] : 0;
	}

	// FUNCTION: ENGINE 0x105AB0B0
	char BufferStringReader::Read()
	{
		if (position >= size)
		{
			return 0;
		}
		char result = buffer[position];
		position = position + 1;
		return result;
	}

	// FUNCTION: ENGINE 0x105AB0D0
	bool BufferStringReader::AtEnd()
	{
		return position >= size;
	}

	// FUNCTION: ENGINE 0x105AB0E0
	IFileStringReader::IFileStringReader(core::IFile* newFile)
		: peeked(0), hasPeeked(false)
	{
		file = newFile;
		file->AddRef();
	}

	// FUNCTION: ENGINE 0x105AB110
	IFileStringReader::~IFileStringReader()
	{
		file->Release();
	}

	// FUNCTION: ENGINE 0x105AB130
	const char* IFileStringReader::GetName()
	{
		return file->GetName();
	}

	// FUNCTION: ENGINE 0x105AB140
	char IFileStringReader::Peek()
	{
		if (hasPeeked)
		{
			return peeked;
		}
		peeked = 0;
		file->Read(&peeked, 1, 1);
		file->Wait();
		hasPeeked = true;
		return peeked;
	}

	// FUNCTION: ENGINE 0x105AB180
	char IFileStringReader::Read()
	{
		char result = Peek();
		peeked = 0;
		hasPeeked = false;
		return result;
	}

	// FUNCTION: ENGINE 0x105AB1A0
	bool IFileStringReader::AtEnd()
	{
		if (hasPeeked)
		{
			return false;
		}
		file->Wait();
		unsigned int position;
		file->GetPosition(&position);
		unsigned int size;
		file->GetSize(&size);
		file->Wait();
		return position >= size;
	}

	// FUNCTION: ENGINE 0x105AB200
	StreamStringReader::StreamStringReader(content::ChunkStream* newStream, const char* newName)
		: name(newName), peeked(0), hasPeeked(false)
	{
		stream = newStream;
		stream->AddRef();
	}

	// FUNCTION: ENGINE 0x105AB230
	StreamStringReader::~StreamStringReader()
	{
		stream->Release();
	}

	// FUNCTION: ENGINE 0x105AB250
	const char* StreamStringReader::GetName()
	{
		return name;
	}

	// FUNCTION: ENGINE 0x105AB260
	char StreamStringReader::Peek()
	{
		if (hasPeeked)
		{
			return peeked;
		}
		peeked = 0;
		if (AtEnd())
		{
			hasPeeked = false;
			return peeked;
		}
		stream->Read(&peeked, 1, 1, 1);
		hasPeeked = true;
		return peeked;
	}

	// FUNCTION: ENGINE 0x105AB2B0
	char StreamStringReader::Read()
	{
		char result = Peek();
		peeked = 0;
		hasPeeked = false;
		return result;
	}

	// FUNCTION: ENGINE 0x105AB2D0
	bool StreamStringReader::AtEnd()
	{
		if (hasPeeked)
		{
			return false;
		}
		return stream->GetPosition() >= stream->GetSize();
	}

	// ---- Bytes -----------------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105AC8C0
	BufferDataReader::BufferDataReader(const char* newBuffer, unsigned int newSize, const char* newName)
		: buffer(newBuffer), name(newName), size(newSize), position(0)
	{
	}

	// FUNCTION: ENGINE 0x105AC590
	BufferDataReader::~BufferDataReader()
	{
	}

	// FUNCTION: ENGINE 0x105AC5A0
	const char* BufferDataReader::GetName()
	{
		return name;
	}

	// FUNCTION: ENGINE 0x105AC5B0
	unsigned int BufferDataReader::Read(void* destination, unsigned int count)
	{
		unsigned int left = size - position;
		if (left < count)
		{
			count = left;
		}
		memcpy(destination, buffer + position, count);
		position = position + count;
		return count;
	}

	// FUNCTION: ENGINE 0x105AC5F0
	bool BufferDataReader::AtEnd()
	{
		return position >= size;
	}

	// FUNCTION: ENGINE 0x105AC600
	IFileDataReader::IFileDataReader(core::IFile* newFile)
		: file(newFile)
	{
		file->AddRef();
	}

	// FUNCTION: ENGINE 0x105AC630
	IFileDataReader::~IFileDataReader()
	{
		file->Release();
	}

	// FUNCTION: ENGINE 0x105AC650
	const char* IFileDataReader::GetName()
	{
		return file->GetName();
	}

	// FUNCTION: ENGINE 0x105AC660
	unsigned int IFileDataReader::Read(void* destination, unsigned int count)
	{
		file->Read(destination, count, 1);
		file->Wait();
		return count;
	}

	// FUNCTION: ENGINE 0x105AC690
	bool IFileDataReader::AtEnd()
	{
		file->Wait();
		unsigned int position;
		file->GetPosition(&position);
		unsigned int size;
		file->GetSize(&size);
		file->Wait();
		return position >= size;
	}

	// FUNCTION: ENGINE 0x105AC6E0
	StreamDataReader::StreamDataReader(content::ChunkStream* newStream, const char* newName)
		: name(newName)
	{
		stream = newStream;
		stream->AddRef();
	}

	// FUNCTION: ENGINE 0x105AC710
	StreamDataReader::~StreamDataReader()
	{
		stream->Release();
	}

	// FUNCTION: ENGINE 0x105AC730
	const char* StreamDataReader::GetName()
	{
		return name;
	}

	// FUNCTION: ENGINE 0x105AC740
	unsigned int StreamDataReader::Read(void* destination, unsigned int count)
	{
		stream->Read(destination, count, 1, 1);
		return count;
	}

	// FUNCTION: ENGINE 0x105AC760
	bool StreamDataReader::AtEnd()
	{
		return stream->GetPosition() >= stream->GetSize();
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x105AAFF0
// FUNCTION: ENGINE 0x105AB020
