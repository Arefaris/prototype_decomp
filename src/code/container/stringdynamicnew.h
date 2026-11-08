// container::StringDynamic<AllocatorNew> (RTTI: StringDynamic<struct container::AllocatorNew>, vftable 0x10E09650): a heap
// copy of a string in a block of operator new[] (the primary template in string.h is the one of the stream packages).
// The members are defined in the class body: the engine keeps its out-of-line copies in the save game manager's unit
// (0x10480270 - 0x10480560), and the users expand them.
#ifndef CONTAINER_STRINGDYNAMICNEW_H
#define CONTAINER_STRINGDYNAMICNEW_H

#include "code/container/arraydynamic.h"
#include "code/container/string.h"
#include <new>

namespace container
{
	template<> class StringDynamic<AllocatorNew> : public String
	{
	public:
		// 0x10480270: an empty string (the allocator is an empty object)
		explicit StringDynamic(const AllocatorNew& allocator)
		{
			size = 0;
			data = 0;
		}
		// 0x10480290 (the deleting form is 0x10480560)
		virtual ~StringDynamic()
		{
			if (size > 0)
			{
				delete[] data;
			}
		}
		// The slots 0x104802C0 / 0x104802D0 / 0x104802E0
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
		// 0x104953D0 (the engine keeps an out-of-line copy): makes room for that many characters
		void Allocate(unsigned int newSize)
		{
			if (newSize > 0)
			{
				data = new char[newSize];
				if (data != 0)
				{
					size = newSize;
				}
			}
		}

		int unknown4;
		unsigned int size;  // +8
		char* data;  // +0xC
	};
}

#endif
