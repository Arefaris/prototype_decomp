// Small helpers of the broad phase's tables (0x10681F10 - 0x10682290); see alignedruns.h.
#include "code/core/heap.h"
#include "code/ravenphysics/alignedruns.h"

namespace ravenphysics
{
	template <int Function>
	void* AllocateAligned128(unsigned int size)
	{
		return core::HeapAllocAligned(core::GetCurrentHeap(), (size + 0x7F) & ~0x7Fu, 0x80);
	}

	// FUNCTION: ENGINE 0x10681F10
	template void* AllocateAligned128<0x10681F10>(unsigned int);
	// FUNCTION: ENGINE 0x10682200
	template void* AllocateAligned128<0x10682200>(unsigned int);

	// FUNCTION: ENGINE 0x10681F30
	void* Aligned128Source::Allocate(unsigned int size)
	{
		return core::HeapAllocAligned(core::GetCurrentHeap(), (size + 0x7F) & ~0x7Fu, 0x80);
	}

	// FUNCTION: ENGINE 0x10681F60
	void SetBit(unsigned char* bits, unsigned int index)
	{
		unsigned short byteIndex = (unsigned short)index >> 3;
		bits[byteIndex] |= (unsigned char)(1 << (index & 7));
	}

	// FUNCTION: ENGINE 0x10681F90
	void ClearBit(unsigned char* bits, unsigned int index)
	{
		unsigned short byteIndex = (unsigned short)index >> 3;
		bits[byteIndex] &= (unsigned char)~(1 << (index & 7));
	}

	// FUNCTION: ENGINE 0x10681FC0
	// EQUIVALENT: the same bit set or cleared in the same byte; ours keeps the bit number in another register across the branch, 22.4 %
	void AssignBit(unsigned char* bits, unsigned short index, bool value)
	{
		unsigned short byteIndex = index >> 3;
		unsigned int bit = index & 7;
		if (value)
		{
			bits[byteIndex] |= (unsigned char)(1 << bit);
		}
		else
		{
			bits[byteIndex] &= (unsigned char)~(1 << bit);
		}
	}

	// FUNCTION: ENGINE 0x10682220
	bool TestBit(const BitSetHolder* holder, unsigned short index)
	{
		return (holder->bits[index >> 3] & (1 << (index & 7))) != 0;
	}

	template <class T>
	bool ElementRun<T>::Reserve(unsigned int count)
	{
		if (count > 0)
		{
			begin = (T*)core::HeapAllocAligned(core::GetCurrentHeap(), (count * sizeof(T) + 0x7F) & ~0x7Fu, 0x80);
			if (begin)
			{
				end = begin + count;
				return true;
			}
		}
		begin = 0;
		end = 0;
		return false;
	}

	// FUNCTION: ENGINE 0x106820E0
	template bool ElementRun<Element4>::Reserve(unsigned int);
	// FUNCTION: ENGINE 0x10682140
	template bool ElementRun<Element24>::Reserve(unsigned int);
	// FUNCTION: ENGINE 0x106821A0
	template bool ElementRun<Element12>::Reserve(unsigned int);

	// FUNCTION: ENGINE 0x10682250
	void SwapWords(int* first, int* second)
	{
		int held = *first;
		*first = *second;
		*second = held;
	}

	// FUNCTION: ENGINE 0x10682270
	void SwapTriples(Element12* first, Element12* second)
	{
		Element12 held = *first;
		*first = *second;
		*second = held;
	}
}
