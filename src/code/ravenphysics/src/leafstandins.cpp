// The tiny leaf functions of 0x106A0000 - 0x106C0000; see leafstandins.h.
#include <new>
#include "code/core/interlocked.h"
#include "code/core/memutils.h"
#include "code/ravenphysics/common/stackallocator.h"
#include "code/ravenphysics/leafstandins.h"

namespace ravenphysics
{
	template <int Function, int Offset>
	char* LeafAddress<Function, Offset>::Get()
	{
		return &member;
	}

	template <int Function, int Offset>
	int LeafWord<Function, Offset>::Get() const
	{
		return member;
	}

	template <int Function, int Offset>
	unsigned short LeafHalf<Function, Offset>::Get() const
	{
		return member;
	}

	template <int Function, int Offset>
	int LeafSignedHalf<Function, Offset>::Get() const
	{
		return member;
	}

	template <int Function, int Offset>
	int LeafUnsignedHalf<Function, Offset>::Get() const
	{
		return member;
	}

	template <int Function, int Offset>
	unsigned char LeafByte<Function, Offset>::Get() const
	{
		return member;
	}

	template <int Function, int Offset>
	float LeafFloat<Function, Offset>::Get() const
	{
		return member;
	}

	template <int Function>
	LeafSelf<Function>* LeafSelf<Function>::Get()
	{
		return this;
	}

	template <int Function>
	void LeafNothing()
	{
	}

	template <int Function>
	int LeafZero()
	{
		return 0;
	}

	template <int Function>
	bool LeafFalse()
	{
		return false;
	}

	template <int Function>
	int LeafSecondArgument(int first, int second)
	{
		return second;
	}

	template <int Function, int Size>
	LeafElement<Size>* LeafArray<Function, Size>::At(int index)
	{
		return items + index;
	}

	template <int Function, int Offset>
	void LeafSetWord<Function, Offset>::Set(int newValue)
	{
		member = newValue;
	}

	template <int Function, int First, int Second>
	LeafInitTwo<Function, First, Second>::LeafInitTwo()
	{
		first = First;
		second = Second;
	}

	template <int Function>
	LeafZeroThree<Function>::LeafZeroThree()
	{
		first = 0;
		second = 0;
		third = 0;
	}

	template <int Function>
	LeafTwoWords<Function>::LeafTwoWords(int newFirst, int newSecond)
	{
		first = newFirst;
		second = newSecond;
	}

	template <int Function>
	void LeafSetTwoWords<Function>::Set(int newFirst, int newSecond)
	{
		first = newFirst;
		second = newSecond;
	}

	template <int Function>
	long LeafIncrement<Function>::Get()
	{
		return _InterlockedIncrement(&member);
	}

	template <int Function>
	long LeafDecrement<Function>::Get()
	{
		return _InterlockedDecrement(&member);
	}

	template <int Function, int Offset, int Bit>
	bool LeafBit<Function, Offset, Bit>::Get() const
	{
		return member.flag;
	}

	template <int Function, int Offset, int Bit>
	char LeafSignedBit<Function, Offset, Bit>::Get() const
	{
		return member.flag;
	}

	template <int Function, int Offset>
	unsigned short LeafHalfIndexed<Function, Offset>::At(unsigned short index) const
	{
		return items[index];
	}

	template <int Function, int Size>
	void LeafCreate<Function, Size>::Create(int newCount, StackAllocator* stack)
	{
		items = stack->Alloc(newCount * Size, 16);
		count = newCount;
	}

	template <int Function, int Size>
	void LeafCreateCapacity<Function, Size>::Create(int newCapacity, StackAllocator* stack)
	{
		items = stack->Alloc(newCapacity * Size, 16);
		count = 0;
		capacity = newCapacity;
	}

	template <int Function, int Size>
	LeafElement<Size>* LeafNext<Function, Size>::Next()
	{
		count++;
		return items + count - 1;
	}

	template <int Function, int Size>
	void LeafPush<Function, Size>::Push(const LeafElement<Size>* value)
	{
		count++;
		new (items + count - 1) LeafElement<Size>(*value);
	}

	template <int Function>
	LeafInitThree<Function>::LeafInitThree(int newFirst, int newThird)
	{
		first = newFirst;
		second = 0;
		third = newThird;
	}

	template <int Function>
	LeafInitThreeLast<Function>::LeafInitThreeLast(int newThird)
	{
		first = 0;
		second = 0;
		third = newThird;
	}

	template <int Function>
	LeafInitFour<Function>::LeafInitFour(int newFourth)
	{
		first = 0;
		second = 0;
		third = 0;
		fourth = newFourth;
	}

	template <int Function, int Size>
	void LeafCreateStacked<Function, Size>::Create(int newCapacity)
	{
		if (newCapacity != 0)
		{
			items = stack->Alloc((newCapacity * Size + 15) & ~15, 16);
		}
		else
		{
			items = 0;
		}
		capacity = newCapacity;
	}

	template <int Function, int Size>
	LeafElement<Size>* LeafEnd<Function, Size>::End()
	{
		return items + count;
	}

	template <int Function, int Size>
	LeafElement<Size>* LeafLast<Function, Size>::Last()
	{
		return items + count - 1;
	}

	template <int Function, int First, int Second>
	bool LeafWordsEqual<Function, First, Second>::Get() const
	{
		return words[First / 4] == words[Second / 4];
	}

	template <int Function, int Size, int Begin, int End>
	int LeafCount<Function, Size, Begin, End>::Get() const
	{
		return pointers[End / 4] - pointers[Begin / 4];
	}

	template <int Function, int Size>
	int LeafHelperSize<Function, Size>::Get(LeafHelperSize* array)
	{
		return array->end - array->begin;
	}

	template <int Function, int Size>
	LeafElement<Size>* LeafHelperGet<Function, Size>::Get(LeafHelperGet* array, int index)
	{
		return array->begin + index;
	}

	template <int Function, int Offset>
	void LeafClearWord<Function, Offset>::Clear()
	{
		member = 0;
	}

	template <int Function, int Offset>
	int LeafWordPlusOne<Function, Offset>::Get() const
	{
		return member + 1;
	}

	template <int Function>
	unsigned short LeafBucket<Function>::Get(unsigned int key) const
	{
		return ((key >> 3 ^ key) >> 4) % count;
	}

	template <int Function>
	bool LeafEqualsWord<Function>::Get(const int* other) const
	{
		return member == *other;
	}

	template <int Function>
	bool LeafEqualsPair<Function>::Get(const LeafEqualsPair* other) const
	{
		return first == other->first && second == other->second;
	}

	template <int Function, int Offset, int Size>
	LeafElement<Size>* LeafInlineArray<Function, Offset, Size>::At(int index)
	{
		return items + index;
	}

	template <int Function, int Offset>
	int LeafInlineWord<Function, Offset>::Get(int index) const
	{
		return items[index];
	}

	template <int Function>
	LeafInitShortWordWord<Function>::LeafInitShortWordWord(unsigned short newFirst, int newSecond, int newThird)
	{
		first = newFirst;
		second = newSecond;
		third = newThird;
	}

	template <int Function>
	void LeafAddShort<Function>::Add(unsigned short value)
	{
		total += value;
		count++;
	}

	template <int Function>
	LeafZeroTwoIgnoring<Function>::LeafZeroTwoIgnoring(int unused)
	{
		first = 0;
		second = 0;
	}

	template <int Function>
	LeafInitWordShort<Function>::LeafInitWordShort(int newFirst)
	{
		first = newFirst;
		second = 0;
	}

	template <int Function>
	LeafInitWordShortShort<Function>::LeafInitWordShortShort(int newFirst, unsigned short newThird)
	{
		first = newFirst;
		second = 1;
		third = newThird;
	}

	template <int Function>
	int LeafFirstArgument(int first)
	{
		return first;
	}

	template <int Function>
	int LeafDereference(const int* pointer)
	{
		return *pointer;
	}

	template <int Function>
	void LeafSwap(int* first, int* second)
	{
		int saved = *first;
		*first = *second;
		*second = saved;
	}

	template <int Function>
	void LeafCopyWord(int* destination, const int* source)
	{
		*destination = *source;
	}

	template <int Function>
	LeafPairOfPointers<Function>::LeafPairOfPointers(const int* newFirst, const int* newSecond)
	{
		first = *newFirst;
		second = *newSecond;
	}

	template <int Function>
	LeafPairPointerWord<Function>::LeafPairPointerWord(const int* newFirst, int newSecond)
	{
		first = *newFirst;
		second = newSecond;
	}

	template <int Function, int Offset>
	int LeafLessThan<Function, Offset>::Get(const LeafLessThan* other) const
	{
		return member < other->member;
	}

	template <int Function>
	bool LeafIsEmpty<Function>::Get() const
	{
		return count == 0;
	}

	template <int Function, int Offset>
	LeafSelfPointer<Function, Offset>* LeafSelfPointer<Function, Offset>::Init()
	{
		self = this;
		return this;
	}

	template <int Function, int Size, int Count>
	int LeafInlineCount<Function, Size, Count>::Get() const
	{
		return end - items;
	}

	template <int Function, int Size, int Count>
	bool LeafInlineIsEmpty<Function, Size, Count>::Get() const
	{
		return end == items;
	}

	template <int Function, int Size>
	void LeafCopyIn<Function, Size>::Copy(const void* source)
	{
		core::MemCopyUnchecked(items, source, count * Size);
	}

	template <int Function, int Size>
	void LeafAssign<Function, Size>::Assign(const LeafAssign* other)
	{
		count = other->count;
		core::MemCopyUnchecked(items, other->items, count * Size);
	}

	template <int Function, int Size>
	void LeafCreateAligned<Function, Size>::Create(int newCount, int align)
	{
		if (newCount != 0)
		{
			items = stack->Alloc((newCount * Size + align - 1) & ~(align - 1), align);
		}
		else
		{
			items = 0;
		}
		count = newCount;
	}


	// FUNCTION: ENGINE 0x106A0000
	template struct LeafAddress<0x106A0000, 104>;

	// FUNCTION: ENGINE 0x106A0010
	template struct LeafAddress<0x106A0010, 96>;

	// FUNCTION: ENGINE 0x106A0020
	template struct LeafAddress<0x106A0020, 112>;

	// FUNCTION: ENGINE 0x106A0B10
	template struct LeafAddress<0x106A0B10, 72>;

	// FUNCTION: ENGINE 0x106A0B20
	template struct LeafAddress<0x106A0B20, 84>;

	// FUNCTION: ENGINE 0x106A12B0
	template struct LeafFloat<0x106A12B0, 4>;

	// FUNCTION: ENGINE 0x106A12C0
	template struct LeafFloat<0x106A12C0, 8>;

	// FUNCTION: ENGINE 0x106A12D0
	template struct LeafAddress<0x106A12D0, 48>;

	// FUNCTION: ENGINE 0x106A12E0
	template struct LeafAddress<0x106A12E0, 56>;

	// FUNCTION: ENGINE 0x106A14A0
	template struct LeafAddress<0x106A14A0, 64>;

	// FUNCTION: ENGINE 0x106A14B0
	template struct LeafInlineArray<0x106A14B0, 64, 12>;

	// FUNCTION: ENGINE 0x106A14C0
	template struct LeafAddress<0x106A14C0, 88>;

	// FUNCTION: ENGINE 0x106A14D0
	template struct LeafFloat<0x106A14D0, 100>;

	// FUNCTION: ENGINE 0x106A14E0
	template struct LeafFloat<0x106A14E0, 128>;

	// FUNCTION: ENGINE 0x106A14F0
	template struct LeafFloat<0x106A14F0, 132>;

	// FUNCTION: ENGINE 0x106A1500
	template struct LeafFloat<0x106A1500, 136>;

	// FUNCTION: ENGINE 0x106A1510
	template struct LeafFloat<0x106A1510, 140>;

	// FUNCTION: ENGINE 0x106A38E0
	template struct LeafSelf<0x106A38E0>;

	// FUNCTION: ENGINE 0x106A38F0
	template struct LeafWord<0x106A38F0, 4>;

	// FUNCTION: ENGINE 0x106A3900
	template struct LeafAddress<0x106A3900, 8>;

	// FUNCTION: ENGINE 0x106A3910
	template struct LeafWord<0x106A3910, 12>;

	// FUNCTION: ENGINE 0x106A3920
	template struct LeafHalf<0x106A3920, 40>;

	// FUNCTION: ENGINE 0x106A3930
	template struct LeafAddress<0x106A3930, 20>;

	// FUNCTION: ENGINE 0x106A3940
	template struct LeafWord<0x106A3940, 24>;

	// FUNCTION: ENGINE 0x106A3950
	template struct LeafAddress<0x106A3950, 28>;

	// FUNCTION: ENGINE 0x106A3960
	template struct LeafWord<0x106A3960, 32>;

	// FUNCTION: ENGINE 0x106A3970
	template struct LeafHalf<0x106A3970, 42>;

	// FUNCTION: ENGINE 0x106A3980
	template struct LeafWord<0x106A3980, 16>;

	// FUNCTION: ENGINE 0x106A3990
	template struct LeafWord<0x106A3990, 36>;

	// FUNCTION: ENGINE 0x106A39A0
	template struct LeafWord<0x106A39A0, 76>;

	// FUNCTION: ENGINE 0x106A39B0
	template struct LeafWord<0x106A39B0, 80>;

	// FUNCTION: ENGINE 0x106A3E80
	template struct LeafNext<0x106A3E80, 112>;

	// FUNCTION: ENGINE 0x106A3EA0
	template LeafSized<0x106A3EA0, 4>* StackAllocator::AllocArray<LeafSized<0x106A3EA0, 4> >(int, int);

	// FUNCTION: ENGINE 0x106A3EC0
	template LeafSized<0x106A3EC0, 4>* StackAllocator::AllocArray<LeafSized<0x106A3EC0, 4> >(int, int);

	// FUNCTION: ENGINE 0x106A3F00
	template LeafSized<0x106A3F00, 4>* StackAllocator::AllocArray<LeafSized<0x106A3F00, 4> >(int, int);

	// FUNCTION: ENGINE 0x106A4160
	template struct LeafWordsEqual<0x106A4160, 4, 8>;

	// FUNCTION: ENGINE 0x106A5DF0
	template struct LeafCount<0x106A5DF0, 12, 0, 4>;

	// FUNCTION: ENGINE 0x106A5E10
	template struct LeafWordsEqual<0x106A5E10, 0, 4>;

	// FUNCTION: ENGINE 0x106A5E20
	template struct LeafArray<0x106A5E20, 12>;

	// FUNCTION: ENGINE 0x106A5E30
	template struct LeafSelf<0x106A5E30>;

	// FUNCTION: ENGINE 0x106A5E40
	template void LeafNothing<0x106A5E40>();

	// FUNCTION: ENGINE 0x106A5E50
	template int LeafSecondArgument<0x106A5E50>(int, int);

	// FUNCTION: ENGINE 0x106A5E60
	template int LeafSecondArgument<0x106A5E60>(int, int);

	// FUNCTION: ENGINE 0x106A6010
	template struct LeafZeroThree<0x106A6010>;

	// FUNCTION: ENGINE 0x106A60E0
	template struct LeafHelperSize<0x106A60E0, 12>;

	// FUNCTION: ENGINE 0x106A6100
	template struct LeafHelperGet<0x106A6100, 12>;

	// FUNCTION: ENGINE 0x106A6120
	template struct LeafHelperGet<0x106A6120, 12>;

	// FUNCTION: ENGINE 0x106A6140
	template struct LeafCount<0x106A6140, 12, 0, 8>;

	// FUNCTION: ENGINE 0x106A6160
	template struct LeafWord<0x106A6160, 0>;

	// FUNCTION: ENGINE 0x106A7700
	template struct LeafUnsignedHalf<0x106A7700, 1024>;

	// FUNCTION: ENGINE 0x106A7A60
	template void LeafNothing<0x106A7A60>();

	// FUNCTION: ENGINE 0x106A7A70
	template struct LeafCreateStacked<0x106A7A70, 1>;

	// FUNCTION: ENGINE 0x106A7AD0
	template struct LeafArray<0x106A7AD0, 12>;

	// FUNCTION: ENGINE 0x106A7AE0
	template struct LeafInitThree<0x106A7AE0>;

	// FUNCTION: ENGINE 0x106A7B00
	template struct LeafInitFour<0x106A7B00>;

	// FUNCTION: ENGINE 0x106A80C0
	template void LeafNothing<0x106A80C0>();

	// FUNCTION: ENGINE 0x106A80D0
	template void LeafNothing<0x106A80D0>();

	// FUNCTION: ENGINE 0x106A80E0
	template void LeafNothing<0x106A80E0>();

	// FUNCTION: ENGINE 0x106A80F0
	template struct LeafNext<0x106A80F0, 48>;

	// FUNCTION: ENGINE 0x106A8110
	template struct LeafWord<0x106A8110, 8>;

	// FUNCTION: ENGINE 0x106A8120
	template struct LeafNext<0x106A8120, 48>;

	// FUNCTION: ENGINE 0x106A8D70
	template struct LeafIncrement<0x106A8D70>;

	// FUNCTION: ENGINE 0x106A8D80
	template struct LeafDecrement<0x106A8D80>;

	// FUNCTION: ENGINE 0x106A8E90
	template struct LeafSelf<0x106A8E90>;

	// FUNCTION: ENGINE 0x106A8FC0
	template struct LeafFloat<0x106A8FC0, 4>;

	// FUNCTION: ENGINE 0x106A8FD0
	template struct LeafFloat<0x106A8FD0, 0>;

	// FUNCTION: ENGINE 0x106A9200
	template struct LeafSignedBit<0x106A9200, 16, 2>;

	// FUNCTION: ENGINE 0x106A9210
	template struct LeafWord<0x106A9210, 0>;

	// FUNCTION: ENGINE 0x106A9220
	template struct LeafWordPlusOne<0x106A9220, 4>;

	// FUNCTION: ENGINE 0x106A9230
	template struct LeafHalf<0x106A9230, 0>;

	// FUNCTION: ENGINE 0x106A9240
	template struct LeafWord<0x106A9240, 8>;

	// FUNCTION: ENGINE 0x106A9250
	template struct LeafWord<0x106A9250, 28>;

	// FUNCTION: ENGINE 0x106A9290
	template struct LeafArray<0x106A9290, 8>;

	// FUNCTION: ENGINE 0x106A92A0
	template struct LeafWord<0x106A92A0, 4>;

	// FUNCTION: ENGINE 0x106A92B0
	template struct LeafArray<0x106A92B0, 36>;

	// FUNCTION: ENGINE 0x106A92C0
	template struct LeafWord<0x106A92C0, 4>;

	// FUNCTION: ENGINE 0x106A92D0
	template struct LeafArray<0x106A92D0, 16>;

	// FUNCTION: ENGINE 0x106A92E0
	template struct LeafWord<0x106A92E0, 0>;

	// FUNCTION: ENGINE 0x106A92F0
	template struct LeafWord<0x106A92F0, 4>;

	// FUNCTION: ENGINE 0x106A9300
	template struct LeafArray<0x106A9300, 64>;

	// FUNCTION: ENGINE 0x106A9310
	template struct LeafWord<0x106A9310, 0>;

	// FUNCTION: ENGINE 0x106A9340
	template struct LeafArray<0x106A9340, 32>;

	// FUNCTION: ENGINE 0x106A9350
	template struct LeafWord<0x106A9350, 0>;

	// FUNCTION: ENGINE 0x106A9380
	template struct LeafArray<0x106A9380, 32>;

	// FUNCTION: ENGINE 0x106A9390
	template struct LeafWord<0x106A9390, 0>;

	// FUNCTION: ENGINE 0x106A93A0
	template struct LeafArray<0x106A93A0, 16>;

	// FUNCTION: ENGINE 0x106A93B0
	template struct LeafWord<0x106A93B0, 0>;

	// FUNCTION: ENGINE 0x106A93C0
	template struct LeafArray<0x106A93C0, 28>;

	// FUNCTION: ENGINE 0x106A93E0
	template struct LeafInitTwo<0x106A93E0, 0, 0>;

	// FUNCTION: ENGINE 0x106A9400
	template struct LeafInitTwo<0x106A9400, 0, 0>;

	// FUNCTION: ENGINE 0x106A9420
	template struct LeafArray<0x106A9420, 8>;

	// FUNCTION: ENGINE 0x106A9430
	template struct LeafArray<0x106A9430, 8>;

	// FUNCTION: ENGINE 0x106A9440
	template struct LeafArray<0x106A9440, 12>;

	// FUNCTION: ENGINE 0x106A9490
	template struct LeafCreate<0x106A9490, 72>;

	// FUNCTION: ENGINE 0x106A94C0
	template struct LeafCreate<0x106A94C0, 128>;

	// FUNCTION: ENGINE 0x106AA3F0
	template struct LeafWord<0x106AA3F0, 0>;

	// FUNCTION: ENGINE 0x106AA400
	template struct LeafWord<0x106AA400, 0>;

	// FUNCTION: ENGINE 0x106AA410
	template struct LeafSignedHalf<0x106AA410, 8>;

	// FUNCTION: ENGINE 0x106AA420
	template struct LeafHalf<0x106AA420, 0>;

	// FUNCTION: ENGINE 0x106AA430
	template struct LeafHalf<0x106AA430, 2>;

	// FUNCTION: ENGINE 0x106AA440
	template struct LeafHalf<0x106AA440, 8>;

	// FUNCTION: ENGINE 0x106AA460
	template struct LeafHalf<0x106AA460, 6>;

	// FUNCTION: ENGINE 0x106AA470
	template struct LeafHalf<0x106AA470, 4>;

	// FUNCTION: ENGINE 0x106AA480
	template struct LeafBit<0x106AA480, 10, 1>;

	// FUNCTION: ENGINE 0x106AA490
	template struct LeafBit<0x106AA490, 10, 2>;

	// FUNCTION: ENGINE 0x106AA4A0
	template struct LeafBit<0x106AA4A0, 10, 3>;

	// FUNCTION: ENGINE 0x106AA4B0
	template struct LeafBit<0x106AA4B0, 10, 4>;

	// FUNCTION: ENGINE 0x106AA5A0
	template struct LeafInitTwo<0x106AA5A0, 0, 0>;

	// FUNCTION: ENGINE 0x106AA5C0
	template struct LeafArray<0x106AA5C0, 12>;

	// FUNCTION: ENGINE 0x106AA5D0
	template struct LeafArray<0x106AA5D0, 304>;

	// FUNCTION: ENGINE 0x106AA610
	template struct LeafArray<0x106AA610, 28>;

	// FUNCTION: ENGINE 0x106AA630
	template struct LeafPush<0x106AA630, 8>;

	// FUNCTION: ENGINE 0x106AA660
	template struct LeafInitTwo<0x106AA660, 0, 0>;

	// FUNCTION: ENGINE 0x106AA6A0
	template struct LeafPush<0x106AA6A0, 8>;

	// FUNCTION: ENGINE 0x106AA6D0
	template struct LeafPush<0x106AA6D0, 8>;

	// FUNCTION: ENGINE 0x106AA700
	template struct LeafTwoWords<0x106AA700>;

	// FUNCTION: ENGINE 0x106AA720
	template struct LeafCreate<0x106AA720, 64>;

	// FUNCTION: ENGINE 0x106AA750
	template struct LeafCreate<0x106AA750, 16>;

	// FUNCTION: ENGINE 0x106AA780
	template struct LeafCreate<0x106AA780, 32>;

	// FUNCTION: ENGINE 0x106AA7B0
	template struct LeafCreate<0x106AA7B0, 32>;

	// FUNCTION: ENGINE 0x106AA7E0
	template struct LeafCreate<0x106AA7E0, 36>;

	// FUNCTION: ENGINE 0x106AA810
	template struct LeafCreate<0x106AA810, 16>;

	// FUNCTION: ENGINE 0x106AA840
	template struct LeafCreate<0x106AA840, 2>;

	// FUNCTION: ENGINE 0x106AA870
	template struct LeafSetTwoWords<0x106AA870>;

	// FUNCTION: ENGINE 0x106AA8A0
	template struct LeafHalfIndexed<0x106AA8A0, 72>;

	// FUNCTION: ENGINE 0x106AA8B0
	template struct LeafHalfIndexed<0x106AA8B0, 96>;

	// FUNCTION: ENGINE 0x106AA8C0
	template struct LeafHalfIndexed<0x106AA8C0, 84>;

	// FUNCTION: ENGINE 0x106AB0F0
	template struct LeafZeroThree<0x106AB0F0>;

	// FUNCTION: ENGINE 0x106AB100
	template struct LeafCreateCapacity<0x106AB100, 8>;

	// FUNCTION: ENGINE 0x106AB3C0
	template struct LeafSignedBit<0x106AB3C0, 0, 1>;

	// FUNCTION: ENGINE 0x106AB3D0
	template struct LeafSignedBit<0x106AB3D0, 0, 2>;

	// FUNCTION: ENGINE 0x106AB3E0
	template struct LeafBit<0x106AB3E0, 10, 0>;

	// FUNCTION: ENGINE 0x106AB3F0
	template struct LeafPush<0x106AB3F0, 4>;

	// FUNCTION: ENGINE 0x106AB410
	template struct LeafWord<0x106AB410, 4>;

	// FUNCTION: ENGINE 0x106AB420
	template struct LeafArray<0x106AB420, 2>;

	// FUNCTION: ENGINE 0x106AB430
	template struct LeafArray<0x106AB430, 12>;

	// FUNCTION: ENGINE 0x106AB440
	template struct LeafWord<0x106AB440, 4>;

	// FUNCTION: ENGINE 0x106AB450
	template struct LeafSetTwoWords<0x106AB450>;

	// FUNCTION: ENGINE 0x106AB5E0
	template struct LeafCreateCapacity<0x106AB5E0, 4>;

	// FUNCTION: ENGINE 0x106AB610
	template struct LeafCreateCapacity<0x106AB610, 4>;

	// FUNCTION: ENGINE 0x106ABB20
	template void LeafNothing<0x106ABB20>();

	// FUNCTION: ENGINE 0x106ABB30
	template struct LeafCreateAligned<0x106ABB30, 2>;

	// FUNCTION: ENGINE 0x106ABB70
	template struct LeafInitThreeLast<0x106ABB70>;

	// FUNCTION: ENGINE 0x106ABD70
	template struct LeafEqualsPair<0x106ABD70>;

	// FUNCTION: ENGINE 0x106ABE00
	template struct LeafAddShort<0x106ABE00>;

	// FUNCTION: ENGINE 0x106ABE60
	template struct LeafSignedBit<0x106ABE60, 0, 0>;

	// FUNCTION: ENGINE 0x106ABE80
	template struct LeafNext<0x106ABE80, 12>;

	// FUNCTION: ENGINE 0x106ABEA0
	template struct LeafArray<0x106ABEA0, 2>;

	// FUNCTION: ENGINE 0x106ABEB0
	template struct LeafArray<0x106ABEB0, 8>;

	// FUNCTION: ENGINE 0x106ABEC0
	template struct LeafBucket<0x106ABEC0>;

	// FUNCTION: ENGINE 0x106AC1E0
	template struct LeafWord<0x106AC1E0, 8>;

	// FUNCTION: ENGINE 0x106AC1F0
	template struct LeafArray<0x106AC1F0, 1>;

	// FUNCTION: ENGINE 0x106AC200
	template struct LeafArray<0x106AC200, 4>;

	// FUNCTION: ENGINE 0x106AC210
	template struct LeafNext<0x106AC210, 2>;

	// FUNCTION: ENGINE 0x106AC220
	template struct LeafPush<0x106AC220, 4>;

	// FUNCTION: ENGINE 0x106AC960
	template struct LeafClearWord<0x106AC960, 184>;

	// FUNCTION: ENGINE 0x106AC970
	template struct LeafWord<0x106AC970, 4>;

	// FUNCTION: ENGINE 0x106ACBC0
	template struct LeafWord<0x106ACBC0, 8>;

	// FUNCTION: ENGINE 0x106ACBF0
	template struct LeafArray<0x106ACBF0, 4>;

	// FUNCTION: ENGINE 0x106ACC00
	template struct LeafSetWord<0x106ACC00, 4>;

	// FUNCTION: ENGINE 0x106ACC10
	template struct LeafArray<0x106ACC10, 16>;

	// FUNCTION: ENGINE 0x106ACC20
	template struct LeafArray<0x106ACC20, 16>;

	// FUNCTION: ENGINE 0x106ACC30
	template struct LeafArray<0x106ACC30, 16>;

	// FUNCTION: ENGINE 0x106ACC40
	template struct LeafInitTwo<0x106ACC40, 0, 0>;

	// FUNCTION: ENGINE 0x106ACC90
	template struct LeafArray<0x106ACC90, 16>;

	// FUNCTION: ENGINE 0x106ACCA0
	template struct LeafWord<0x106ACCA0, 4>;

	// FUNCTION: ENGINE 0x106AD270
	template struct LeafInitWordShort<0x106AD270>;

	// FUNCTION: ENGINE 0x106AD290
	template struct LeafInitWordShortShort<0x106AD290>;

	// FUNCTION: ENGINE 0x106AD2B0
	template struct LeafEqualsWord<0x106AD2B0>;

	// FUNCTION: ENGINE 0x106AD2D0
	template struct LeafInlineWord<0x106AD2D0, 24>;

	// FUNCTION: ENGINE 0x106AD340
	template struct LeafArray<0x106AD340, 8>;

	// FUNCTION: ENGINE 0x106AD350
	template struct LeafArray<0x106AD350, 4>;

	// FUNCTION: ENGINE 0x106AD360
	template struct LeafNext<0x106AD360, 8>;

	// FUNCTION: ENGINE 0x106AD370
	template struct LeafPush<0x106AD370, 8>;

	// FUNCTION: ENGINE 0x106AD3A0
	template struct LeafWord<0x106AD3A0, 8>;

	// FUNCTION: ENGINE 0x106AD3B0
	template struct LeafArray<0x106AD3B0, 8>;

	// FUNCTION: ENGINE 0x106AD3C0
	template struct LeafArray<0x106AD3C0, 4>;

	// FUNCTION: ENGINE 0x106AD3D0
	template struct LeafPush<0x106AD3D0, 4>;

	// FUNCTION: ENGINE 0x106AD3F0
	template struct LeafArray<0x106AD3F0, 4>;

	// FUNCTION: ENGINE 0x106AD400
	template struct LeafWord<0x106AD400, 4>;

	// FUNCTION: ENGINE 0x106AD410
	template struct LeafTwoWords<0x106AD410>;

	// FUNCTION: ENGINE 0x106AD450
	template struct LeafSetTwoWords<0x106AD450>;

	// FUNCTION: ENGINE 0x106AD960
	template struct LeafZeroThree<0x106AD960>;

	// FUNCTION: ENGINE 0x106AD970
	template struct LeafCreateCapacity<0x106AD970, 8>;

	// FUNCTION: ENGINE 0x106AD9A0
	template struct LeafCreateCapacity<0x106AD9A0, 4>;

	// FUNCTION: ENGINE 0x106AEDF0
	template struct LeafSelf<0x106AEDF0>;

	// FUNCTION: ENGINE 0x106AF010
	template struct LeafInitTwo<0x106AF010, 0, 0>;

	// FUNCTION: ENGINE 0x106AF060
	template struct LeafCreateStacked<0x106AF060, 20>;

	// FUNCTION: ENGINE 0x106AF0A0
	template struct LeafWord<0x106AF0A0, 4>;

	// FUNCTION: ENGINE 0x106AF0B0
	template void LeafNothing<0x106AF0B0>();

	// FUNCTION: ENGINE 0x106AF0C0
	template struct LeafCreateStacked<0x106AF0C0, 36>;

	// FUNCTION: ENGINE 0x106AF100
	template void LeafNothing<0x106AF100>();

	// FUNCTION: ENGINE 0x106AF110
	template struct LeafCreateStacked<0x106AF110, 20>;

	// FUNCTION: ENGINE 0x106AF150
	template struct LeafSetWord<0x106AF150, 4>;

	// FUNCTION: ENGINE 0x106AF160
	template struct LeafArray<0x106AF160, 36>;

	// FUNCTION: ENGINE 0x106AF170
	template struct LeafArray<0x106AF170, 36>;

	// FUNCTION: ENGINE 0x106AF180
	template struct LeafWord<0x106AF180, 4>;

	// FUNCTION: ENGINE 0x106AF190
	template void LeafNothing<0x106AF190>();

	// FUNCTION: ENGINE 0x106AF1A0
	template struct LeafCreateStacked<0x106AF1A0, 36>;

	// FUNCTION: ENGINE 0x106AF1E0
	template struct LeafSetWord<0x106AF1E0, 4>;

	// FUNCTION: ENGINE 0x106AF1F0
	template void LeafNothing<0x106AF1F0>();

	// FUNCTION: ENGINE 0x106AF200
	template struct LeafCreateStacked<0x106AF200, 2>;

	// FUNCTION: ENGINE 0x106AF240
	template struct LeafSetWord<0x106AF240, 4>;

	// FUNCTION: ENGINE 0x106AF250
	template void LeafNothing<0x106AF250>();

	// FUNCTION: ENGINE 0x106AF260
	template struct LeafCreateAligned<0x106AF260, 4>;

	// FUNCTION: ENGINE 0x106AF350
	template struct LeafSetWord<0x106AF350, 4>;

	// FUNCTION: ENGINE 0x106AF360
	template struct LeafCopyIn<0x106AF360, 20>;

	// FUNCTION: ENGINE 0x106AF380
	template struct LeafWord<0x106AF380, 0>;

	// FUNCTION: ENGINE 0x106AF390
	template struct LeafSetWord<0x106AF390, 4>;

	// FUNCTION: ENGINE 0x106AF3A0
	template struct LeafCopyIn<0x106AF3A0, 36>;

	// FUNCTION: ENGINE 0x106AF3C0
	template struct LeafWord<0x106AF3C0, 0>;

	// FUNCTION: ENGINE 0x106AF3D0
	template struct LeafWord<0x106AF3D0, 4>;

	// FUNCTION: ENGINE 0x106AF3E0
	template struct LeafCopyIn<0x106AF3E0, 20>;

	// FUNCTION: ENGINE 0x106AF400
	template struct LeafWord<0x106AF400, 0>;

	// FUNCTION: ENGINE 0x106AF410
	template struct LeafWord<0x106AF410, 4>;

	// FUNCTION: ENGINE 0x106AF420
	template struct LeafTwoWords<0x106AF420>;

	// FUNCTION: ENGINE 0x106AF440
	template struct LeafTwoWords<0x106AF440>;

	// FUNCTION: ENGINE 0x106AF460
	template struct LeafTwoWords<0x106AF460>;

	// FUNCTION: ENGINE 0x106AF480
	template struct LeafTwoWords<0x106AF480>;

	// FUNCTION: ENGINE 0x106AF9C0
	template struct LeafAssign<0x106AF9C0, 20>;

	// FUNCTION: ENGINE 0x106AFA30
	template struct LeafAssign<0x106AFA30, 36>;

	// FUNCTION: ENGINE 0x106AFAC0
	template struct LeafAssign<0x106AFAC0, 20>;

	// FUNCTION: ENGINE 0x106AFB30
	template struct LeafInitThreeLast<0x106AFB30>;

	// FUNCTION: ENGINE 0x106AFB50
	template struct LeafInitThree<0x106AFB50>;

	// FUNCTION: ENGINE 0x106AFB70
	template struct LeafInitThree<0x106AFB70>;

	// FUNCTION: ENGINE 0x106AFB90
	template struct LeafInitThree<0x106AFB90>;

	// FUNCTION: ENGINE 0x106AFBB0
	template struct LeafInitThree<0x106AFBB0>;

	// FUNCTION: ENGINE 0x106AFBD0
	template struct LeafInitThree<0x106AFBD0>;

	// FUNCTION: ENGINE 0x106AFBF0
	template struct LeafInitFour<0x106AFBF0>;

	// FUNCTION: ENGINE 0x106AFC10
	template struct LeafInitFour<0x106AFC10>;

	// FUNCTION: ENGINE 0x106AFC30
	template struct LeafInitFour<0x106AFC30>;

	// FUNCTION: ENGINE 0x106AFC50
	template struct LeafInitFour<0x106AFC50>;

	// FUNCTION: ENGINE 0x106AFC70
	template struct LeafInitFour<0x106AFC70>;

	// FUNCTION: ENGINE 0x106B23F0
	template void LeafNothing<0x106B23F0>();

	// FUNCTION: ENGINE 0x106B2400
	template void LeafNothing<0x106B2400>();

	// FUNCTION: ENGINE 0x106B2410
	template void LeafNothing<0x106B2410>();

	// FUNCTION: ENGINE 0x106B2890
	template bool LeafFalse<0x106B2890>();

	// FUNCTION: ENGINE 0x106B28A0
	template bool LeafFalse<0x106B28A0>();

	// FUNCTION: ENGINE 0x106B28B0
	template bool LeafFalse<0x106B28B0>();

	// FUNCTION: ENGINE 0x106B28E0
	template struct LeafIncrement<0x106B28E0>;

	// FUNCTION: ENGINE 0x106B2910
	template struct LeafLessThan<0x106B2910, 0>;

	// FUNCTION: ENGINE 0x106B2940
	template struct LeafByte<0x106B2940, 44>;

	// FUNCTION: ENGINE 0x106B2950
	template struct LeafByte<0x106B2950, 45>;

	// FUNCTION: ENGINE 0x106B2960
	template struct LeafWord<0x106B2960, 48>;

	// FUNCTION: ENGINE 0x106B3060
	template struct LeafZeroTwoIgnoring<0x106B3060>;

	// FUNCTION: ENGINE 0x106B3550
	template struct LeafDecrement<0x106B3550>;

	// FUNCTION: ENGINE 0x106B3570
	template struct LeafSelf<0x106B3570>;

	// FUNCTION: ENGINE 0x106B3580
	template struct LeafAddress<0x106B3580, 8>;

	// FUNCTION: ENGINE 0x106B35B0
	template struct LeafSelf<0x106B35B0>;

	// FUNCTION: ENGINE 0x106B35C0
	template struct LeafAddress<0x106B35C0, 40>;

	// FUNCTION: ENGINE 0x106B3600
	template struct LeafArray<0x106B3600, 64>;

	// FUNCTION: ENGINE 0x106B39D0
	template struct LeafDecrement<0x106B39D0>;

	// FUNCTION: ENGINE 0x106B3B70
	template struct LeafDecrement<0x106B3B70>;

	// FUNCTION: ENGINE 0x106B3CD0
	template struct LeafDecrement<0x106B3CD0>;

	// FUNCTION: ENGINE 0x106B3CF0
	template struct LeafWord<0x106B3CF0, 80>;

	// FUNCTION: ENGINE 0x106B3D10
	template struct LeafInitTwo<0x106B3D10, 0, 0>;

	// FUNCTION: ENGINE 0x106B3D60
	template struct LeafWord<0x106B3D60, 4>;

	// FUNCTION: ENGINE 0x106B3D90
	template void LeafNothing<0x106B3D90>();

	// FUNCTION: ENGINE 0x106B3DA0
	template struct LeafCreateStacked<0x106B3DA0, 4>;

	// FUNCTION: ENGINE 0x106B3DE0
	template struct LeafPush<0x106B3DE0, 4>;

	// FUNCTION: ENGINE 0x106B3E00
	template struct LeafArray<0x106B3E00, 4>;

	// FUNCTION: ENGINE 0x106B3E10
	template struct LeafWord<0x106B3E10, 0>;

	// FUNCTION: ENGINE 0x106B3E20
	template struct LeafEnd<0x106B3E20, 4>;

	// FUNCTION: ENGINE 0x106B3E30
	template struct LeafWord<0x106B3E30, 4>;

	// FUNCTION: ENGINE 0x106B3E40
	template void LeafNothing<0x106B3E40>();

	// FUNCTION: ENGINE 0x106B3E50
	template struct LeafCreateStacked<0x106B3E50, 4>;

	// FUNCTION: ENGINE 0x106B3E90
	template struct LeafLast<0x106B3E90, 4>;

	// FUNCTION: ENGINE 0x106B3EA0
	template void LeafNothing<0x106B3EA0>();

	// FUNCTION: ENGINE 0x106B3EB0
	template struct LeafCreateStacked<0x106B3EB0, 16>;

	// FUNCTION: ENGINE 0x106B3F10
	template void LeafNothing<0x106B3F10>();

	// FUNCTION: ENGINE 0x106B3F20
	template struct LeafCreateAligned<0x106B3F20, 8>;

	// FUNCTION: ENGINE 0x106B3F60
	template struct LeafArray<0x106B3F60, 8>;

	// FUNCTION: ENGINE 0x106B3F70
	template struct LeafTwoWords<0x106B3F70>;

	// FUNCTION: ENGINE 0x106B3F90
	template struct LeafTwoWords<0x106B3F90>;

	// FUNCTION: ENGINE 0x106B3FB0
	template struct LeafTwoWords<0x106B3FB0>;

	// FUNCTION: ENGINE 0x106B4060
	template int LeafDereference<0x106B4060>(const int*);

	// FUNCTION: ENGINE 0x106B4070
	template struct LeafPairOfPointers<0x106B4070>;

	// FUNCTION: ENGINE 0x106B4090
	template int LeafZero<0x106B4090>();

	// FUNCTION: ENGINE 0x106B40A0
	template int LeafZero<0x106B40A0>();

	// FUNCTION: ENGINE 0x106B40B0
	template void LeafSwap<0x106B40B0>(int*, int*);

	// FUNCTION: ENGINE 0x106B40D0
	template int LeafFirstArgument<0x106B40D0>(int);

	// FUNCTION: ENGINE 0x106B4250
	template struct LeafInitThreeLast<0x106B4250>;

	// FUNCTION: ENGINE 0x106B4270
	template struct LeafInitThree<0x106B4270>;

	// FUNCTION: ENGINE 0x106B4290
	template struct LeafInitThree<0x106B4290>;

	// FUNCTION: ENGINE 0x106B42B0
	template struct LeafInitThree<0x106B42B0>;

	// FUNCTION: ENGINE 0x106B42D0
	template int LeafDereference<0x106B42D0>(const int*);

	// FUNCTION: ENGINE 0x106B42E0
	template void LeafSwap<0x106B42E0>(int*, int*);

	// FUNCTION: ENGINE 0x106B45C0
	template struct LeafInitFour<0x106B45C0>;

	// FUNCTION: ENGINE 0x106B45E0
	template struct LeafInitFour<0x106B45E0>;

	// FUNCTION: ENGINE 0x106B4600
	template struct LeafInitFour<0x106B4600>;

	// FUNCTION: ENGINE 0x106B53E0
	template struct LeafDecrement<0x106B53E0>;

	// FUNCTION: ENGINE 0x106B5460
	template struct LeafAddress<0x106B5460, 4>;

	// FUNCTION: ENGINE 0x106B5470
	template struct LeafWord<0x106B5470, 0>;

	// FUNCTION: ENGINE 0x106B5480
	template struct LeafWord<0x106B5480, 12>;

	// FUNCTION: ENGINE 0x106B5490
	template struct LeafWord<0x106B5490, 20>;

	// FUNCTION: ENGINE 0x106B54C0
	template struct LeafArray<0x106B54C0, 8>;

	// FUNCTION: ENGINE 0x106B5640
	template struct LeafIncrement<0x106B5640>;

	// FUNCTION: ENGINE 0x106B5650
	template struct LeafDecrement<0x106B5650>;

	// FUNCTION: ENGINE 0x106B5720
	template struct LeafAddress<0x106B5720, 24>;

	// FUNCTION: ENGINE 0x106B5730
	template struct LeafAddress<0x106B5730, 24>;

	// FUNCTION: ENGINE 0x106B5740
	template struct LeafAddress<0x106B5740, 36>;

	// FUNCTION: ENGINE 0x106B5750
	template struct LeafAddress<0x106B5750, 12>;

	// FUNCTION: ENGINE 0x106B5760
	template struct LeafAddress<0x106B5760, 58>;

	// FUNCTION: ENGINE 0x106B5800
	template struct LeafWord<0x106B5800, 84>;

	// FUNCTION: ENGINE 0x106B5810
	template struct LeafPairPointerWord<0x106B5810>;

	// FUNCTION: ENGINE 0x106B5830
	template struct LeafLessThan<0x106B5830, 4>;

	// FUNCTION: ENGINE 0x106B58D0
	template struct LeafTwoWords<0x106B58D0>;

	// FUNCTION: ENGINE 0x106B58F0
	template struct LeafTwoWords<0x106B58F0>;

	// FUNCTION: ENGINE 0x106B5910
	template struct LeafTwoWords<0x106B5910>;

	// FUNCTION: ENGINE 0x106B5930
	template struct LeafTwoWords<0x106B5930>;

	// FUNCTION: ENGINE 0x106B5950
	template struct LeafZeroTwoIgnoring<0x106B5950>;

	// FUNCTION: ENGINE 0x106B5970
	template struct LeafWord<0x106B5970, 0>;

	// FUNCTION: ENGINE 0x106B5980
	template struct LeafArray<0x106B5980, 12>;

	// FUNCTION: ENGINE 0x106B5990
	template struct LeafCount<0x106B5990, 4, 0, 4>;

	// FUNCTION: ENGINE 0x106B59A0
	template struct LeafWord<0x106B59A0, 0>;

	// FUNCTION: ENGINE 0x106B59C0
	template struct LeafWord<0x106B59C0, 0>;

	// FUNCTION: ENGINE 0x106B59D0
	template struct LeafCount<0x106B59D0, 52, 0, 8>;

	// FUNCTION: ENGINE 0x106B59F0
	template struct LeafArray<0x106B59F0, 52>;

	// FUNCTION: ENGINE 0x106B5A00
	template struct LeafWordsEqual<0x106B5A00, 4, 8>;

	// FUNCTION: ENGINE 0x106B5A10
	template struct LeafArray<0x106B5A10, 4>;

	// FUNCTION: ENGINE 0x106B5A20
	template struct LeafWord<0x106B5A20, 4>;

	// FUNCTION: ENGINE 0x106B5A30
	template struct LeafWordsEqual<0x106B5A30, 4, 8>;

	// FUNCTION: ENGINE 0x106B5A80
	template struct LeafWord<0x106B5A80, 0>;

	// FUNCTION: ENGINE 0x106B5A90
	template struct LeafCount<0x106B5A90, 24, 0, 4>;

	// FUNCTION: ENGINE 0x106B5AB0
	template struct LeafArray<0x106B5AB0, 12>;

	// FUNCTION: ENGINE 0x106B5AC0
	template struct LeafZeroTwoIgnoring<0x106B5AC0>;

	// FUNCTION: ENGINE 0x106B5AE0
	template struct LeafWord<0x106B5AE0, 0>;

	// FUNCTION: ENGINE 0x106B5AF0
	template struct LeafArray<0x106B5AF0, 12>;

	// FUNCTION: ENGINE 0x106B5B00
	template struct LeafWord<0x106B5B00, 0>;

	// FUNCTION: ENGINE 0x106B5B10
	template struct LeafWord<0x106B5B10, 4>;

	// FUNCTION: ENGINE 0x106B5B20
	template struct LeafCount<0x106B5B20, 8, 0, 4>;

	// FUNCTION: ENGINE 0x106B5B30
	template struct LeafWordsEqual<0x106B5B30, 4, 8>;

	// FUNCTION: ENGINE 0x106B5B40
	template struct LeafArray<0x106B5B40, 8>;

	// FUNCTION: ENGINE 0x106B5C20
	template struct LeafSelf<0x106B5C20>;

	// FUNCTION: ENGINE 0x106B5C30
	template void LeafNothing<0x106B5C30>();

	// FUNCTION: ENGINE 0x106B5C90
	template struct LeafSelf<0x106B5C90>;

	// FUNCTION: ENGINE 0x106B5CA0
	template void LeafNothing<0x106B5CA0>();

	// FUNCTION: ENGINE 0x106B5D50
	template LeafSized<0x106B5D50, 4>* ScratchStack::AllocArray<LeafSized<0x106B5D50, 4> >(int, int);

	// FUNCTION: ENGINE 0x106B5DC0
	template LeafSized<0x106B5DC0, 4>* ScratchStack::AllocArray<LeafSized<0x106B5DC0, 4> >(int, int);

	// FUNCTION: ENGINE 0x106B5E00
	template int LeafZero<0x106B5E00>();

	// FUNCTION: ENGINE 0x106B5E10
	template void LeafCopyWord<0x106B5E10>(int*, const int*);

	// FUNCTION: ENGINE 0x106B5E20
	template LeafSized<0x106B5E20, 116>* ScratchStack::AllocArray<LeafSized<0x106B5E20, 116> >(int, int);

	// FUNCTION: ENGINE 0x106B5E50
	template void LeafNothing<0x106B5E50>();

	// FUNCTION: ENGINE 0x106B5E80
	template void LeafNothing<0x106B5E80>();

	// FUNCTION: ENGINE 0x106B5E90
	template void LeafNothing<0x106B5E90>();

	// FUNCTION: ENGINE 0x106B5EA0
	template int LeafDereference<0x106B5EA0>(const int*);

	// FUNCTION: ENGINE 0x106B5EB0
	template int LeafFirstArgument<0x106B5EB0>(int);

	// FUNCTION: ENGINE 0x106B5F00
	template int LeafDereference<0x106B5F00>(const int*);

	// FUNCTION: ENGINE 0x106B5F10
	template int LeafDereference<0x106B5F10>(const int*);

	// FUNCTION: ENGINE 0x106B5F20
	template struct LeafPairOfPointers<0x106B5F20>;

	// FUNCTION: ENGINE 0x106B5F40
	template struct LeafPairOfPointers<0x106B5F40>;

	// FUNCTION: ENGINE 0x106B5F60
	template struct LeafPairOfPointers<0x106B5F60>;

	// FUNCTION: ENGINE 0x106B5F80
	template int LeafZero<0x106B5F80>();

	// FUNCTION: ENGINE 0x106B5F90
	template int LeafZero<0x106B5F90>();

	// FUNCTION: ENGINE 0x106B5FA0
	template int LeafZero<0x106B5FA0>();

	// FUNCTION: ENGINE 0x106B5FB0
	template int LeafZero<0x106B5FB0>();

	// FUNCTION: ENGINE 0x106B5FC0
	template int LeafZero<0x106B5FC0>();

	// FUNCTION: ENGINE 0x106B6030
	template void LeafSwap<0x106B6030>(int*, int*);

	// FUNCTION: ENGINE 0x106B60C0
	template int LeafFirstArgument<0x106B60C0>(int);

	// FUNCTION: ENGINE 0x106B6140
	template int LeafFirstArgument<0x106B6140>(int);

	// FUNCTION: ENGINE 0x106B61C0
	template int LeafFirstArgument<0x106B61C0>(int);

	// FUNCTION: ENGINE 0x106B6810
	template struct LeafZeroThree<0x106B6810>;

	// FUNCTION: ENGINE 0x106B68A0
	template struct LeafZeroThree<0x106B68A0>;

	// FUNCTION: ENGINE 0x106B68C0
	template struct LeafZeroThree<0x106B68C0>;

	// FUNCTION: ENGINE 0x106B6970
	template void LeafNothing<0x106B6970>();

	// FUNCTION: ENGINE 0x106B6A00
	template void LeafNothing<0x106B6A00>();

	// FUNCTION: ENGINE 0x106B6A10
	template void LeafNothing<0x106B6A10>();

	// FUNCTION: ENGINE 0x106B6AB0
	template int LeafDereference<0x106B6AB0>(const int*);

	// FUNCTION: ENGINE 0x106B6B00
	template int LeafDereference<0x106B6B00>(const int*);

	// FUNCTION: ENGINE 0x106B6B10
	template int LeafDereference<0x106B6B10>(const int*);

	// FUNCTION: ENGINE 0x106B6B80
	template void LeafSwap<0x106B6B80>(int*, int*);

	// FUNCTION: ENGINE 0x106B7310
	template void LeafNothing<0x106B7310>();

	// FUNCTION: ENGINE 0x106B7B30
	template struct LeafWord<0x106B7B30, 4>;

	// FUNCTION: ENGINE 0x106B7B40
	template struct LeafWord<0x106B7B40, 8>;

	// FUNCTION: ENGINE 0x106BBD60
	template struct LeafFloat<0x106BBD60, 76>;

	// FUNCTION: ENGINE 0x106BBDA0
	template struct LeafFloat<0x106BBDA0, 236>;

	// FUNCTION: ENGINE 0x106BCB00
	template struct LeafWord<0x106BCB00, 12>;

	// FUNCTION: ENGINE 0x106BCB10
	template struct LeafWord<0x106BCB10, 16>;

	// FUNCTION: ENGINE 0x106BF7D0
	template struct LeafSelf<0x106BF7D0>;

	// FUNCTION: ENGINE 0x106BF7E0
	template struct LeafArray<0x106BF7E0, 20>;

	// FUNCTION: ENGINE 0x106BF7F0
	template struct LeafArray<0x106BF7F0, 20>;

	// FUNCTION: ENGINE 0x106BF800
	template struct LeafEnd<0x106BF800, 20>;

	// FUNCTION: ENGINE 0x106BF810
	template struct LeafArray<0x106BF810, 20>;

	// FUNCTION: ENGINE 0x106BF820
	template struct LeafArray<0x106BF820, 20>;

	// FUNCTION: ENGINE 0x106BF830
	template struct LeafWord<0x106BF830, 0>;

	// FUNCTION: ENGINE 0x106BF840
	template struct LeafEnd<0x106BF840, 20>;

	// FUNCTION: ENGINE 0x106BF850
	template struct LeafIsEmpty<0x106BF850>;

	// FUNCTION: ENGINE 0x106BF860
	template struct LeafArray<0x106BF860, 36>;

	// FUNCTION: ENGINE 0x106BF870
	template struct LeafWord<0x106BF870, 0>;

	// FUNCTION: ENGINE 0x106BF880
	template struct LeafEnd<0x106BF880, 36>;

	// FUNCTION: ENGINE 0x106BF890
	template struct LeafEnd<0x106BF890, 36>;

	// FUNCTION: ENGINE 0x106BF8A0
	template struct LeafSelfPointer<0x106BF8A0, 96>;

	// FUNCTION: ENGINE 0x106BF8B0
	template struct LeafSelf<0x106BF8B0>;

	// FUNCTION: ENGINE 0x106BF8C0
	template struct LeafWord<0x106BF8C0, 96>;

	// FUNCTION: ENGINE 0x106BF8D0
	template struct LeafInlineCount<0x106BF8D0, 12, 8>;

	// FUNCTION: ENGINE 0x106BF8F0
	template struct LeafInlineArray<0x106BF8F0, 0, 12>;

	// FUNCTION: ENGINE 0x106BF900
	template struct LeafSelfPointer<0x106BF900, 32>;

	// FUNCTION: ENGINE 0x106BF910
	template struct LeafInlineArray<0x106BF910, 0, 4>;

	// FUNCTION: ENGINE 0x106BF920
	template struct LeafSelfPointer<0x106BF920, 3072>;

	// FUNCTION: ENGINE 0x106BF930
	template struct LeafInlineCount<0x106BF930, 12, 256>;

	// FUNCTION: ENGINE 0x106BF960
	template struct LeafInlineArray<0x106BF960, 0, 12>;

	// FUNCTION: ENGINE 0x106BF970
	template struct LeafSelfPointer<0x106BF970, 1024>;

	// FUNCTION: ENGINE 0x106BF980
	template struct LeafInlineArray<0x106BF980, 0, 4>;

	// FUNCTION: ENGINE 0x106BF9E0
	template struct LeafInlineCount<0x106BF9E0, 4, 8>;

	// FUNCTION: ENGINE 0x106BF9F0
	template struct LeafInlineCount<0x106BF9F0, 4, 256>;
}
