// The Windows-1252 codec (0x10646F70 - 0x106470E3; see code/core/textcodec.h; file name guessed)
#include "code/core/textcodec.h"

namespace core
{
	// Unicode of Windows-1252 0x80 - 0x9F (data of the unit, not reproduced here)
	extern unsigned short gCp1252Table[32];

	// FUNCTION: ENGINE 0x10646F70
	bool Cp1252DecodeChar(const char* source, unsigned int* bytes, unsigned int* code, int flags)
	{
		unsigned char c = *source;
		if ((c & 0x80) == 0)
		{
			return AsciiDecodeChar(source, bytes, code, flags);
		}
		unsigned int value;
		if (c < 0x80)
		{
			value = c;
		}
		else if (c <= 0x9F)
		{
			value = gCp1252Table[c - 0x80];
		}
		else
		{
			value = c;
		}
		if (bytes != 0)
		{
			*bytes = 1;
		}
		if (code != 0)
		{
			*code = value;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10646FC0
	int Cp1252EncodeChar(unsigned int code, char* target, unsigned int size, unsigned int replacement, unsigned int* bytes, int flags)
	{
		if (size < 1)
		{
			return -1;
		}
		if (AsciiEncodeChar(code, target, size, 0, bytes, flags) == 0)
		{
			return 0;
		}
		if (code >= 0x80 && code <= 0xFF && code > 0x9F)
		{
			*target = (char)code;
			*bytes = 1;
			return 0;
		}
		for (unsigned int i = 0; i < 0x20; i++)
		{
			if (code == gCp1252Table[i])
			{
				*target = (char)(i + 0x80);
				*bytes = 1;
				return 0;
			}
		}
		if (replacement == 0)
		{
			return -4;
		}
		int result = Cp1252EncodeChar(replacement, target, size, 0, bytes, flags);
		if (result == -2)
		{
			result = -6;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10647080
	// EQUIVALENT: as AsciiCopyString, the registers are saved after the empty-source test here
	int Cp1252CopyString(char* target, const char* source, unsigned int size)
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

	// FUNCTION: ENGINE 0x106470C0
	int Cp1252CountChars(const char* source, unsigned int* bytes)
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
}
