// The original formats with sprintf (an import of the CRT); the define only silences VS 2005's deprecation warning
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "code/core/hash.h"

namespace core
{
	// FUNCTION: ENGINE 0x1063A440
	void DefaultHash64Callback(unsigned __int64 hash, const char* string)
	{
	}

	// FUNCTION: ENGINE 0x1063A450
	void DefaultHash32Callback(unsigned int hash, const char* string)
	{
	}

	// GLOBAL: ENGINE 0x110BC598
	static Hash64Callback sHash64Callback = DefaultHash64Callback;
	// GLOBAL: ENGINE 0x110BC59C
	static Hash32Callback sHash32Callback = DefaultHash32Callback;

	// FUNCTION: ENGINE 0x1063A460
	unsigned __int64 Hash64(const char* string, unsigned __int64 hash)
	{
		if (string != 0)
		{
			const char* start = string;
			while (*string != 0)
			{
				hash = hash * 65599 ^ (__int64)*string;
				string++;
			}
			sHash64Callback(hash, start);
		}
		return hash;
	}

	// FUNCTION: ENGINE 0x1063A4D0
	unsigned __int64 MakeHash64(const char* string, unsigned __int64 hash)
	{
		return Hash64(string, hash);
	}

	// FUNCTION: ENGINE 0x1063A4F0
	unsigned __int64 Hash64NoCase(const char* string, unsigned __int64 hash)
	{
		if (string != 0)
		{
			const char* start = string;
			while (*string != 0)
			{
				// The multiplication (a CRT 64-bit multiply) comes before the case adjustment in the original
				hash *= 65599;
				hash ^= (__int64)(*string < 'a' ? *string + ('a' - 'A') : *string);
				string++;
			}
			sHash64Callback(hash, start);
		}
		return hash;
	}

	// FUNCTION: ENGINE 0x1063A560
	void SetHash64Callback(Hash64Callback callback)
	{
		sHash64Callback = callback;
		if (callback == 0)
		{
			sHash64Callback = DefaultHash64Callback;
		}
	}

	// FUNCTION: ENGINE 0x1063A580
	unsigned int Hash32(const char* string, unsigned int hash)
	{
		if (string != 0)
		{
			const char* start = string;
			while (*string != 0)
			{
				hash = hash * 31 + *string;
				string++;
			}
			sHash32Callback(hash, start);
		}
		return hash;
	}

	// FUNCTION: ENGINE 0x1063A5D0
	unsigned int Hash32NoCase(const char* string, unsigned int hash)
	{
		if (string != 0)
		{
			const char* start = string;
			while (*string != 0)
			{
				hash = hash * 31 + (*string < 'a' ? *string + ('a' - 'A') : *string);
				string++;
			}
			sHash32Callback(hash, start);
		}
		return hash;
	}

	// FUNCTION: ENGINE 0x1063A620
	void SetHash32Callback(Hash32Callback callback)
	{
		sHash32Callback = callback;
		if (callback == 0)
		{
			sHash32Callback = DefaultHash32Callback;
		}
	}

	// FUNCTION: ENGINE 0x1063A640
	int Hash64ToString(unsigned __int64 hash, char* buffer)
	{
		sprintf(buffer, "%8.8x", (unsigned int)(hash >> 32));
		sprintf(buffer + 8, "%8.8x", (unsigned int)hash);
		return 16;
	}

	// FUNCTION: ENGINE 0x1063A680
	int Hash32ToString(unsigned int hash, char* buffer)
	{
		sprintf(buffer, "%8x", hash);
		return 8;
	}
}
