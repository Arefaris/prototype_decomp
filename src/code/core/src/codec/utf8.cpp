// The UTF-8 codec, after Unicode, Inc.'s ConvertUTF.c, and the width-form mapping the Shift-JIS codec uses
// (0x106470F0 - 0x10647508; see code/core/textcodec.h; file name guessed)
#include "code/core/textcodec.h"

namespace core
{
	// The unit's tables (not reproduced here): ConvertUTF.c's, and for DecomposeWidthForm the low bytes of the
	// full-width katakana for U+FF61 - U+FF9F (plus 0x3000) and the decompositions of U+FFE0 - U+FFE6 / U+FFE8 - U+FFEE
	extern const char trailingBytesForUTF8[256];
	extern const unsigned int offsetsFromUTF8[6];
	extern const unsigned char firstByteMark[7];
	extern unsigned char gHalfwidthKatakana[63];
	extern unsigned short gWidthSymbols1[7];
	extern unsigned short gWidthSymbols2[7];

	// FUNCTION: ENGINE 0x106470F0
	// ConvertUTF.c's check of one UTF-8 sequence (the compiler passes the length in ecx and the source in edx)
	static bool isLegalUTF8(const unsigned char* source, int length)
	{
		unsigned char a;
		const unsigned char* srcptr = source + length;
		switch (length)
		{
		default:
			return false;
		case 4:
			if ((a = (*--srcptr)) < 0x80 || a > 0xBF)
			{
				return false;
			}
		case 3:
			if ((a = (*--srcptr)) < 0x80 || a > 0xBF)
			{
				return false;
			}
		case 2:
			if ((a = (*--srcptr)) > 0xBF)
			{
				return false;
			}
			switch (*source)
			{
			case 0xE0:
				if (a < 0xA0)
				{
					return false;
				}
				break;
			case 0xF0:
				if (a < 0x90)
				{
					return false;
				}
				break;
			case 0xF4:
				if (a > 0x8F)
				{
					return false;
				}
				break;
			default:
				if (a < 0x80)
				{
					return false;
				}
			}
		case 1:
			if (*source >= 0x80 && *source < 0xC2)
			{
				return false;
			}
		}
		if (*source > 0xF4)
		{
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10647180
	bool DecomposeWidthForm(unsigned int code, unsigned int* result)
	{
		if (code >= 0xFF01 && code <= 0xFF5E)
		{
			*result = code - 0xFEE0;
			return true;
		}
		if (code >= 0xFF5F && code <= 0xFF60)
		{
			*result = code - 0xD5DA;
			return true;
		}
		if (code >= 0xFF61 && code <= 0xFF9F)
		{
			*result = gHalfwidthKatakana[code - 0xFF61] + 0x3000;
			return true;
		}
		if (code == 0xFFA0)
		{
			*result = 0x3164;
			return true;
		}
		if (code >= 0xFFA1 && code <= 0xFFBE)
		{
			*result = code - 0xCE70;
			return true;
		}
		if (code >= 0xFFC2 && code <= 0xFFC7)
		{
			*result = code - 0xCE73;
			return true;
		}
		if (code >= 0xFFCA && code <= 0xFFCF)
		{
			*result = code - 0xCE75;
			return true;
		}
		if (code >= 0xFFD2 && code <= 0xFFD7)
		{
			*result = code - 0xCE77;
			return true;
		}
		if (code >= 0xFFDA && code <= 0xFFDC)
		{
			*result = code - 0xCE79;
			return true;
		}
		if (code >= 0xFFE0 && code <= 0xFFE6)
		{
			*result = gWidthSymbols1[code - 0xFFE0];
			return true;
		}
		if (code >= 0xFFE8 && code <= 0xFFEE)
		{
			*result = gWidthSymbols2[code - 0xFFE8];
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106472B0
	bool Utf8DecodeChar(const char* source, unsigned int* bytes, unsigned int* code, int flags)
	{
		unsigned int ch = 0;
		int extraBytesToRead = trailingBytesForUTF8[(unsigned char)*source];
		if (!isLegalUTF8((const unsigned char*)source, extraBytesToRead + 1))
		{
			return false;
		}
		switch (extraBytesToRead)
		{
		case 3:
			ch += (unsigned char)*source++;
			ch <<= 6;
		case 2:
			ch += (unsigned char)*source++;
			ch <<= 6;
		case 1:
			ch += (unsigned char)*source++;
			ch <<= 6;
		case 0:
			ch += (unsigned char)*source++;
		}
		ch -= offsetsFromUTF8[extraBytesToRead];
		if (bytes != 0)
		{
			*bytes = extraBytesToRead + 1;
		}
		if (code != 0)
		{
			*code = ch;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10647340
	int Utf8EncodeChar(unsigned int code, char* target, unsigned int size, unsigned int replacement, unsigned int* bytes, int flags)
	{
		unsigned int bytesToWrite;
		if (code < 0x80)
		{
			bytesToWrite = 1;
		}
		else if (code < 0x800)
		{
			bytesToWrite = 2;
		}
		else if (code < 0x10000)
		{
			bytesToWrite = 3;
		}
		else if (code < 0x200000)
		{
			bytesToWrite = 4;
		}
		else
		{
			if (replacement == 0)
			{
				return -4;
			}
			int result = Utf8EncodeChar(replacement, target, size, 0, bytes, flags);
			if (result == -2)
			{
				result = -6;
			}
			return result;
		}
		if (size < bytesToWrite)
		{
			return -1;
		}
		unsigned char* p = (unsigned char*)target + bytesToWrite;
		switch (bytesToWrite)
		{
		case 4:
			*--p = (unsigned char)((code | 0x80) & 0xBF);
			code >>= 6;
		case 3:
			*--p = (unsigned char)((code | 0x80) & 0xBF);
			code >>= 6;
		case 2:
			*--p = (unsigned char)((code | 0x80) & 0xBF);
			code >>= 6;
		case 1:
			*--p = (unsigned char)(code | firstByteMark[bytesToWrite]);
		}
		*bytes = bytesToWrite;
		return 0;
	}

	// FUNCTION: ENGINE 0x10647430
	// EQUIVALENT: the original gives the count esi, the source pointer edi and the inner index edx, this
	// build edi, edx and esi (75.8 %)
	int Utf8CopyString(char* target, const char* source, unsigned int size)
	{
		unsigned int count = 0;
		while (source[count] != 0)
		{
			const char* p = source + count;
			unsigned int length = trailingBytesForUTF8[(unsigned char)*p] + 1;
			if (count + length + 1 > size)
			{
				break;
			}
			for (unsigned int i = 0; i < length; i++)
			{
				if (p == 0)
				{
					return -1;
				}
				target[count + i] = *p++;
			}
			count += length;
		}
		target[count] = 0;
		return count;
	}

	// FUNCTION: ENGINE 0x106474B0
	// EQUIVALENT: the original gives the source pointer esi and the inner index edx, this build the other way
	// round (92.1 %)
	int Utf8CountChars(const char* source, unsigned int* bytes)
	{
		int count = 0;
		unsigned int total = 0;
		char c = *source;
		while (c != 0)
		{
			const char* p = source + total;
			unsigned int length = trailingBytesForUTF8[(unsigned char)c] + 1;
			for (unsigned int i = 0; i < length; i++)
			{
				if (p == 0)
				{
					return -1;
				}
				p++;
			}
			total += length;
			c = source[total];
			count++;
		}
		if (bytes != 0)
		{
			*bytes = total;
		}
		return count;
	}
}
