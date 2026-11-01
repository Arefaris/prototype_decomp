// The wide character buffer the online code keeps names in (engine::WideStringBuffer; code/engine/online/widestringbuffer.cpp, the
// file name is a guess; the unit starts at 0x108A5560). Names are guesses.
#include "code/core/textconvert.h"
#include "code/engine/online/olsfriend.h"
#include <new>

namespace engine
{
	// FUNCTION: ENGINE 0x108A5560
	WideStringBuffer::WideStringBuffer()
		: data(0), capacity(0)
	{
	}

	// FUNCTION: ENGINE 0x108A5570
	WideStringBuffer::~WideStringBuffer()
	{
		if (capacity > 0)
		{
			delete[] data;
		}
	}

	// FUNCTION: ENGINE 0x108A5590
	void WideStringBuffer::Release()
	{
		if (capacity > 0)
		{
			delete[] data;
			capacity = 0;
		}
	}

	// FUNCTION: ENGINE 0x108A55B0
	void WideStringBuffer::Allocate(int newCapacity)
	{
		Release();
		capacity = newCapacity;
		data = new wchar_t[newCapacity];
		data[0] = 0;
	}

	// FUNCTION: ENGINE 0x108A55F0
	void WideStringBuffer::Borrow(const wchar_t* text)
	{
		if (capacity == 0)
		{
			data = (wchar_t*)text;
		}
	}

	// FUNCTION: ENGINE 0x108A5600
	void WideStringBuffer::CopyFrom(const WideStringBuffer& other)
	{
		if (capacity > 0)
		{
			core::Utf16Copy((unsigned short*)data, (const unsigned short*)other.data, capacity * 2);
		}
	}

	// FUNCTION: ENGINE 0x108A5620
	void WideStringBuffer::Copy(const wchar_t* text)
	{
		if (capacity > 0)
		{
			core::Utf16Copy((unsigned short*)data, (const unsigned short*)text, capacity * 2);
		}
	}

	// FUNCTION: ENGINE 0x108A5640
	void WideStringBuffer::Set(const char* text)
	{
		if (capacity > 0)
		{
			core::ConvertText(data, core::ENCODING_UTF16, text, core::ENCODING_ASCII, 0x21, capacity, 0, 0, 0);
		}
	}

	// FUNCTION: ENGINE 0x108A5670
	void WideStringBuffer::CopyTo(char* destination, int size)
	{
		core::ConvertText(destination, core::ENCODING_ASCII, data, core::ENCODING_UTF16, 0x2a, size, 0, 0, 0);
	}
}
