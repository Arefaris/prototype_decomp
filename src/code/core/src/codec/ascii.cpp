// The ASCII codec (0x10646E20 - 0x10646F67; see code/core/textcodec.h; file name guessed)
#include "code/core/textcodec.h"

namespace core
{
	// FUNCTION: ENGINE 0x10646E20
	bool AsciiDecodeChar(const char* source, unsigned int* bytes, unsigned int* code, int flags)
	{
		if (*source & 0x80)
		{
			return false;
		}
		if (bytes != 0)
		{
			*bytes = 1;
		}
		if (code != 0)
		{
			*code = (unsigned char)*source;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10646E50
	// EQUIVALENT: the original keeps the target pointer in ecx and loads the bytes pointer into eax after
	// the store (and edx / eax for U+3000), here edx / eax and eax / ecx (91.7 %)
	int AsciiEncodeChar(unsigned int code, char* target, unsigned int size, unsigned int replacement, unsigned int* bytes, int flags)
	{
		if (size < 1)
		{
			return -1;
		}
		if (code <= 0x7F)
		{
			*target = (char)code;
			*bytes = 1;
			return 0;
		}
		if (code >= 0xFF01 && code <= 0xFF5E)
		{
			*target = (char)(code - 0xFEE0);
			*bytes = 1;
			return 0;
		}
		if (code == 0x3000)
		{
			*target = ' ';
			*bytes = 1;
			return 0;
		}
		if (replacement == 0)
		{
			return -4;
		}
		int result = AsciiEncodeChar(replacement, target, size, 0, bytes, flags);
		if (result == -2)
		{
			result = -6;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10646EE0
	// EQUIVALENT: the original saves ebp, esi and edi before testing for an empty source, this build only after
	// it (same loop)
	int AsciiCopyString(char* target, const char* source, unsigned int size)
	{
		unsigned int count = 0;
		while (*source != 0)
		{
			if (count == size - 1)
			{
				break;
			}
			target[count] = *source;
			source++;
			count++;
		}
		target[count] = 0;
		return count;
	}

	// FUNCTION: ENGINE 0x10646F20
	int AsciiCountChars(const char* source, unsigned int* bytes)
	{
		unsigned int count = 0;
		while (source[count] != 0)
		{
			count++;
		}
		if (bytes != 0)
		{
			*bytes = count;
		}
		return count;
	}

	// FUNCTION: ENGINE 0x10646F50
	bool AsciiValidate(const char* source)
	{
		while (*source != 0)
		{
			if ((*source & 0x80) == 0)
			{
				return false;
			}
		}
		return true;
	}
}
