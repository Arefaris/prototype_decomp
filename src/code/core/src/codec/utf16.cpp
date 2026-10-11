// The UTF-16 codec (0x10647510 - 0x10647792; see code/core/textcodec.h; file name guessed)
#include "code/core/textcodec.h"

namespace core
{
	// FUNCTION: ENGINE 0x10647510
	bool Utf16DecodeChar(const unsigned short* source, unsigned int* bytes, unsigned int* code, int flags)
	{
		unsigned int ch = source[0];
		unsigned int length = 1;
		if (ch >= 0xD800 && ch <= 0xDBFF)
		{
			unsigned int low = source[1];
			if (low < 0xDC00 || low > 0xDFFF)
			{
				return false;
			}
			ch = ((ch - 0xD800) << 10) + (low - 0xDC00) + 0x10000;
			length = 2;
		}
		else if (ch >= 0xDC00 && ch <= 0xDFFF)
		{
			return false;
		}
		if (bytes != 0)
		{
			*bytes = length * 2;
		}
		if (code != 0)
		{
			*code = ch;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10647580
	int Utf16EncodeChar(unsigned int code, unsigned short* target, unsigned int size, unsigned int replacement, unsigned int* bytes, int flags)
	{
		unsigned int count;
		if (code <= 0xFFFF)
		{
			count = 1;
		}
		else if (code < 0x10FFFF)
		{
			count = 2;
		}
		else
		{
			int result = Utf16EncodeChar(replacement, target, size, 0, bytes, flags);
			if (result == -2)
			{
				result = -6;
			}
			return result;
		}
		unsigned int length = count * 2;
		if (size < length)
		{
			return -1;
		}
		if (code <= 0xFFFF)
		{
			if (code >= 0xD800 && code <= 0xDFFF)
			{
				return -2;
			}
			target[0] = (unsigned short)code;
		}
		else if (code < 0x10FFFF)
		{
			code -= 0x10000;
			*target++ = (unsigned short)((code >> 10) + 0xD800);
			*target = (unsigned short)((code & 0x3FF) + 0xDC00);
		}
		else
		{
			if (replacement == 0)
			{
				return -4;
			}
			target[0] = (unsigned short)(replacement & 0xFF);
		}
		*bytes = length;
		return 0;
	}

	// FUNCTION: ENGINE 0x10647650
	// EQUIVALENT: the original tests the high surrogate range with two compares (cmp si, 0xD800 / 0xDBFF), this
	// build folds it into one (lea / cmp 0x3FF), as it does the low surrogate test after it; the copy loop is the
	// same
	// Returns the length in bytes, but in characters when the target is full
	int Utf16CopyString(unsigned short* target, const unsigned short* source, unsigned int size)
	{
		unsigned int count = 0;
		while (source[count] != 0)
		{
			unsigned short ch = source[count];
			unsigned int length = 1;
			if (ch >= 0xD800 && ch <= 0xDBFF)
			{
				unsigned short low = source[count + 1];
				if (low < 0xDC00 || low > 0xDFFF)
				{
					return -1;
				}
				length = 2;
			}
			else if (ch >= 0xDC00 && ch <= 0xDFFF)
			{
				return -1;
			}
			if ((count + length) * 2 + 2 > size)
			{
				target[count] = 0;
				return count;
			}
			for (unsigned int i = 0; i < length; i++)
			{
				target[count + i] = source[count + i];
			}
			count += length;
		}
		target[count] = 0;
		return count * 2;
	}

	// FUNCTION: ENGINE 0x10647710
	// EQUIVALENT: as Utf16CopyString, the surrogate ranges are tested with two compares each in the original
	// and folded here
	int Utf16CountChars(const unsigned short* source, unsigned int* bytes)
	{
		int count = 0;
		unsigned int total = 0;
		while (source[total] != 0)
		{
			unsigned short ch = source[total];
			unsigned int length = 1;
			if (ch >= 0xD800 && ch <= 0xDBFF)
			{
				unsigned short low = source[total + 1];
				if (low < 0xDC00 || low > 0xDFFF)
				{
					return -1;
				}
				length = 2;
			}
			else if (ch >= 0xDC00 && ch <= 0xDFFF)
			{
				return -1;
			}
			total += length;
			count++;
		}
		if (bytes != 0)
		{
			*bytes = total * 2;
		}
		return count;
	}
}
