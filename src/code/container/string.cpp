// container::String: the members that work over the virtual buffer accessors (names guessed; unit
// 0x1060E960 - 0x1060F4F0 of the core library). The overloads that take a plain character pointer wrap it in a
// StringLiteral and call the String ones.
#include "code/container/string.h"
#include <string.h>

namespace core
{
	// 0x1063B960 again, as the engine's callers see it: the count _vsnprintf answered
	int VSNPrintfResult(char* buffer, int size, const char* format, va_list arguments);
}

namespace container
{
	// FUNCTION: ENGINE 0x1060E960
	void String::Clear()
	{
		char* buffer = Data();
		if (buffer != 0)
		{
			if (Capacity() != 0)
			{
				*buffer = 0;
			}
		}
	}

	// FUNCTION: ENGINE 0x1060E990
	int String::Compare(const String& other, bool caseSensitive) const
	{
		const char* a = ConstData();
		const char* b = other.ConstData();
		bool aEmpty = a == 0 || *a == 0;
		bool bEmpty = b == 0 || *b == 0;
		if (aEmpty)
		{
			return bEmpty ? 0 : -1;
		}
		if (bEmpty)
		{
			return 1;
		}
		if (caseSensitive)
		{
			return core::StrCmp(a, b);
		}
		return core::StrICmp(a, b);
	}

	// FUNCTION: ENGINE 0x1060EA10
	bool String::Equals(const char* other, bool caseSensitive) const
	{
		StringLiteral literal(other);
		return Compare(literal, caseSensitive) == 0;
	}

	// FUNCTION: ENGINE 0x1060EA40
	bool String::Equals(const String& other, bool caseSensitive) const
	{
		return Compare(other, caseSensitive) == 0;
	}

	// FUNCTION: ENGINE 0x1060EA60
	unsigned int String::Length() const
	{
		const char* text = ConstData();
		if (text != 0 && *text != 0)
		{
			return core::StrLen(text);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1060EA80
	unsigned int String::Prepend(const String& other)
	{
		char* destination = Data();
		int capacity = Capacity();
		unsigned int length = Length();
		unsigned int count = other.Length();
		if (capacity != 0 && destination != 0 && count != 0)
		{
			capacity -= 1;
			unsigned int room = capacity - length;
			if (count >= room)
			{
				unsigned int overflow = count - room;
				if (overflow > length)
				{
					count += length - overflow;
					length = 0;
				}
				else
				{
					length -= overflow;
				}
			}
			const char* source = other.ConstData();
			memmove_s(destination + count, capacity - count, destination, length);
			memcpy_s(destination, capacity, source, count);
			destination[count + length] = 0;
			return count;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1060EB20
	int String::FindLast(char c, int start, bool caseSensitive) const
	{
		const char* text = ConstData();
		if (text != 0)
		{
			unsigned int length = Length();
			unsigned int index = start;
			if (start < 0)
			{
				index += length;
			}
			if (index < length)
			{
				char upper = (char)core::ToUpperChar(c);
				index += 1;
				if (index != 0)
				{
					do
					{
						index -= 1;
						if (caseSensitive)
						{
							if (text[index] == c)
							{
								return index;
							}
						}
						else if (core::ToUpperChar(text[index]) == upper)
						{
							return index;
						}
					}
					while (index != 0);
				}
			}
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x1060EBA0
	// NONMATCHING: two spilled locals and the engine's pointer-difference loop form are not reproduced, best 28.8%
#ifdef NONMATCHING
	int String::FindLast(const String& other, int start, bool caseSensitive) const
	{
		const char* text = ConstData();
		const char* needle = other.ConstData();
		if (text != 0 && needle != 0)
		{
			unsigned int length = Length();
			unsigned int count = other.Length();
			unsigned int index = start;
			if (start < 0)
			{
				index += length;
			}
			if (index < length && count > 0)
			{
				unsigned int last = length - count;
				if (last < index)
				{
					index = last;
				}
				unsigned int position = index + 1;
				if (position != 0)
				{
					do
					{
						position -= 1;
						unsigned int j = 0;
						while (needle[j] != 0)
						{
							if (caseSensitive)
							{
								if (text[position + j] != needle[j])
								{
									break;
								}
							}
							else if (core::ToUpperChar(text[position + j]) != core::ToUpperChar(needle[j]))
							{
								break;
							}
							j++;
						}
						if (needle[j] == 0)
						{
							return position;
						}
					}
					while (position != 0);
				}
			}
		}
		return -1;
	}
#endif

	// FUNCTION: ENGINE 0x1060EC60
	// EQUIVALENT: a conditional move for the count clamp and the backward copy's counter register, 82.2%
	unsigned int String::Mid(const String& source, int start, int length)
	{
		char* destination = Data();
		unsigned int capacity = Capacity();
		unsigned int sourceLength = source.Length();
		if (destination != 0 && capacity != 0 && sourceLength != 0)
		{
			unsigned int from = start;
			if (start < 0)
			{
				from = -start;
				if (from > sourceLength)
				{
					from = 0;
				}
				else
				{
					from = sourceLength - from;
				}
			}
			else if (from >= sourceLength)
			{
				from = sourceLength - 1;
			}
			bool backwards = false;
			unsigned int count = length;
			unsigned int available;
			if (length < 0)
			{
				backwards = true;
				count = -length;
				available = from + 1;
			}
			else
			{
				available = sourceLength - from;
			}
			if (available < count)
			{
				count = available;
			}
			if (count >= capacity)
			{
				count = capacity - 1;
			}
			const char* text = source.ConstData();
			unsigned int i;
			if (backwards)
			{
				text += from;
				for (i = 0; i < count; i++)
				{
					destination[i] = *text;
					text--;
				}
			}
			else
			{
				for (i = 0; i < count; i++)
				{
					destination[i] = text[from + i];
				}
			}
			destination[count] = 0;
			return count;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1060ED50
	// EQUIVALENT: the shared return block sits after the tail call, not before the body, 33.8%
	void String::Format(const char* format, ...)
	{
		char* buffer = Data();
		if (buffer == 0)
		{
			return;
		}
		va_list arguments;
		va_start(arguments, format);
		int count = core::VSNPrintfResult(buffer, Capacity(), format, arguments);
		va_end(arguments);
		if (count >= 0)
		{
			return;
		}
		Capacity();
	}

	// FUNCTION: ENGINE 0x1060EDA0
	void String::ToUpper()
	{
		char* buffer = Data();
		if (buffer != 0)
		{
			core::StrUpper(buffer);
		}
	}

	// FUNCTION: ENGINE 0x1060EDC0
	void String::ToLower()
	{
		char* buffer = Data();
		if (buffer != 0)
		{
			core::StrLower(buffer);
		}
	}

	// FUNCTION: ENGINE 0x1060EDE0
	// EQUIVALENT: the shared return-0 block sits at the end, not after the first test, 21.2%
	int String::Append(const String& other)
	{
		unsigned int length = Length();
		unsigned int count = other.Length();
		if (count == 0)
		{
			return 0;
		}
		char* destination = Data();
		int capacity = Capacity();
		if (capacity == 0 || destination == 0)
		{
			return 0;
		}
		if (count >= capacity - length)
		{
			count = capacity - length - 1;
		}
		const char* source = other.ConstData();
		for (unsigned int i = 0; i < count; i++)
		{
			destination[length + i] = source[i];
		}
		destination[length + count] = 0;
		return count;
	}

	// FUNCTION: ENGINE 0x1060EE70
	char String::At(int index) const
	{
		const char* text = ConstData();
		if (text != 0)
		{
			unsigned int length = Length();
			unsigned int position = index;
			if (index < 0)
			{
				position += length;
			}
			if (position < length)
			{
				return text[position];
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1060EEB0
	int String::Compare(const char* other, bool caseSensitive) const
	{
		StringLiteral literal(other);
		return Compare(literal, caseSensitive);
	}

	// FUNCTION: ENGINE 0x1060EEE0
	int String::Count(char c)
	{
		int count = 0;
		const char* text = ConstData();
		if (text != 0)
		{
			unsigned int length = Length();
			while (length != 0)
			{
				length -= 1;
				if (text[length] == c)
				{
					count += 1;
				}
			}
		}
		return count;
	}

	// FUNCTION: ENGINE 0x1060EF20
	// EQUIVALENT: text and length swap edi and ebp, 93.5%
	int String::Find(char c, int start, bool caseSensitive) const
	{
		const char* text = ConstData();
		if (text != 0)
		{
			unsigned int length = Length();
			unsigned int index = start;
			if (start < 0)
			{
				index += length;
			}
			if (index < length)
			{
				char upper = (char)core::ToUpperChar(c);
				do
				{
					if (caseSensitive)
					{
						if (text[index] == c)
						{
							return index;
						}
					}
					else if (core::ToUpperChar(text[index]) == upper)
					{
						return index;
					}
					index += 1;
				}
				while (index < length);
			}
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x1060EFA0
	// NONMATCHING: two spilled locals and the engine's pointer-difference loop form are not reproduced, best 10%
#ifdef NONMATCHING
	int String::Find(const String& other, int start, bool caseSensitive) const
	{
		const char* text = ConstData();
		const char* needle = other.ConstData();
		if (text != 0 && needle != 0)
		{
			unsigned int length = Length();
			unsigned int count = other.Length();
			unsigned int index = start;
			if (start < 0)
			{
				index += length;
			}
			if (index < length && length - index >= count && count > 0)
			{
				unsigned int end = length - count + 1;
				if (index < end)
				{
					do
					{
						unsigned int j = 0;
						while (needle[j] != 0)
						{
							if (caseSensitive)
							{
								if (text[index + j] != needle[j])
								{
									break;
								}
							}
							else if (core::ToUpperChar(text[index + j]) != core::ToUpperChar(needle[j]))
							{
								break;
							}
							j++;
						}
						if (needle[j] == 0)
						{
							return index;
						}
						index += 1;
					}
					while (index < end);
				}
			}
		}
		return -1;
	}
#endif

	// FUNCTION: ENGINE 0x1060F080
	void String::ForEachToken(char separator, void (*function)(const char* token, void* context), void* context)
	{
		StringC<256> token;
		int from = 0;
		int found = Find(separator, 0, true);
		while (found > -1)
		{
			token.Mid(*this, from, found - from);
			function(token.buffer, context);
			from = found + 1;
			found = Find(separator, from, true);
		}
		token.Mid(*this, from, 0x7FFFFFFF);
		function(token.buffer, context);
	}

	// FUNCTION: ENGINE 0x1060F130
	bool String::IsEmpty() const
	{
		return Length() == 0;
	}

	// FUNCTION: ENGINE 0x1060F140
	int String::IsFull() const
	{
		if (Capacity() != 0)
		{
			if (Length() < Capacity() - 1)
			{
				return 0;
			}
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x1060F180
	unsigned int String::Prepend(const char* other)
	{
		StringLiteral literal(other);
		return Prepend(literal);
	}

	// FUNCTION: ENGINE 0x1060F1B0
	int String::FindLast(const char* other, int start, bool caseSensitive) const
	{
		StringLiteral literal(other);
		return FindLast(literal, start, caseSensitive);
	}

	// FUNCTION: ENGINE 0x1060F1E0
	unsigned int String::Mid(const char* source, int start, int length)
	{
		StringLiteral literal(source);
		return Mid(literal, start, length);
	}

	// FUNCTION: ENGINE 0x1060F210
	bool String::StartsWith(const String& other, bool caseSensitive) const
	{
		bool thisEmpty = IsEmpty();
		bool otherEmpty = other.IsEmpty();
		if (thisEmpty)
		{
			if (otherEmpty)
			{
				return true;
			}
		}
		else if (!otherEmpty)
		{
			unsigned int count = other.Length();
			if (count <= Length())
			{
				const char* a = ConstData();
				const char* b = other.ConstData();
				if (caseSensitive)
				{
					return core::StrNCmp(a, b, count) == 0;
				}
				return core::StrNICmp(a, b, count) == 0;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1060F2A0
	unsigned int String::CountTokens(char separator) const
	{
		if (ConstData() == 0)
		{
			return 0;
		}
		if (Length() == 0)
		{
			return 0;
		}
		unsigned int count = 1;
		int found = Find(separator, 0, true);
		while (found > -1)
		{
			count += 1;
			found = Find(separator, found + 1, true);
		}
		return count;
	}

	// FUNCTION: ENGINE 0x1060F300
	unsigned int String::Split(char separator, char** parts, unsigned int maxParts)
	{
		char* text = Data();
		if (text != 0 && Length() != 0 && maxParts != 0)
		{
			unsigned int count = 1;
			parts[0] = text;
			int found = Find(separator, 0, true);
			while (found > -1 && count < maxParts)
			{
				parts[count++] = text + found + 1;
				found = Find(separator, found + 1, true);
			}
			for (unsigned int i = 1; i < count; i++)
			{
				parts[i][-1] = 0;
			}
			return count;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1060F3A0
	int String::Append(const char* other)
	{
		StringLiteral literal(other);
		return Append(literal);
	}

	// FUNCTION: ENGINE 0x1060F3D0
	// EQUIVALENT: register allocation of this/other and the order of the pointer sum, 72.1%
	bool String::EndsWith(const String& other, bool caseSensitive) const
	{
		if (other.IsEmpty())
		{
			return true;
		}
		unsigned int count = other.Length();
		unsigned int length = Length();
		if (count > length)
		{
			return false;
		}
		const char* a = ConstData() - count + length;
		const char* b = other.ConstData();
		if (caseSensitive)
		{
			return core::StrCmp(a, b) == 0;
		}
		return core::StrICmp(a, b) == 0;
	}

	// FUNCTION: ENGINE 0x1060F460
	int String::Find(const char* other, int start, bool caseSensitive) const
	{
		StringLiteral literal(other);
		return Find(literal, start, caseSensitive);
	}

	// FUNCTION: ENGINE 0x1060F490
	bool String::StartsWith(const char* other, bool caseSensitive) const
	{
		StringLiteral literal(other);
		return StartsWith(literal, caseSensitive);
	}

	// FUNCTION: ENGINE 0x1060F4C0
	bool String::EndsWith(const char* other, bool caseSensitive) const
	{
		StringLiteral literal(other);
		return EndsWith(literal, caseSensitive);
	}
}
