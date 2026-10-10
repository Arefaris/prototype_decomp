// The original formats with _vsnprintf (an import of the CRT); the define only silences VS 2005's deprecation warning
#define _CRT_SECURE_NO_WARNINGS
#include <stdarg.h>
#include <stdio.h>

#include "code/core/strings.h"

namespace core
{
	// A 32-bit word has a zero byte when this is non-zero
	#define HAS_ZERO_BYTE(w) ((((w) - 0x01010101) & ~(w)) & 0x80808080)

	// FUNCTION: ENGINE 0x1063AFA0
	int ToUpperChar(int c)
	{
		if ((unsigned char)(c - 'a') <= 25)
		{
			return c + 'A' - 'a';
		}
		return c;
	}

	// FUNCTION: ENGINE 0x1063AFC0
	int ToLowerChar(int c)
	{
		if ((unsigned char)(c - 'A') <= 25)
		{
			c += 'a' - 'A';
		}
		return c;
	}

	// FUNCTION: ENGINE 0x1063AFE0
	// EQUIVALENT: same loops in the same order; the original keeps the source in esi and the moving destination
	// in edx, ours the other way round (69 %)
	char* StrCpy(char* destination, const char* source)
	{
		if (source == 0)
		{
			source = "";
		}
		char* d = destination;
		if ((((unsigned int)d | (unsigned int)source) & 3) == 0)
		{
			unsigned int w = *(const unsigned int*)source;
			while (!HAS_ZERO_BYTE(w))
			{
				*(unsigned int*)d = w;
				source += 4;
				d += 4;
				w = *(const unsigned int*)source;
			}
		}
		char c;
		do
		{
			c = *source;
			*d = c;
			d++;
			source++;
		} while (c != 0);
		return destination;
	}

	// FUNCTION: ENGINE 0x1063B050
	// EQUIVALENT: a static helper (the compiler passes destination in edx, source in ecx, count in eax as the
	// original does); same loops in the same order, but the original keeps count in eax and copies the source
	// to esi, ours keeps the source in ecx and count in edi (23 %). Returns the count left over.
	static unsigned int StrNCpyTail(char* destination, const char* source, unsigned int count)
	{
		if (source == 0)
		{
			source = "";
		}
		if (count == 0)
		{
			return count;
		}
		if ((((unsigned int)destination | (unsigned int)source) & 3) == 0 && count >= 4)
		{
			do
			{
				unsigned int w = *(const unsigned int*)source;
				if (HAS_ZERO_BYTE(w))
				{
					break;
				}
				count -= 4;
				*(unsigned int*)destination = w;
				destination += 4;
				source += 4;
			} while (count >= 4);
		}
		if (count == 0)
		{
			destination[-1] = 0;
			return count;
		}
		while (count > 0)
		{
			count--;
			if (count == 0)
			{
				*destination = 0;
				return count;
			}
			char c = *source;
			*destination = c;
			destination++;
			source++;
			if (c == 0)
			{
				return count;
			}
		}
		return count;
	}

	// FUNCTION: ENGINE 0x1063B130
	char* StrCat(char* destination, const char* source)
	{
		if (source == 0)
		{
			source = "";
		}
		char* start = destination;
		if (((unsigned int)destination & 3) == 0)
		{
			unsigned int* w = (unsigned int*)destination;
			while (!HAS_ZERO_BYTE(*w))
			{
				w++;
			}
			destination = (char*)w;
		}
		while (*destination != 0)
		{
			destination++;
		}
		StrCpy(destination, source);
		return start;
	}

	// FUNCTION: ENGINE 0x1063B1A0
	// Static helper of the two StrNCat: appends and returns the characters now used, or size when the
	// destination was already that long
	static unsigned int StrNCatTail(char* destination, const char* source, unsigned int size)
	{
		if (source == 0)
		{
			source = "";
		}
		if (size == 0)
		{
			return 0;
		}
		char* start = destination;
		if (((unsigned int)destination & 3) == 0)
		{
			unsigned int* w = (unsigned int*)destination;
			while (!HAS_ZERO_BYTE(*w))
			{
				w++;
			}
			destination = (char*)w;
		}
		while (*destination != 0)
		{
			destination++;
		}
		unsigned int length = destination - start;
		if (size > length)
		{
			return StrNCpyTail(destination, source, size - length) + length;
		}
		return size;
	}

	// FUNCTION: ENGINE 0x1063B210
	char* StrNCat(char* destination, const char* source, unsigned int size)
	{
		StrNCatTail(destination, source, size);
		return destination;
	}

	// FUNCTION: ENGINE 0x1063B230
	char* StrNCat(char* destination, const char* source, unsigned int size, int* remaining)
	{
		unsigned int used = StrNCatTail(destination, source, size);
		if (remaining != 0)
		{
			*remaining = (size == used) ? 0 : size - used - 1;
		}
		return destination;
	}

	// FUNCTION: ENGINE 0x1063B270
	const char* StrChr(const char* string, char c)
	{
		const char* p = string;
		if (((unsigned int)p & 3) == 0)
		{
			unsigned int pattern = (unsigned char)c;
			pattern = (pattern << 8) | (unsigned char)c;
			pattern = (pattern << 8) | (unsigned char)c;
			pattern = (pattern << 8) | (unsigned char)c;
			const unsigned int* w = (const unsigned int*)p;
			unsigned int v = *w;
			while (!HAS_ZERO_BYTE(v) && !HAS_ZERO_BYTE(v ^ pattern))
			{
				w++;
				v = *w;
			}
			p = (const char*)w;
		}
		while (*p != 0)
		{
			if (*p == c)
			{
				return p;
			}
			p++;
		}
		if (*p != c)
		{
			p = 0;
		}
		return p;
	}

	// FUNCTION: ENGINE 0x1063B300
	const char* StrStr(const char* string, const char* find)
	{
		if (find == 0)
		{
			find = "";
		}
		if (*string == 0)
		{
			return *find == 0 ? string : 0;
		}
		do
		{
			const char* a = string;
			const char* b = find;
			for (;;)
			{
				if (*b == 0)
				{
					return string;
				}
				if (*b != *a)
				{
					break;
				}
				a++;
				b++;
			}
			string++;
		} while (*string != 0);
		return 0;
	}

	// FUNCTION: ENGINE 0x1063B350
	// Tokeniser: splits at any of the delimiters, writing terminators into the string; *context carries the
	// position between calls (null when the string is exhausted). With skipEmpty the leading delimiters are
	// skipped (strtok), without it every delimiter yields a token, empty ones included.
	char* StrTok(char* string, const char* delimiters, char** context, bool skipEmpty)
	{
		if (string == 0)
		{
			string = *context;
			if (string == 0)
			{
				return 0;
			}
		}
		int c;
		for (;;)
		{
			c = *string++;
			const char* d = delimiters;
			int x;
			do
			{
				x = *d++;
				if (x == 0)
				{
					goto tokenStart;
				}
			} while (c != x);
			if (skipEmpty)
			{
				continue;
			}
			*context = string;
			string[-1] = 0;
			return string - 1;
		}
	tokenStart:
		if (c == 0)
		{
			*context = 0;
			return 0;
		}
		char* token = string - 1;
		for (;;)
		{
			c = *string++;
			const char* d = delimiters;
			int x;
			do
			{
				x = *d++;
				if (x == c)
				{
					goto hit;
				}
			} while (x != 0);
		}
	hit:
		if (c == 0)
		{
			string = 0;
		}
		else
		{
			string[-1] = 0;
		}
		*context = string;
		return token;
	}

	// FUNCTION: ENGINE 0x1063B3F0
	char* StrTok(char* string, const char* delimiters, char** context)
	{
		return StrTok(string, delimiters, context, true);
	}

	// GLOBAL: ENGINE 0x11278FB8
	static char* sStrTokContext;

	// FUNCTION: ENGINE 0x1063B410
	char* StrTok(char* string, const char* delimiters)
	{
		return StrTok(string, delimiters, &sStrTokContext, true);
	}

	// FUNCTION: ENGINE 0x1063B430
	unsigned int StrLen(const char* string)
	{
		const char* start = string;
		if (((unsigned int)string & 3) == 0)
		{
			const unsigned int* w = (const unsigned int*)string;
			while (!HAS_ZERO_BYTE(*w))
			{
				w++;
			}
			string = (const char*)w;
		}
		while (*string != 0)
		{
			string++;
		}
		return string - start;
	}

	// FUNCTION: ENGINE 0x1063B480
	unsigned int StrNLen(const char* string, unsigned int count)
	{
		const char* start = string;
		if (((unsigned int)string & 3) == 0 && count >= 4)
		{
			const unsigned int* w = (const unsigned int*)string;
			do
			{
				if (HAS_ZERO_BYTE(*w))
				{
					break;
				}
				count -= 4;
				w++;
			} while (count >= 4);
			string = (const char*)w;
		}
		while (count > 0 && *string != 0)
		{
			count--;
			string++;
		}
		return string - start;
	}

	// FUNCTION: ENGINE 0x1063B4E0
	char* StrLower(char* string)
	{
		char* start = string;
		while (*string != 0)
		{
			if ((unsigned char)(*string - 'A') <= 25)
			{
				*string = (char)ToLowerChar(*string);
			}
			string++;
		}
		return start;
	}

	// FUNCTION: ENGINE 0x1063B520
	char* StrUpper(char* string)
	{
		char* start = string;
		while (*string != 0)
		{
			if ((unsigned char)(*string - 'a') <= 25)
			{
				*string = (char)ToUpperChar(*string);
			}
			string++;
		}
		return start;
	}

	// FUNCTION: ENGINE 0x1063B560
	int StrCmp(const char* a, const char* b)
	{
		if ((((unsigned int)a | (unsigned int)b) & 3) == 0)
		{
			const unsigned int* wa = (const unsigned int*)a;
			const unsigned int* wb = (const unsigned int*)b;
			while (*wa == *wb)
			{
				if (HAS_ZERO_BYTE(*wa))
				{
					return 0;
				}
				wa++;
				wb++;
			}
			a = (const char*)wa;
			b = (const char*)wb;
		}
		while (*a != 0 && *a == *b)
		{
			a++;
			b++;
		}
		return (unsigned char)*a - (unsigned char)*b;
	}

	// FUNCTION: ENGINE 0x1063B5D0
	int StrNCmp(const char* a, const char* b, unsigned int count)
	{
		if (count == 0)
		{
			return 0;
		}
		if ((((unsigned int)a | (unsigned int)b) & 3) == 0)
		{
			while (count >= 4 && *(const unsigned int*)a == *(const unsigned int*)b)
			{
				count -= 4;
				if (count == 0)
				{
					return 0;
				}
				if (HAS_ZERO_BYTE(*(const unsigned int*)a))
				{
					return 0;
				}
				a += 4;
				b += 4;
			}
		}
		while (count > 0)
		{
			count--;
			if (*a != *b)
			{
				break;
			}
			if (count == 0 || *a == 0)
			{
				return 0;
			}
			a++;
			b++;
		}
		return (unsigned char)*a - (unsigned char)*b;
	}

	// FUNCTION: ENGINE 0x1063B650
	int StrICmp(const char* a, const char* b)
	{
		while (*a != 0)
		{
			if (ToLowerChar(*a) != ToLowerChar(*b))
			{
				break;
			}
			a++;
			b++;
		}
		return ToLowerChar((unsigned char)*a) - ToLowerChar((unsigned char)*b);
	}

	// FUNCTION: ENGINE 0x1063B6B0
	// NONMATCHING: the original's loop is not inverted (one copy of the two ToLowerChar calls, a jmp back to the
	// loop head); every for / while / goto form tried makes VS 2005 duplicate the condition (34 %)
#ifdef NONMATCHING
	int StrNICmp(const char* a, const char* b, unsigned int count)
	{
		if (count == 0)
		{
			return 0;
		}
		for (;;)
		{
			char cb = *b;
			count--;
			char ca = *a;
			if (ToLowerChar(cb) != ToLowerChar(ca) || count == 0 || ca == 0 || cb == 0)
			{
				break;
			}
			a++;
			b++;
		}
		return ToLowerChar((unsigned char)*a) - ToLowerChar((unsigned char)*b);
	}
#endif

	// 0x1063B730 - 0x1063B7E0 (the string heap and StrDup) are a unit of their own: stringheap.cpp

	// FUNCTION: ENGINE 0x1063B7F0
	// Matches string against a pattern with '*' (any run) and '?' (any one character); returns 0 or 1 in al
	unsigned char MatchWildcard(const char* string, const char* pattern)
	{
		int c = *string;
		int p = *pattern;
		while (p != 0)
		{
			if (c == 0)
			{
				if (p == '*')
				{
					goto star;
				}
				return 0;
			}
			if (p == '*')
			{
				goto star;
			}
			if (p != '?' && c != p)
			{
				return 0;
			}
			p = *++pattern;
			c = *++string;
		}
		return c == 0;
	star:
		pattern++;
		if (*pattern != 0)
		{
			while (!MatchWildcard(string, pattern))
			{
				if (*string == 0)
				{
					return 0;
				}
				string++;
			}
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x1063B880
	// NONMATCHING: every block is there in the original's order and registers (59 %); two things remain: the
	// `read += 2` of the ".\" case is sunk by our compiler into the trailing-dot case (the original keeps its own
	// copy), and the inline strlen takes `path + 1` from the cursor register instead of `path` (also the issue
	// of the int-sized StrNCat below)
#ifdef NONMATCHING
	// Removes "." and ".." components from a path in place ('\\' and '/' are separators); returns the path
	char* NormalisePath(char* path)
	{
		if (path != 0)
		{
			char* write = path;
			const char* read = path;
			const char* q = write + 1;
			char c;
			do
			{
				c = *write++;
			} while (c != 0);
			unsigned int length = write - q;
			const char* end = path + length + 1;
			write = path;
			while (read < end)
			{
				if (*read == '.')
				{
					c = read[1];
					if (c == '.')
					{
						if (write < path + 2 || write[-2] == '.' || write[-3] == '.')
						{
							write[0] = '.';
							write[1] = '.';
							write += 2;
						}
						else
						{
							write -= 2;
							c = *write;
							if (c != '\\')
							{
								do
								{
									if (c == '/')
									{
										break;
									}
									if (write == path)
									{
										read++;
										break;
									}
									write--;
									c = *write;
								} while (c != '\\');
							}
						}
						read += 2;
					}
					else if (c == '\\' || c == '/')
					{
						read += 2;
					}
					else if (c == 0)
					{
						if (write > path)
						{
							write--;
						}
						*write = 0;
						read += 2;
					}
					else
					{
						goto copy;
					}
				}
				else
				{
				copy:
					*write = *read;
					read++;
					write++;
				}
			}
		}
		return path;
	}
#endif

	// FUNCTION: ENGINE 0x1063B960
	void VSNPrintf(char* buffer, int size, const char* format, va_list arguments)
	{
		_vsnprintf(buffer, size, format, arguments);
		if (size > 0)
		{
			buffer[size - 1] = 0;
		}
	}

	// FUNCTION: ENGINE 0x1063B990
	void SNPrintf(char* buffer, int size, const char* format, ...)
	{
		va_list arguments;
		va_start(arguments, format);
		VSNPrintf(buffer, size, format, arguments);
		va_end(arguments);
	}

	// FUNCTION: ENGINE 0x1063B9B0
	char* StrNCpyCount(char* destination, const char* source, int size, int* count)
	{
		*count = 0;
		while (source[*count] != 0 && *count < size - 1)
		{
			destination[*count] = source[*count];
			(*count)++;
		}
		destination[*count] = 0;
		return destination;
	}

	// FUNCTION: ENGINE 0x1063BA00
	// Continues a StrNCpyCount: source is indexed from where *count already stands
	char* StrNCpyAppend(char* destination, const char* source, int size, int* count)
	{
		source -= *count;
		while (source[*count] != 0 && *count < size - 1)
		{
			destination[*count] = source[*count];
			(*count)++;
		}
		destination[*count] = 0;
		return destination;
	}

	// FUNCTION: ENGINE 0x1063BA50
	char* StrNCpy(char* destination, const char* source, int size)
	{
		int i = 0;
		while (source[i] != 0 && i < size - 1)
		{
			destination[i] = source[i];
			i++;
		}
		destination[i] = 0;
		return destination;
	}

	// FUNCTION: ENGINE 0x1063BAA0
	// NONMATCHING: 95 %; the original computes `destination + 1` with lea from the cursor's register right after
	// copying it (before push esi), ours from the parameter's register after the push; every spelling of the
	// inline strlen tried (p - q, p - (d + 1), p - d - 1, unsigned char cursor, the parameter as cursor) gives
	// the same code
#ifdef NONMATCHING
	char* StrNCat(char* destination, const char* source, int size)
	{
		const char* p = destination;
		const char* q = p + 1;
		char c;
		do
		{
			c = *p++;
		} while (c != 0);
		int length = p - q;
		source -= length;
		while (source[length] != 0 && length < size - 1)
		{
			destination[length] = source[length];
			length++;
		}
		destination[length] = 0;
		return destination;
	}
#endif

	// FUNCTION: ENGINE 0x1063BB00
	char* FormatValue(char* buffer, int size, const char* format, int value)
	{
		SNPrintf(buffer, size, format, value);
		return buffer;
	}
}
