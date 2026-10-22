// The base class of the om library's streams (0x105B86E0 - 0x105B8780 and the constructor 0x105C0E00).
#include "code/om/stream.h"

namespace om
{
	// FUNCTION: ENGINE 0x105C0E00
	Stream::Stream() :
		failed(false)
	{
	}

	// FUNCTION: ENGINE 0x105B86E0
	bool Stream::Write(const void* data, unsigned int size)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x105B86F0
	bool Stream::Read(void* data, unsigned int size)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x105B8700
	bool Stream::GetSize(unsigned int* size)
	{
		*size = 0;
		return false;
	}

	// FUNCTION: ENGINE 0x105B8710
	bool Stream::GetPosition(unsigned int* position)
	{
		*position = 0;
		return false;
	}

	// FUNCTION: ENGINE 0x105B8720
	bool Stream::Seek(unsigned int position)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x105B8770
	bool Stream::HasFailed()
	{
		return failed;
	}
}
