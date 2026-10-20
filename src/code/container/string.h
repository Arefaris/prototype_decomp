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
		// 0x1060F130: the string has no characters
		bool IsEmpty() const;
		// 0x1060EDE0: appends other (as much as fits); the result's meaning is unknown
		int Append(const String& other);
		// 0x1060EEE0: how often c occurs
		int Count(char c);
		// 0x1060EF20: the place of the first c from start on, a negative number when there is none (the third
		// argument is 1 in its users)
		int Find(char c, int start, int unknown);
		// 0x1060EC60: becomes the part of other that starts at start and has length characters
		void Assign(const String& other, int start, int length);
		// 0x1060EA40: the strings have the same characters (the second argument says to ignore the case)
		bool Equals(const String& other, bool ignoreCase);
		// 0x1060F3A0: appends text (as much as fits)
		void Append(const char* text);
		// 0x1060F080: calls function with every part of the string between separators (and context)
		void ForEachToken(char separator, void (*function)(const char* token, void* context), void* context);
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
