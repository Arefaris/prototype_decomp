// The UTF-32 codec (0x106477A0 - 0x1064789A; see code/core/textcodec.h; file name guessed)
#include "code/core/textcodec.h"

namespace core
{
	// FUNCTION: ENGINE 0x106477A0
	bool Utf32DecodeChar(const unsigned int* source, unsigned int* bytes, unsigned int* code, int flags)
	{
		unsigned int ch = *source;
		if (ch >= 0xD800 && ch <= 0xDFFF)
		{
			return false;
		}
		if (bytes != 0)
		{
			*bytes = 4;
		}
		if (code != 0)
		{
			*code = ch;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x106477E0
	int Utf32EncodeChar(unsigned int code, unsigned int* target, unsigned int size, unsigned int replacement, unsigned int* bytes, int flags)
	{
		if (size < 4)
		{
			return -1;
		}
		if (code >= 0xD800 && code <= 0xDFFF)
		{
			return -2;
		}
		*target = code;
		*bytes = 4;
		return 0;
	}

	// FUNCTION: ENGINE 0x10647820
	// Returns the length in bytes, but in characters when the target is full
	int Utf32CopyString(unsigned int* target, const unsigned int* source, unsigned int size)
	{
		unsigned int count = 0;
		while (source[count] != 0)
		{
			if (count * 4 + 4 > size)
			{
				target[count] = 0;
				return count;
			}
			target[count] = source[count];
			count++;
		}
		target[count] = 0;
		return count * 4;
	}

	// FUNCTION: ENGINE 0x10647870
	int Utf32CountChars(const unsigned int* source, unsigned int* bytes)
	{
		unsigned int count = 0;
		while (source[count] != 0)
		{
			count++;
		}
		if (bytes != 0)
		{
			*bytes = count * 4;
		}
		return count;
	}
}
