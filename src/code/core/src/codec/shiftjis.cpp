// The Shift-JIS codec (0x106478A0 - 0x10647BE9; see code/core/textcodec.h; file name guessed)
#include "code/core/textcodec.h"

namespace core
{
	// Shift-JIS <-> Unicode pairs (a single '?' entry; the lookups below always answer it)
	struct ShiftJisPair
	{
		unsigned short shiftJis;
		unsigned short unicode;
	};

	// The unit's tables (not reproduced here): the pairs, and the full-width Shift-JIS forms of the ASCII punctuation
	// 0x20 - 0x2F, 0x3A - 0x40, 0x5B - 0x60 and 0x7B - 0x7E
	extern ShiftJisPair gShiftJisTable[1];
	extern unsigned short gShiftJisPunctuation1[16];
	extern unsigned short gShiftJisPunctuation2[7];
	extern unsigned short gShiftJisPunctuation3[6];
	extern unsigned short gShiftJisPunctuation4[4];

	// FUNCTION: ENGINE 0x106478A0
	// The table lookups are stubs: every character maps to the table's only entry
	static int FindShiftJisByUnicode(unsigned int code)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x106478B0
	static int FindShiftJisByCode(unsigned int code)
	{
		return 0;
	}

#define IS_SHIFT_JIS_LEAD(c) (((c) >= 0x81 && (c) <= 0x9F) || ((c) >= 0xE0 && (c) <= 0xFC))
#define IS_SHIFT_JIS_TRAIL(c) ((c) >= 0x40 && (c) <= 0xFC && (c) != 0x7F)

	// 0x106478C0 is a static IsShiftJisTrail(c) with the character in al that nothing calls (the codec tests trail
	// bytes with the macro); the compiler drops an unreferenced static function, so it is not reconstructed

	// FUNCTION: ENGINE 0x106478E0
	// The full-width double-byte form of a printable ASCII character, 0 for anything else
	static unsigned short AsciiToShiftJis(char c)
	{
		if (c >= 0x20 && c <= 0x2F)
		{
			return gShiftJisPunctuation1[c - 0x20];
		}
		if (c >= '0' && c <= '9')
		{
			return (unsigned short)(c - '0') + 0x824F;
		}
		if (c >= 0x3A && c <= 0x40)
		{
			return gShiftJisPunctuation2[c - 0x3A];
		}
		if (c >= 'A' && c <= 'Z')
		{
			return (unsigned short)(c - 'A') + 0x8260;
		}
		if (c >= 0x5B && c <= 0x60)
		{
			return gShiftJisPunctuation3[c - 0x5B];
		}
		if (c >= 'a' && c <= 'z')
		{
			return (unsigned short)(c - 'a') + 0x8281;
		}
		if (c >= 0x7B && c <= 0x7E)
		{
			return gShiftJisPunctuation4[c - 0x7B];
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10647990
	bool ShiftJisDecodeChar(const char* source, unsigned int* bytes, unsigned int* code, int flags)
	{
		unsigned char c = source[0];
		unsigned int value;
		unsigned int length;
		if (c <= 0x7F)
		{
			value = c;
			length = 1;
		}
		else if (c >= 0xA1 && c <= 0xDF)
		{
			value = c + 0xFEC0;
			length = 1;
		}
		else
		{
			if (!IS_SHIFT_JIS_LEAD(c))
			{
				return false;
			}
			unsigned char trail = source[1];
			if (!IS_SHIFT_JIS_TRAIL(trail))
			{
				return false;
			}
			int index = FindShiftJisByCode((c << 8) | trail);
			if (index < 0)
			{
				return false;
			}
			value = gShiftJisTable[index].unicode;
			length = 2;
		}
		if (bytes != 0)
		{
			*bytes = length;
		}
		if (code != 0)
		{
			*code = value;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10647A10
	// EQUIVALENT: same operations; the original keeps the size check and the high-byte split after the ASCII
	// branch and lets the table branch jump back to them, this build puts them after the table branch
	int ShiftJisEncodeChar(unsigned int code, char* target, unsigned int size, unsigned int replacement, unsigned int* bytes, int flags)
	{
		unsigned char low = 0;
		unsigned char high;
		unsigned int length;
		if (code <= 0x7F)
		{
			if (flags == 1)
			{
				length = 2;
				if (code == 0)
				{
					high = 0;
				}
				else
				{
					unsigned short full = AsciiToShiftJis((char)code);
					if (full == 0)
					{
						goto replace;
					}
					high = (unsigned char)(full >> 8);
					low = (unsigned char)full;
				}
			}
			else
			{
				length = 1;
				high = (unsigned char)code;
			}
		}
		else if (code >= 0xFF61 && code <= 0xFF9F)
		{
			if (flags == 1)
			{
				unsigned int full = 0;
				if (!DecomposeWidthForm(code, &full))
				{
					goto replace;
				}
				return ShiftJisEncodeChar(full, target, size, replacement, bytes, flags);
			}
			length = 1;
			high = (unsigned char)(code - 0xFEC0);
		}
		else
		{
			length = 2;
			if (code & 0xFFFF0000)
			{
				goto replace;
			}
			int index = FindShiftJisByUnicode(code);
			if (index < 0)
			{
				goto replace;
			}
			unsigned short value = gShiftJisTable[index].shiftJis;
			high = (unsigned char)(value >> 8);
			low = (unsigned char)value;
		}
		if (size < length)
		{
			return -1;
		}
		target[0] = high;
		if (length == 2)
		{
			target[1] = low;
		}
		*bytes = length;
		return 0;

	replace:
		if (replacement == 0)
		{
			return -4;
		}
		int result = ShiftJisEncodeChar(replacement, target, size, 0, bytes, flags);
		if (result == -2)
		{
			return -6;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10647B30
	int ShiftJisCopyString(char* target, const char* source, unsigned int size)
	{
		unsigned int count = 0;
		while (source[count] != 0)
		{
			unsigned char c = source[count];
			target[count] = c;
			if (IS_SHIFT_JIS_LEAD(c))
			{
				unsigned char trail = source[count + 1];
				if (!IS_SHIFT_JIS_TRAIL(trail))
				{
					target[count] = 0;
					return -1;
				}
				target[count + 1] = trail;
				count++;
			}
			count++;
		}
		target[count] = 0;
		return count;
	}

	// FUNCTION: ENGINE 0x10647B90
	int ShiftJisCountChars(const char* source, unsigned int* bytes)
	{
		int count = 0;
		unsigned int total = 0;
		while (source[total] != 0)
		{
			unsigned char c = source[total];
			if (IS_SHIFT_JIS_LEAD(c))
			{
				unsigned char trail = source[total + 1];
				if (!IS_SHIFT_JIS_TRAIL(trail))
				{
					return -1;
				}
				total++;
			}
			total++;
			count++;
		}
		if (bytes != 0)
		{
			*bytes = total;
		}
		return count;
	}
}
