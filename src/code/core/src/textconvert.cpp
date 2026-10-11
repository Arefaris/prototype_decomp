#include <string.h>

#include "code/core/textcodec.h"
#include "code/core/textconvert.h"

namespace core
{
	// FUNCTION: ENGINE 0x1063E730
	int AsciiCopy(char* target, const char* source, unsigned int size)
	{
		return AsciiCopyString(target, source, size);
	}

	// FUNCTION: ENGINE 0x1063E740
	int Cp1252Copy(char* target, const char* source, unsigned int size)
	{
		return Cp1252CopyString(target, source, size);
	}

	// FUNCTION: ENGINE 0x1063E750
	int Utf8Copy(char* destination, const char* source, unsigned int size)
	{
		return Utf8CopyString(destination, source, size);
	}

	// FUNCTION: ENGINE 0x1063E760
	int Utf16Copy(unsigned short* target, const unsigned short* source, unsigned int size)
	{
		return Utf16CopyString(target, source, size);
	}

	// FUNCTION: ENGINE 0x1063E770
	int Utf32Copy(unsigned int* target, const unsigned int* source, unsigned int size)
	{
		return Utf32CopyString(target, source, size);
	}

	// FUNCTION: ENGINE 0x1063E780
	int ShiftJisCopy(char* target, const char* source, unsigned int size)
	{
		return ShiftJisCopyString(target, source, size);
	}

	// FUNCTION: ENGINE 0x1063E790
	int AsciiCount(const char* source, unsigned int* bytes)
	{
		if (source == 0)
		{
			return 0;
		}
		return AsciiCountChars(source, bytes);
	}

	// FUNCTION: ENGINE 0x1063E7B0
	int Cp1252Count(const char* source, unsigned int* bytes)
	{
		if (source == 0)
		{
			return 0;
		}
		return Cp1252CountChars(source, bytes);
	}

	// FUNCTION: ENGINE 0x1063E7D0
	int Utf8Count(const char* source, unsigned int* bytes)
	{
		if (source == 0)
		{
			return 0;
		}
		return Utf8CountChars(source, bytes);
	}

	// FUNCTION: ENGINE 0x1063E7F0
	int Utf16Count(const unsigned short* source, unsigned int* bytes)
	{
		if (source == 0)
		{
			return 0;
		}
		return Utf16CountChars(source, bytes);
	}

	// FUNCTION: ENGINE 0x1063E810
	int Utf32Count(const unsigned int* source, unsigned int* bytes)
	{
		if (source == 0)
		{
			return 0;
		}
		return Utf32CountChars(source, bytes);
	}

	// FUNCTION: ENGINE 0x1063E830
	int ShiftJisCount(const char* source, unsigned int* bytes)
	{
		if (source == 0)
		{
			return 0;
		}
		return ShiftJisCountChars(source, bytes);
	}

	// Instances by target encoding (ASCII, UTF-8, UTF-16, UTF-32, Shift-JIS, Windows-1252):
	// FUNCTION: ENGINE 0x1063E850
	// FUNCTION: ENGINE 0x1063EE30
	// FUNCTION: ENGINE 0x1063F410
	// FUNCTION: ENGINE 0x1063FA20
	// FUNCTION: ENGINE 0x10640030
	// FUNCTION: ENGINE 0x10640610
	// The copy for equal encodings without flags: validates each character and copies its bytes while they fit
	// (with the terminator); the length, -1 on an invalid character. The compiler passes the source in eax (and
	// for 16- and 32-bit units the target in ecx); the parameter order decides which register gets which
	template <typename S, bool (*Decode)(const S*, unsigned int*, unsigned int*, int)>
	static int CopyChars(char* target, const char* source, unsigned int size)
	{
		unsigned int total = 0;
		while (*(const S*)source != 0)
		{
			unsigned int code;
			unsigned int length = 0;
			if (!Decode((const S*)source, &length, &code, 0))
			{
				return -1;
			}
			if (length + total > size - sizeof(S))
			{
				break;
			}
			memcpy(target, source, length);
			source += length;
			target += length;
			total += length;
		}
		*(S*)target = 0;
		return total;
	}

	// Instances by target, then by source encoding (in the order of TextEncoding):
	// FUNCTION: ENGINE 0x1063E8D0
	// FUNCTION: ENGINE 0x1063E9B0
	// FUNCTION: ENGINE 0x1063EA90
	// FUNCTION: ENGINE 0x1063EB80
	// FUNCTION: ENGINE 0x1063EC70
	// FUNCTION: ENGINE 0x1063ED50
	// FUNCTION: ENGINE 0x1063EEB0
	// FUNCTION: ENGINE 0x1063EF90
	// FUNCTION: ENGINE 0x1063F070
	// FUNCTION: ENGINE 0x1063F160
	// FUNCTION: ENGINE 0x1063F250
	// FUNCTION: ENGINE 0x1063F330
	// FUNCTION: ENGINE 0x1063F490
	// FUNCTION: ENGINE 0x1063F580
	// FUNCTION: ENGINE 0x1063F670
	// FUNCTION: ENGINE 0x1063F750
	// FUNCTION: ENGINE 0x1063F840
	// FUNCTION: ENGINE 0x1063F930
	// FUNCTION: ENGINE 0x1063FAA0
	// FUNCTION: ENGINE 0x1063FB90
	// FUNCTION: ENGINE 0x1063FC80
	// FUNCTION: ENGINE 0x1063FD70
	// FUNCTION: ENGINE 0x1063FE50
	// FUNCTION: ENGINE 0x1063FF40
	// FUNCTION: ENGINE 0x106400B0
	// FUNCTION: ENGINE 0x10640190
	// FUNCTION: ENGINE 0x10640270
	// FUNCTION: ENGINE 0x10640360
	// FUNCTION: ENGINE 0x10640450
	// FUNCTION: ENGINE 0x10640530
	// FUNCTION: ENGINE 0x10640690
	// FUNCTION: ENGINE 0x10640770
	// FUNCTION: ENGINE 0x10640850
	// FUNCTION: ENGINE 0x10640940
	// FUNCTION: ENGINE 0x10640A30
	// FUNCTION: ENGINE 0x10640B10
	// One source / target pair: decodes and encodes character by character, keeping room for the terminator.
	// Sources and targets of different unit sizes may not be the same buffer. The compiler passes the source in eax
	// (UTF-16 <-> UTF-32 also the buffer in ecx). The target walks a copy of `buffer`: the parameter's stack slot
	// then holds `code`, as in the original
	template <typename S, typename T, bool (*Decode)(const S*, unsigned int*, unsigned int*, int), int (*Encode)(unsigned int, T*, unsigned int, unsigned int, unsigned int*, int)>
	static int ConvertChars(char* buffer, const char* source, unsigned int replacement, unsigned int size, int flags, unsigned int* bytes, unsigned int* chars)
	{
		if (sizeof(S) != sizeof(T) && source == buffer)
		{
			return -5;
		}
		char* target = buffer;
		unsigned int count = 0;
		unsigned int total = 0;
		while (*(const S*)source != 0)
		{
			unsigned int code = 0;
			unsigned int length = 0;
			if (!Decode((const S*)source, &length, &code, flags))
			{
				*bytes = total;
				*chars = count;
				return -2;
			}
			unsigned int written;
			int result = Encode(code, (T*)target, size - total - sizeof(T), replacement, &written, flags);
			if (result != 0)
			{
				if (result == -1)
				{
					*(T*)target = 0;
					*bytes = total;
					*chars = count;
					return -1;
				}
				*bytes = total;
				*chars = count;
				return result;
			}
			source += length;
			target += written;
			total += written;
			count++;
		}
		*(T*)target = 0;
		*bytes = total;
		*chars = count;
		return 0;
	}

	// Instances by target encoding:
	// FUNCTION: ENGINE 0x10640BF0
	// FUNCTION: ENGINE 0x10640CD0
	// FUNCTION: ENGINE 0x10640DB0
	// FUNCTION: ENGINE 0x10640E90
	// FUNCTION: ENGINE 0x10640F70
	// FUNCTION: ENGINE 0x10641050
	// The conversions to one target encoding, by source encoding
	template <typename T, bool (*Decode)(const T*, unsigned int*, unsigned int*, int), int (*Encode)(unsigned int, T*, unsigned int, unsigned int, unsigned int*, int)>
	static int ConvertTo(char* target, int targetEncoding, const char* source, int sourceEncoding, unsigned int replacement, unsigned int size, int flags, unsigned int* bytes, unsigned int* chars)
	{
		if (targetEncoding == sourceEncoding && flags == 0)
		{
			int result = CopyChars<T, Decode>(target, source, size);
			if (result < 0)
			{
				return -2;
			}
			return (result >= (int)size) - 1;
		}
		switch (sourceEncoding)
		{
		case ENCODING_ASCII:
			return ConvertChars<char, T, AsciiDecodeChar, Encode>(target, source, replacement, size, flags, bytes, chars);
		case ENCODING_UTF8:
			return ConvertChars<char, T, Utf8DecodeChar, Encode>(target, source, replacement, size, flags, bytes, chars);
		case ENCODING_UTF16:
			return ConvertChars<unsigned short, T, Utf16DecodeChar, Encode>(target, source, replacement, size, flags, bytes, chars);
		case ENCODING_UTF32:
			return ConvertChars<unsigned int, T, Utf32DecodeChar, Encode>(target, source, replacement, size, flags, bytes, chars);
		case ENCODING_SHIFT_JIS:
			return ConvertChars<char, T, ShiftJisDecodeChar, Encode>(target, source, replacement, size, flags, bytes, chars);
		case ENCODING_CP1252:
			return ConvertChars<char, T, Cp1252DecodeChar, Encode>(target, source, replacement, size, flags, bytes, chars);
		}
		return -2;
	}

	// FUNCTION: ENGINE 0x10641130
	int ConvertText(void* target, int targetEncoding, const void* source, int sourceEncoding, unsigned int replacement, unsigned int size, int flags, unsigned int* bytes, unsigned int* chars)
	{
		if (bytes != 0)
		{
			*bytes = 0;
		}
		if (chars != 0)
		{
			*chars = 0;
		}
		if (target == 0)
		{
			return -3;
		}
		if (source == 0)
		{
			return -2;
		}
		if (targetEncoding == sourceEncoding && target == source && flags == 0)
		{
			return 0;
		}
		unsigned int written = 0;
		unsigned int converted = 0;
		int result;
		switch (targetEncoding)
		{
		case ENCODING_ASCII:
			result = ConvertTo<char, AsciiDecodeChar, AsciiEncodeChar>((char*)target, ENCODING_ASCII, (const char*)source, sourceEncoding, replacement, size, flags, &written, &converted);
			break;
		case ENCODING_UTF8:
			result = ConvertTo<char, Utf8DecodeChar, Utf8EncodeChar>((char*)target, ENCODING_UTF8, (const char*)source, sourceEncoding, replacement, size, flags, &written, &converted);
			break;
		case ENCODING_UTF16:
			result = ConvertTo<unsigned short, Utf16DecodeChar, Utf16EncodeChar>((char*)target, ENCODING_UTF16, (const char*)source, sourceEncoding, replacement, size, flags, &written, &converted);
			break;
		case ENCODING_UTF32:
			result = ConvertTo<unsigned int, Utf32DecodeChar, Utf32EncodeChar>((char*)target, ENCODING_UTF32, (const char*)source, sourceEncoding, replacement, size, flags, &written, &converted);
			break;
		case ENCODING_SHIFT_JIS:
			result = ConvertTo<char, ShiftJisDecodeChar, ShiftJisEncodeChar>((char*)target, ENCODING_SHIFT_JIS, (const char*)source, sourceEncoding, replacement, size, flags, &written, &converted);
			break;
		case ENCODING_CP1252:
			result = ConvertTo<char, Cp1252DecodeChar, Cp1252EncodeChar>((char*)target, ENCODING_CP1252, (const char*)source, sourceEncoding, replacement, size, flags, &written, &converted);
			break;
		default:
			result = -3;
		}
		if (bytes != 0)
		{
			*bytes = written;
		}
		if (chars != 0)
		{
			*chars = converted;
		}
		return result;
	}
}
