// container::String and container::StringC<N> (RTTI names): a string over storage its subclass provides. String's
// four virtual slots are the destructor, the writable and the constant buffer and the capacity; StringC<N> keeps N
// characters inline. Only what the engine's users need is reconstructed (the class lives in the core library);
// member names are guesses.
#ifndef CONTAINER_STRING_H
#define CONTAINER_STRING_H

#include "code/core/strings.h"

namespace container
{
	class String
	{
	public:
		String()
		{
		}
		virtual ~String()
		{
		}
		virtual char* Data() = 0;
		virtual const char* ConstData() const = 0;
		virtual int Capacity() const = 0;

		// 0x1060ED50: printf into the string
		void Format(const char* format, ...);
		// 0x1060E960: empties the string
		void Clear();
		// 0x1060EDE0: appends other (as much as fits); the result's meaning is unknown
		int Append(const String& other);
		// 0x1060EEE0: how often c occurs
		int Count(char c);
		// 0x1060F080: calls function with every part of the string between separators (and context)
		void ForEachToken(char separator, void (*function)(const char* token, void* context), void* context);

		// The members below are in container/string.cpp (names guessed; a negative index counts from the end)
		// 0x1060EA60: the characters before the terminator
		unsigned int Length() const;
		// 0x1060F130 / 0x1060F140: no characters / no room for another
		bool IsEmpty() const;
		int IsFull() const;
		// 0x1060E990 / 0x1060EEB0: -1, 0 or 1 (an empty string sorts first)
		int Compare(const String& other, bool caseSensitive) const;
		int Compare(const char* other, bool caseSensitive) const;
		// 0x1060EA40 / 0x1060EA10
		bool Equals(const String& other, bool caseSensitive) const;
		bool Equals(const char* other, bool caseSensitive) const;
		// 0x1060F210 / 0x1060F490, 0x1060F3D0 / 0x1060F4C0
		bool StartsWith(const String& other, bool caseSensitive) const;
		bool StartsWith(const char* other, bool caseSensitive) const;
		bool EndsWith(const String& other, bool caseSensitive) const;
		bool EndsWith(const char* other, bool caseSensitive) const;
		// 0x1060EE70: the character at index, 0 when there is none
		char At(int index) const;
		// 0x1060EA80 / 0x1060F180: puts other in front, cutting what does not fit; answers how many characters
		unsigned int Prepend(const String& other);
		unsigned int Prepend(const char* other);
		// 0x1060F3A0
		int Append(const char* other);
		// 0x1060EF20 / 0x1060EFA0 / 0x1060F460: the index of the first match from start, -1 for none
		int Find(char c, int start, bool caseSensitive) const;
		int Find(const String& other, int start, bool caseSensitive) const;
		int Find(const char* other, int start, bool caseSensitive) const;
		// 0x1060EB20 / 0x1060EBA0 / 0x1060F1B0: the last match at or before start
		int FindLast(char c, int start, bool caseSensitive) const;
		int FindLast(const String& other, int start, bool caseSensitive) const;
		int FindLast(const char* other, int start, bool caseSensitive) const;
		// 0x108C04E0 (kept copy in the subtitle manager's unit): case insensitive
		int FindLast(const char* other, int start) const
		{
			return FindLast(other, start, false);
		}
		// 0x1060EC60 / 0x1060F1E0: copies length characters of source from start into this string (a negative
		// length goes backwards)
		unsigned int Mid(const String& source, int start, int length);
		unsigned int Mid(const char* source, int start, int length);
		// 0x1060EDA0 / 0x1060EDC0
		void ToUpper();
		void ToLower();
		// 0x1060F2A0: how many parts the separator cuts the string into
		unsigned int CountTokens(char separator) const;
		// 0x1060F300: cuts the string at every separator (writing terminators) and stores the start of each part
		unsigned int Split(char separator, char** parts, unsigned int maxParts);
	};

	// A string over a constant buffer (RTTI: container::StringLiteral; its vftable lives in another unit)
	class StringLiteral : public String
	{
	public:
		explicit StringLiteral(const char* newText)
		{
			text = newText;
		}
		virtual char* Data();
		virtual const char* ConstData() const;
		virtual int Capacity() const;

		const char* text;
	};

	template<int N> class StringC : public String
	{
	public:
		StringC()
		{
			buffer[0] = 0;
		}
		// Copies text, cut to N characters including the terminator
		explicit StringC(const char* text)
		{
			if (text != 0)
			{
				int length = (int)core::StrLen(text) + 1;
				if (length > N)
				{
					length = N;
				}
				core::StrNCpy(buffer, text, (unsigned int)length);
			}
			else
			{
				buffer[0] = 0;
			}
		}
		StringC(const StringC& other)
		{
			core::StrNCpy(buffer, other.buffer, core::StrNLen(other.buffer, N) + 1);
		}
		StringC& operator=(const StringC& other)
		{
			core::StrNCpy(buffer, other.buffer, core::StrNLen(other.buffer, N) + 1);
			return *this;
		}
		virtual char* Data()
		{
			return buffer;
		}
		virtual const char* ConstData() const
		{
			return buffer;
		}
		virtual int Capacity() const
		{
			return N;
		}

		char buffer[N];
	};

	// A heap copy of a string through Allocator (RTTI: StringDynamic<struct container::AllocatorCoreStatic<12,16> >;
	// copies of the members are in the stream package unit, 0x107FB1D0 - 0x107FB2D0; member names guessed)
	template<class Allocator> class StringDynamic : public String
	{
	public:
		// The allocator argument is an empty object passed by reference (the stream packages inline the constructor
		// where the argument is defaulted, and call it where it is passed)
		StringDynamic(const char* text, const Allocator& allocator = Allocator())
		{
			size = 0;
			data = 0;
			if (text != 0)
			{
				size = core::StrLen(text) + 1;
				data = (char*)Allocator::Alloc(size);
				core::StrNCpy(data, text, size);
			}
		}
		virtual ~StringDynamic()
		{
			if (size > 0)
			{
				Allocator::Free(data);
			}
		}
		virtual char* Data()
		{
			return data;
		}
		virtual const char* ConstData() const
		{
			return data;
		}
		virtual int Capacity() const
		{
			return size;
		}

		int unknown4;
		unsigned int size;
		char* data;
	};
}

#endif
