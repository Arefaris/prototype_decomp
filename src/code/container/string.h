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
		// 0x1060EEE0: the number of times c occurs
		unsigned int Count(char c);
		// 0x1060F080: calls callback with each separator-delimited part (copied into a StringC<256>) and context
		void Split(char separator, void (*callback)(const char* part, void* context), void* context);
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

	// A string in a block of the allocator's heap, exactly as long as the text it was made from (RTTI:
	// container::StringDynamic<struct container::AllocatorCoreStatic<12,16> >)
	template<class Allocator> class StringDynamic : public String
	{
	public:
		StringDynamic(const char* text, const Allocator& newAllocator = Allocator())
		{
			capacity = 0;
			data = 0;
			if (text != 0)
			{
				capacity = core::StrLen(text) + 1;
				data = (char*)allocator.Alloc(capacity, 16);
				core::StrNCpy(data, text, capacity);
			}
		}
		virtual ~StringDynamic()
		{
			if (capacity > 0)
			{
				allocator.Free(data);
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
			return capacity;
		}

		Allocator allocator;
		unsigned int capacity;
		char* data;
	};
}

#endif
