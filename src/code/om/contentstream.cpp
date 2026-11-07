// The om library's stream on the content load streams (0x10AAAC70 - 0x10AAADD0).
#include "code/om/contentstream.h"

namespace om
{
	// FUNCTION: ENGINE 0x10AAAC70
	ContentStream::ContentStream(const char* path, int unused)
	{
		content::CreateLoadStream(&stream, path, 0, 1);
	}

	// FUNCTION: ENGINE 0x10AAACA0
	ContentStream::ContentStream(content::LoadStream* newStream) :
		stream(newStream)
	{
		stream->AddRef();
	}

	// FUNCTION: ENGINE 0x10AAACD0
	bool ContentStream::Write(const void* data, unsigned int size)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x10AAACE0
	bool ContentStream::Read(void* data, unsigned int size)
	{
		return stream->Read(data, size, 1, 1);
	}

	// FUNCTION: ENGINE 0x10AAAD00
	bool ContentStream::GetSize(unsigned int* size)
	{
		*size = stream->GetSize() - stream->GetPosition();
		return true;
	}

	// FUNCTION: ENGINE 0x10AAAD30
	bool ContentStream::GetPosition(unsigned int* position)
	{
		*position = stream->GetPosition();
		return true;
	}

	// FUNCTION: ENGINE 0x10AAAD50
	bool ContentStream::Seek(unsigned int position)
	{
		unsigned int current = stream->GetPosition();
		if (position >= current)
		{
			stream->Skip(position - current);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10AAADD0
	String ContentStream::GetName()
	{
		const char* text = stream->GetName();
		String name(text, true);
		return String(name);
	}

	// FUNCTION: ENGINE 0x10AAAD80
	ContentStream::~ContentStream()
	{
		stream->Release();
	}
}
