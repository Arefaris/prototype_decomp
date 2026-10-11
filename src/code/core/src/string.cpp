// The original formats with sprintf (an import of the CRT); the define only silences VS 2005's deprecation warning
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>

#include "code/core/istring.h"
#include "code/core/strings.h"

// Array allocation from a heap, inlined here (`new(heap) char[size]`: the heap is read before the size is computed);
// the engine defines the same operator out of line (code/engine/memory/memory.cpp, 0x107DEFB0)
inline void* operator new[](unsigned int size, int heap)
{
	return core::HeapAlloc(heap, size);
}

namespace core
{
	const char* CoreName();

	// FUNCTION: ENGINE 0x10647F80
	String::String()
		: RefCount(1)
	{
		buffer = 0;
		capacity = 1;
		null = 1;
		CoreName();
	}

	// FUNCTION: ENGINE 0x10648010
	bool String::IsNull()
	{
		return null;
	}

	// FUNCTION: ENGINE 0x10648020
	void String::SetNull(bool value)
	{
		if (value)
		{
			null = 1;
		}
		else
		{
			null = 0;
		}
	}

	// FUNCTION: ENGINE 0x10648040
	bool String::Equals(const char* string)
	{
		if (string != 0)
		{
			if (!NoValue())
			{
				return strcmp(buffer, string) == 0;
			}
		}
		else if (NoValue())
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106480B0
	bool String::Equals(IString* string)
	{
		if (string != 0)
		{
			return Equals(string->Get());
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106480E0
	unsigned int String::GetCapacity()
	{
		return capacity;
	}

	// FUNCTION: ENGINE 0x106480F0
	void String::SetCapacity(unsigned int size)
	{
		capacity = size;
	}

	// FUNCTION: ENGINE 0x10648110
	void String::Reserve(unsigned int size)
	{
		if (size > GetCapacity())
		{
			if (buffer != 0)
			{
				char* grown = new(heap) char[size];
				strcpy(grown, buffer);
				HeapFree(heap, buffer);
				buffer = grown;
			}
			capacity = size;
		}
	}

	// FUNCTION: ENGINE 0x10648180
	void String::Assign(const char* string)
	{
		if (string != 0)
		{
			unsigned int size = strlen(string) + 1;
			if (size > GetCapacity())
			{
				capacity = size;
				if (buffer != 0)
				{
					HeapFree(heap, buffer);
				}
				buffer = new(heap) char[GetCapacity()];
			}
			else if (buffer == 0)
			{
				buffer = new(heap) char[GetCapacity()];
			}
			strcpy(buffer, string);
			null = 0;
		}
		else
		{
			null = 1;
		}
	}

	// FUNCTION: ENGINE 0x10648230
	void String::Assign(IString* string)
	{
		if (string != 0 && string != this)
		{
			Assign(string->Get());
		}
	}

	// FUNCTION: ENGINE 0x10648260
	void String::Copy(char* destination, unsigned int size)
	{
		if (destination != 0 && size > 0)
		{
			if (!NoValue())
			{
				strncpy(destination, buffer, size);
			}
			else
			{
				*destination = 0;
			}
		}
	}

	// FUNCTION: ENGINE 0x106482A0
	const char* String::Get()
	{
		if (NoValue())
		{
			return 0;
		}
		return buffer;
	}

	// FUNCTION: ENGINE 0x106482C0
	unsigned int String::Length()
	{
		if (!NoValue())
		{
			return strlen(buffer);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x106482E0
	void String::Append(IString* string)
	{
		if (string != 0)
		{
			Append(string->Get());
		}
	}

	// FUNCTION: ENGINE 0x10648310
	void String::Append(const char* string)
	{
		if (string == 0)
		{
			return;
		}
		if (NoValue())
		{
			Assign(string);
			return;
		}
		unsigned int size = strlen(string) + strlen(buffer) + 1;
		if (size > GetCapacity())
		{
			capacity = size;
			char* grown = new(heap) char[GetCapacity()];
			strcpy(grown, buffer);
			strcat(grown, string);
			HeapFree(heap, buffer);
			null = 0;
			buffer = grown;
		}
		else
		{
			strcat(buffer, string);
			null = 0;
		}
	}

	// FUNCTION: ENGINE 0x10648440
	void String::Append(unsigned int value)
	{
		Append((int)value);
	}

	// FUNCTION: ENGINE 0x10648450
	void String::Append(int value)
	{
		char text[256];
		sprintf(text, "%d", value);
		Append(text);
	}

	// FUNCTION: ENGINE 0x10648490
	void String::Append(char value)
	{
		char text[2];
		text[0] = value;
		text[1] = 0;
		Append(text);
	}

	// FUNCTION: ENGINE 0x106484B0
	void String::Append(unsigned long value)
	{
		Append((unsigned int)value);
	}

	// FUNCTION: ENGINE 0x106484C0
	void String::Append(float value)
	{
		char text[64];
		sprintf(text, "%f", value);
		Append(text);
	}

	// FUNCTION: ENGINE 0x10648500
	void String::Append(bool value)
	{
		Append(value ? "true" : "false");
	}

	// FUNCTION: ENGINE 0x10648520
	void String::ToLower()
	{
		if (!NoValue())
		{
			_strlwr(buffer);
		}
	}

	// FUNCTION: ENGINE 0x10648540
	void String::ToUpper()
	{
		if (!NoValue())
		{
			_strupr(buffer);
		}
	}

	// FUNCTION: ENGINE 0x10648560
	unsigned char String::Match(const char* pattern)
	{
		return MatchWildcard(buffer, pattern);
	}

	// FUNCTION: ENGINE 0x10648580
	unsigned char String::Match(IString* pattern)
	{
		if (pattern != 0)
		{
			return Match(pattern->Get());
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106485B0
	void String::Slot24()
	{
	}

	// FUNCTION: ENGINE 0x10648690
	void String::AddRef()
	{
		RefCount::AddRef();
	}

	// FUNCTION: ENGINE 0x106486A0
	void String::Release()
	{
		RefCount::Release();
	}

	// FUNCTION: ENGINE 0x106486D0
	void CreateString(IString** string, int heap)
	{
		*string = new(heap) String();
	}
}
