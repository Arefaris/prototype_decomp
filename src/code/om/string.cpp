// The om library's string and the data behind it (0x105B3880 - 0x105B4480; names guessed).
// The characters of an owned string sit behind a header of the number of strings that share them and the room they have.
#include "code/om/string.h"
#include "code/om/stringdata.h"

#include "code/om/allocation.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace om
{
	// The engine's tag for the allocations of the string buffers: a static string "om::String" (constructed elsewhere)
	extern String gStringTag;

	// FUNCTION: ENGINE 0x105B3AF0
	void StringData::Create(StringData** result, const char* text, unsigned int count, unsigned int capacity)
	{
		char* block = (char*)Allocate(gStringTag.GetTextOutOfLine(), capacity + 9, 4) + 8;
		*result = (StringData*)block;
		StringHeader* header = (*result)->GetHeader();
		header->capacity = capacity;
		header->refCount = 1;
		memcpy((*result)->GetCharacters(), text, count);
		(*result)->GetCharacters()[count] = 0;
	}

	// FUNCTION: ENGINE 0x105B39B0
	void StringData::Free(StringData* data)
	{
		om::Release((char*)data - 8, data->GetHeader()->capacity + 9, 4);
	}

	// FUNCTION: ENGINE 0x105B3AC0
	void StringData::Unshare()
	{
		if (AtomicDecrement(&GetHeader()->refCount) == 0 && (char*)this != gEmptyStringData)
		{
			Free(this);
		}
	}

	// FUNCTION: ENGINE 0x105B3990
	void StringData::AddRef()
	{
		AtomicIncrement(&GetHeader()->refCount);
	}

	// FUNCTION: ENGINE 0x105B39A0
	unsigned int StringData::GetRefCount()
	{
		return GetHeader()->refCount;
	}

	// FUNCTION: ENGINE 0x105B3890
	StringHeader* StringData::GetHeader()
	{
		return (StringHeader*)((char*)this - 8);
	}

	// FUNCTION: ENGINE 0x105B3880
	char* StringData::GetCharacters()
	{
		return (char*)this;
	}

	// FUNCTION: ENGINE 0x105B39D0
	char* StringData::GetReadCharacters()
	{
		return GetCharacters();
	}

	// FUNCTION: ENGINE 0x105B39E0
	char* StringData::GetWriteCharacters()
	{
		return GetCharacters();
	}

	// FUNCTION: ENGINE 0x105B38C0
	char* String::GetData() const
	{
		return data;
	}

	// FUNCTION: ENGINE 0x105B38B0
	void String::SetLength(unsigned int newLength)
	{
		length = newLength;
	}

	// FUNCTION: ENGINE 0x105B39F0
	String::String()
	{
		data = gEmptyStringData;
		((StringData*)gEmptyStringData)->AddRef();
		length = 0;
		mode = 2;
	}

	// FUNCTION: ENGINE 0x105B3A20
	const char* String::GetTextOutOfLine() const
	{
		return data == gEmptyStringData ? "" : data;
	}

	// FUNCTION: ENGINE 0x105B3A30
	float String::ToFloat() const
	{
		return (float)atof(data == gEmptyStringData ? "" : data);
	}

	// FUNCTION: ENGINE 0x105B3A50
	unsigned int String::ToUnsignedInt() const
	{
		const char* text = data == gEmptyStringData ? "" : data;
		unsigned int value = 0;
		sscanf_s(text, "%u", &value, 4);
		return value;
	}

	// FUNCTION: ENGINE 0x105B3A90
	char String::GetCharacter(int index) const
	{
		return (data == gEmptyStringData ? "" : data)[index];
	}

	// FUNCTION: ENGINE 0x105B3B50
	bool String::operator==(const String& other) const
	{
		if (other.data == gEmptyStringData)
		{
			if (data == gEmptyStringData)
			{
				return true;
			}
			return false;
		}
		if (strcmp(GetTextOutOfLine(), other.GetTextOutOfLine()) == 0)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105B3BB0
	bool String::operator==(const char* other) const
	{
		if (other == 0)
		{
			if (data == gEmptyStringData)
			{
				return true;
			}
			return false;
		}
		if (strcmp(GetTextOutOfLine(), other) == 0)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105B3C10
	bool String::operator!=(const String& other) const
	{
		return !(*this == other);
	}

	// FUNCTION: ENGINE 0x105B3C30
	bool String::operator!=(const char* other) const
	{
		return !(*this == other);
	}

	// FUNCTION: ENGINE 0x105B3C60
	void String::Initialize(const char* text, unsigned int count, unsigned int capacity, int newMode)
	{
		mode = newMode;
		length = count;
		if (newMode == 0)
		{
			data = (char*)text;
			return;
		}
		if (newMode == 1)
		{
			data = (char*)text;
			return;
		}
		StringData* copy;
		StringData::Create(&copy, text, count, capacity);
		data = (char*)copy;
	}

	// FUNCTION: ENGINE 0x105B3CC0
	void String::Release()
	{
		if (mode == 2)
		{
			((StringData*)data)->Unshare();
		}
	}

	// FUNCTION: ENGINE 0x105B3CD0
	// EQUIVALENT: register choice only (96.6 %): the temporary that holds the address of the new data is edx / eax in the
	// engine, ecx / edx here; the same calls and stores in the same order
	char* String::GetWritableText()
	{
		StringData* copy;
		if (mode == 0)
		{
			StringData::Create(&copy, GetData(), length, length);
			data = (char*)copy;
			mode = 2;
			return ((StringData*)data)->GetWriteCharacters();
		}
		if (((StringData*)data)->GetRefCount() > 1)
		{
			StringData::Create(&copy, ((StringData*)data)->GetWriteCharacters(), length, length);
			Release();
			data = (char*)copy;
		}
		return ((StringData*)data)->GetWriteCharacters();
	}

	// FUNCTION: ENGINE 0x105B3D50
	String::String(const char* text, int newMode)
	{
		if (text == 0)
		{
			data = gEmptyStringData;
			((StringData*)gEmptyStringData)->AddRef();
			length = 0;
			mode = 2;
			return;
		}
		unsigned int count = (unsigned int)strlen(text);
		Initialize(text, count, count, newMode);
	}

	// FUNCTION: ENGINE 0x105B3DB0
	String::String(const char* text, unsigned int count, int newMode)
	{
		if (text == 0)
		{
			data = gEmptyStringData;
			((StringData*)gEmptyStringData)->AddRef();
			length = 0;
			mode = 2;
			return;
		}
		Initialize(text, count, count, newMode);
	}

	// FUNCTION: ENGINE 0x105B3E00
	inline String::String(const char* text, unsigned int count)
	{
		Initialize(text, count, count, 2);
	}

	// FUNCTION: ENGINE 0x105B3E20
	String::String(int unused, unsigned int capacity)
	{
		Initialize(0, 0, capacity, 2);
	}

	// FUNCTION: ENGINE 0x105B3E40
	String& String::Set(const char* text, unsigned int count, int newMode)
	{
		Release();
		Initialize(text, count, count, newMode);
		return *this;
	}

	// FUNCTION: ENGINE 0x105B3FF0
	String::~String()
	{
		Release();
	}

	// FUNCTION: ENGINE 0x105B4000
	void String::Copy(const String& other)
	{
		if (other.mode == 0)
		{
			data = other.data;
			mode = 0;
			length = other.length;
			return;
		}
		if (other.mode == 1)
		{
			Initialize(other.GetData(), other.length, other.length, 2);
			length = other.length;
			return;
		}
		mode = 2;
		data = other.data;
		length = other.length;
		((StringData*)data)->AddRef();
	}

	// FUNCTION: ENGINE 0x105B4070
	String::String(const String& other)
	{
		Copy(other);
	}

	// FUNCTION: ENGINE 0x105B4160
	String& String::operator=(const String& other)
	{
		if (&other != this)
		{
			Release();
			Copy(other);
		}
		return *this;
	}

	// FUNCTION: ENGINE 0x105B3750
	int FormatBuffer(char* buffer, unsigned int size, const char* format, ...)
	{
		va_list arguments;
		va_start(arguments, format);
		int count = _vsnprintf_s(buffer, size, -1, format, arguments);
		if (size > 0)
		{
			buffer[size - 1] = 0;
		}
		return count;
	}

	// FUNCTION: ENGINE 0x105B3E70
	String Format(int unused, const char* format, ...)
	{
		char buffer[4096];
		va_list arguments;
		va_start(arguments, format);
		int count = _vsnprintf_s(buffer, 4096, -1, format, arguments);
		buffer[4095] = 0;
		return String(buffer, (unsigned int)count);
	}

	// FUNCTION: ENGINE 0x105B4090
	String::String(float value)
	{
		String text = Format(0, "%f", (double)value);
		Copy(text);
	}

	// FUNCTION: ENGINE 0x105B40E0
	String::String(int value)
	{
		String text = Format(0, "%d", value);
		Copy(text);
	}

	// FUNCTION: ENGINE 0x105B4120
	String::String(unsigned int value)
	{
		String text = Format(0, "%u", value);
		Copy(text);
	}

	// FUNCTION: ENGINE 0x105B4180
	String& Sprintf(String& result, const char* format, ...)
	{
		char buffer[4096];
		va_list arguments;
		va_start(arguments, format);
		_vsnprintf_s(buffer, 4096, -1, format, arguments);
		buffer[4095] = 0;
		String text(buffer, 1);
		result = text;
		return result;
	}

	// FUNCTION: ENGINE 0x105B4230
	String String::ToUpper() const
	{
		String result(*this);
		char* text = result.GetWritableText();
		if (text != 0)
		{
			while (*text != 0)
			{
				if (*text >= 'a' && *text <= 'z')
				{
					*text -= 32;
				}
				text++;
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x105B4270
	String& String::operator+=(float value)
	{
		char buffer[64];
		int count = FormatBuffer(buffer, 64, "%f", (double)value);
		*this += String(buffer, count, 2);
		return *this;
	}

	// FUNCTION: ENGINE 0x105B42C0
	String& String::operator+=(unsigned int value)
	{
		char buffer[64];
		int count = FormatBuffer(buffer, 64, "%u", value);
		*this += String(buffer, count, 2);
		return *this;
	}

	// FUNCTION: ENGINE 0x105B43A0
	String String::operator+(float value) const
	{
		String result(*this);
		result += value;
		return result;
	}

	// FUNCTION: ENGINE 0x105B43D0
	String String::operator+(unsigned int value) const
	{
		String result(*this);
		result += value;
		return result;
	}

	// FUNCTION: ENGINE 0x105B43F0
	String String::operator+(const String& other) const
	{
		String result(*this);
		result += other;
		return result;
	}

	// FUNCTION: ENGINE 0x105B3ED0
	String& String::operator+=(const String& other)
	{
		unsigned short total = length + other.length;
		if (mode == 2 && ((StringData*)data)->GetRefCount() <= 1)
		{
			unsigned int room = ((StringData*)data)->GetHeader()->capacity;
			if (room >= total)
			{
				strcpy_s(((StringData*)data)->GetWriteCharacters() + length, room - length + 1,
					other.data == gEmptyStringData ? "" : other.data);
				length = total;
				return *this;
			}
		}
		StringData* combined;
		StringData::Create(&combined, data == gEmptyStringData ? "" : data, length, total);
		strcpy_s(combined->GetWriteCharacters(), combined->GetHeader()->capacity + 1,
			data == gEmptyStringData ? "" : data);
		strcpy_s(combined->GetWriteCharacters() + length, combined->GetHeader()->capacity - length + 1,
			other.data == gEmptyStringData ? "" : other.data);
		Release();
		data = (char*)combined;
		mode = 2;
		length += other.length;
		return *this;
	}

	// FUNCTION: ENGINE 0x105B4310
	String& String::Append(char character)
	{
		if (mode == 2 && ((StringData*)data)->GetRefCount() == 1 && ((StringData*)data)->GetHeader()->capacity > length)
		{
			((StringData*)data)->GetWriteCharacters()[length] = character;
			length++;
			((StringData*)data)->GetWriteCharacters()[length] = 0;
			return *this;
		}
		char text[2] = { character, 0 };
		*this += String(text, 1, 2);
		return *this;
	}

	// FUNCTION: ENGINE 0x105B4410
	String String::Substring(unsigned int start, unsigned int count) const
	{
		String result(0, count);
		for (unsigned int i = 0; i < count; i++)
		{
			result.Append(GetCharacter(start + i));
		}
		return result;
	}

	// FUNCTION: ENGINE 0x105B4460
	String String::Tail(unsigned int start) const
	{
		return Substring(start, length - start);
	}

	// FUNCTION: ENGINE 0x105B4480
	String String::Head(unsigned int count) const
	{
		return Substring(0, count);
	}

	// FUNCTION: ENGINE 0x105B44A0
	bool String::EndsWith(const String& suffix) const
	{
		if (length < suffix.length)
		{
			return false;
		}
		String tail = Tail(length - suffix.length);
		return tail == suffix;
	}

	// FUNCTION: ENGINE 0x105B4500
	// NONMATCHING: the engine tests the letter with two compares and branches (cmp 'A' / cmp 'Z'), ours turns the range test
	// into one unsigned compare (45 %)
#ifdef NONMATCHING
	String SpaceOutCapitals(const String& source)
	{
		char buffer[256];
		strcpy_s(buffer, 256, source.GetText());
		char* out = buffer;
		const char* in = source.GetText();
		bool previousCapital = *in >= 'A' && *in <= 'Z';
		char character = *in;
		while (character != 0)
		{
			bool capital;
			if (character < 'A' || character > 'Z')
			{
				capital = false;
			}
			else
			{
				capital = true;
			}
			if (!previousCapital && capital)
			{
				*out = ' ';
				out++;
			}
			character = *in;
			in++;
			*out = character;
			out++;
			previousCapital = capital;
			character = *in;
		}
		*out = 0;
		String text(buffer, 1);
		return String(text);
	}
#endif

	// FUNCTION: ENGINE 0x105B46B0
	void AssignTail(String& result, const String& source, unsigned int count)
	{
		char buffer[256];
		unsigned int total = source.length;
		unsigned int skip;
		if (total < count)
		{
			skip = 0;
			count = total + 1;
		}
		else
		{
			skip = total - count + 1;
		}
		memcpy(buffer, (source.data == gEmptyStringData ? "" : source.data) + skip, count);
		String text(buffer, 1);
		result = text;
	}
}
