// The tiny leaf functions of 0x10600000 - 0x10620000; see leafstandins.h.
#include <new>
#include "code/core/interlocked.h"
#include "code/core/memutils.h"
#include "code/core/leafstandins.h"

namespace leaf
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
		return items == end;
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


	// FUNCTION: ENGINE 0x10601C20
	template struct LeafWord<0x10601C20, 16>;

	// FUNCTION: ENGINE 0x10601C50
	template struct LeafByte<0x10601C50, 9>;

	// FUNCTION: ENGINE 0x10601C60
	template struct LeafWord<0x10601C60, 4>;

	// FUNCTION: ENGINE 0x10601C70
	template struct LeafSelfPointer<0x10601C70, 8>;

	// FUNCTION: ENGINE 0x10601C80
	template struct LeafSelf<0x10601C80>;

	// FUNCTION: ENGINE 0x10601C90
	template struct LeafWord<0x10601C90, 8>;

	// FUNCTION: ENGINE 0x10601CA0
	template struct LeafInlineCount<0x10601CA0, 4, 2>;

	// FUNCTION: ENGINE 0x10601CB0
	template struct LeafInlineIsEmpty<0x10601CB0, 4, 2>;

	// FUNCTION: ENGINE 0x10601CE0
	template struct LeafInlineArray<0x10601CE0, 0, 4>;

	// FUNCTION: ENGINE 0x10601D70
	template void LeafNothing<0x10601D70>();

	// FUNCTION: ENGINE 0x10601DB0
	template void LeafNothing<0x10601DB0>();

	// FUNCTION: ENGINE 0x10601E20
	template void LeafNothing<0x10601E20>();

	// FUNCTION: ENGINE 0x10602230
	template void LeafNothing<0x10602230>();

	// FUNCTION: ENGINE 0x10603830
	template struct LeafInitTwo<0x10603830, 0, 0>;

	// FUNCTION: ENGINE 0x10604310
	template struct LeafSelf<0x10604310>;

	// FUNCTION: ENGINE 0x10604350
	template struct LeafSelf<0x10604350>;

	// FUNCTION: ENGINE 0x10606330
	template struct LeafArray<0x10606330, 4>;

	// FUNCTION: ENGINE 0x10606340
	template struct LeafArray<0x10606340, 4>;

	// FUNCTION: ENGINE 0x106063A0
	template void LeafNothing<0x106063A0>();

	// FUNCTION: ENGINE 0x10606550
	template void LeafNothing<0x10606550>();

	// FUNCTION: ENGINE 0x10606A40
	template struct LeafSetWord<0x10606A40, 8>;

	// FUNCTION: ENGINE 0x10606A50
	template struct LeafWord<0x10606A50, 8>;

	// FUNCTION: ENGINE 0x10606CB0
	template struct LeafSetWord<0x10606CB0, 4>;

	// FUNCTION: ENGINE 0x10606CC0
	template struct LeafWord<0x10606CC0, 4>;

	// FUNCTION: ENGINE 0x10606CE0
	template struct LeafByte<0x10606CE0, 0>;

	// FUNCTION: ENGINE 0x10606D00
	template struct LeafSetWord<0x10606D00, 60>;

	// FUNCTION: ENGINE 0x10606D50
	template struct LeafWord<0x10606D50, 24>;

	// FUNCTION: ENGINE 0x10606D60
	template void LeafNothing<0x10606D60>();

	// FUNCTION: ENGINE 0x10606E50
	template struct LeafCount<0x10606E50, 8, 8, 12>;

	// FUNCTION: ENGINE 0x10606EC0
	template struct LeafCount<0x10606EC0, 4, 8, 12>;

	// FUNCTION: ENGINE 0x10606F50
	template void LeafNothing<0x10606F50>();

	// FUNCTION: ENGINE 0x10606F80
	template void LeafNothing<0x10606F80>();

	// FUNCTION: ENGINE 0x10606F90
	template void LeafNothing<0x10606F90>();

	// FUNCTION: ENGINE 0x10606FA0
	template void LeafNothing<0x10606FA0>();

	// FUNCTION: ENGINE 0x10608970
	template struct LeafAddress<0x10608970, 32>;

	// FUNCTION: ENGINE 0x10608B70
	template struct LeafWord<0x10608B70, 28>;

	// FUNCTION: ENGINE 0x10608BB0
	template struct LeafCount<0x10608BB0, 4, 0, 8>;

	// FUNCTION: ENGINE 0x10608BC0
	template struct LeafCount<0x10608BC0, 4, 0, 4>;

	// FUNCTION: ENGINE 0x10608BD0
	template struct LeafArray<0x10608BD0, 4>;

	// FUNCTION: ENGINE 0x10608BE0
	template struct LeafArray<0x10608BE0, 4>;

	// FUNCTION: ENGINE 0x10608C40
	template struct LeafSelf<0x10608C40>;

	// FUNCTION: ENGINE 0x10608C50
	template void LeafNothing<0x10608C50>();

	// FUNCTION: ENGINE 0x10608C80
	template void LeafNothing<0x10608C80>();

	// FUNCTION: ENGINE 0x10608E00
	template void LeafNothing<0x10608E00>();

	// FUNCTION: ENGINE 0x10609480
	template struct LeafInitTwo<0x10609480, 0, 0>;

	// FUNCTION: ENGINE 0x10609490
	template struct LeafTwoWords<0x10609490>;

	// FUNCTION: ENGINE 0x106094F0
	template struct LeafEqualsWord<0x106094F0>;

	// FUNCTION: ENGINE 0x10609810
	template void LeafNothing<0x10609810>();

	// FUNCTION: ENGINE 0x10609820
	template void LeafNothing<0x10609820>();

	// FUNCTION: ENGINE 0x10609830
	template void LeafNothing<0x10609830>();

	// FUNCTION: ENGINE 0x10609840
	template void LeafNothing<0x10609840>();

	// FUNCTION: ENGINE 0x10609850
	template void LeafNothing<0x10609850>();

	// FUNCTION: ENGINE 0x10609860
	template void LeafNothing<0x10609860>();

	// FUNCTION: ENGINE 0x10609870
	template void LeafNothing<0x10609870>();

	// FUNCTION: ENGINE 0x10609880
	template void LeafNothing<0x10609880>();

	// FUNCTION: ENGINE 0x10609890
	template void LeafNothing<0x10609890>();

	// FUNCTION: ENGINE 0x106098A0
	template void LeafNothing<0x106098A0>();

	// FUNCTION: ENGINE 0x106098B0
	template void LeafNothing<0x106098B0>();

	// FUNCTION: ENGINE 0x106098C0
	template void LeafNothing<0x106098C0>();

	// FUNCTION: ENGINE 0x106098D0
	template void LeafNothing<0x106098D0>();

	// FUNCTION: ENGINE 0x106098E0
	template void LeafNothing<0x106098E0>();

	// FUNCTION: ENGINE 0x106098F0
	template void LeafNothing<0x106098F0>();

	// FUNCTION: ENGINE 0x1060A410
	template struct LeafWord<0x1060A410, 12>;

	// FUNCTION: ENGINE 0x1060B3C0
	template struct LeafSetWord<0x1060B3C0, 12>;

	// FUNCTION: ENGINE 0x1060B3D0
	template struct LeafSetWord<0x1060B3D0, 8>;

	// FUNCTION: ENGINE 0x1060B810
	template struct LeafByte<0x1060B810, 19>;

	// FUNCTION: ENGINE 0x1060BB40
	template struct LeafWord<0x1060BB40, 644>;

	// FUNCTION: ENGINE 0x1060BC10
	template void LeafNothing<0x1060BC10>();

	// FUNCTION: ENGINE 0x1060DCF0
	template struct LeafIncrement<0x1060DCF0>;

	// FUNCTION: ENGINE 0x1060DD00
	template struct LeafDecrement<0x1060DD00>;

	// FUNCTION: ENGINE 0x1060DD70
	template int LeafDereference<0x1060DD70>(const int*);

	// FUNCTION: ENGINE 0x1060E500
	template struct LeafWord<0x1060E500, 12>;

	// FUNCTION: ENGINE 0x1060E510
	template struct LeafSetWord<0x1060E510, 12>;

	// FUNCTION: ENGINE 0x1060E520
	template struct LeafWord<0x1060E520, 8>;

	// FUNCTION: ENGINE 0x1060E560
	template struct LeafWord<0x1060E560, 12>;

	// FUNCTION: ENGINE 0x1060E570
	template struct LeafSetWord<0x1060E570, 12>;

	// FUNCTION: ENGINE 0x1060E580
	template struct LeafWord<0x1060E580, 8>;

	// FUNCTION: ENGINE 0x1060E5D0
	template struct LeafWord<0x1060E5D0, 8>;

	// FUNCTION: ENGINE 0x1060E600
	template struct LeafWord<0x1060E600, 4>;

	// FUNCTION: ENGINE 0x1060E660
	template struct LeafWord<0x1060E660, 12>;

	// FUNCTION: ENGINE 0x1060F520
	template struct LeafWord<0x1060F520, 0>;

	// FUNCTION: ENGINE 0x1060F530
	template struct LeafWord<0x1060F530, 8>;

	// FUNCTION: ENGINE 0x1060F660
	template void LeafNothing<0x1060F660>();

	// FUNCTION: ENGINE 0x1060F810
	template struct LeafSetWord<0x1060F810, 0>;

	// FUNCTION: ENGINE 0x1060F9E0
	template struct LeafInlineArray<0x1060F9E0, 0, 4>;

	// FUNCTION: ENGINE 0x1060F9F0
	template struct LeafInlineArray<0x1060F9F0, 0, 4>;

	// FUNCTION: ENGINE 0x1060FA00
	template struct LeafSelfPointer<0x1060FA00, 128>;

	// FUNCTION: ENGINE 0x1060FA10
	template struct LeafSelf<0x1060FA10>;

	// FUNCTION: ENGINE 0x1060FA20
	template struct LeafWord<0x1060FA20, 128>;

	// FUNCTION: ENGINE 0x1060FA30
	template struct LeafZeroTwoIgnoring<0x1060FA30>;

	// FUNCTION: ENGINE 0x1060FA50
	template struct LeafZeroTwoIgnoring<0x1060FA50>;

	// FUNCTION: ENGINE 0x1060FA70
	template struct LeafArray<0x1060FA70, 4>;

	// FUNCTION: ENGINE 0x1060FA80
	template struct LeafArray<0x1060FA80, 4>;

	// FUNCTION: ENGINE 0x1060FA90
	template struct LeafInlineCount<0x1060FA90, 8, 16>;

	// FUNCTION: ENGINE 0x1060FB50
	template void LeafNothing<0x1060FB50>();

	// FUNCTION: ENGINE 0x1060FD10
	template void LeafNothing<0x1060FD10>();

	// FUNCTION: ENGINE 0x106103B0
	template void LeafNothing<0x106103B0>();

	// FUNCTION: ENGINE 0x10611200
	template int LeafDereference<0x10611200>(const int*);

	// FUNCTION: ENGINE 0x10611210
	template struct LeafPairOfPointers<0x10611210>;

	// FUNCTION: ENGINE 0x10611230
	template int LeafZero<0x10611230>();

	// FUNCTION: ENGINE 0x10611240
	template int LeafZero<0x10611240>();

	// FUNCTION: ENGINE 0x10611250
	template void LeafSwap<0x10611250>(int*, int*);

	// FUNCTION: ENGINE 0x10611270
	template int LeafFirstArgument<0x10611270>(int);

	// FUNCTION: ENGINE 0x10611380
	template int LeafDereference<0x10611380>(const int*);

	// FUNCTION: ENGINE 0x10611390
	template void LeafSwap<0x10611390>(int*, int*);

	// FUNCTION: ENGINE 0x10611AB0
	template struct LeafIncrement<0x10611AB0>;

	// FUNCTION: ENGINE 0x10611AC0
	template struct LeafDecrement<0x10611AC0>;

	// FUNCTION: ENGINE 0x10611E60
	template struct LeafCount<0x10611E60, 76, 0, 8>;

	// FUNCTION: ENGINE 0x10611E80
	template struct LeafCount<0x10611E80, 76, 0, 4>;

	// FUNCTION: ENGINE 0x10611EA0
	template struct LeafWordsEqual<0x10611EA0, 4, 8>;

	// FUNCTION: ENGINE 0x10611EB0
	template struct LeafArray<0x10611EB0, 76>;

	// FUNCTION: ENGINE 0x10611F10
	template struct LeafSelf<0x10611F10>;

	// FUNCTION: ENGINE 0x10611F20
	template void LeafNothing<0x10611F20>();

	// FUNCTION: ENGINE 0x106121E0
	template void LeafNothing<0x106121E0>();

	// FUNCTION: ENGINE 0x106121F0
	template struct LeafZeroThree<0x106121F0>;

	// FUNCTION: ENGINE 0x10612A60
	template void LeafNothing<0x10612A60>();

	// FUNCTION: ENGINE 0x10613BC0
	template struct LeafAddress<0x10613BC0, 744>;

	// FUNCTION: ENGINE 0x106146C0
	template struct LeafSelf<0x106146C0>;

	// FUNCTION: ENGINE 0x10614710
	template struct LeafAddress<0x10614710, 8>;

	// FUNCTION: ENGINE 0x10614720
	template struct LeafAddress<0x10614720, 80>;

	// FUNCTION: ENGINE 0x10614730
	template struct LeafAddress<0x10614730, 152>;

	// FUNCTION: ENGINE 0x10614740
	template struct LeafAddress<0x10614740, 440>;

	// FUNCTION: ENGINE 0x10614750
	template struct LeafAddress<0x10614750, 224>;

	// FUNCTION: ENGINE 0x10615250
	template struct LeafSelf<0x10615250>;

	// FUNCTION: ENGINE 0x10615260
	template void LeafNothing<0x10615260>();

	// FUNCTION: ENGINE 0x10615F10
	template struct LeafByte<0x10615F10, 2084>;

	// FUNCTION: ENGINE 0x10615F60
	template struct LeafWord<0x10615F60, 1652>;

	// FUNCTION: ENGINE 0x10615F70
	template struct LeafWord<0x10615F70, 1656>;

	// FUNCTION: ENGINE 0x10616770
	template struct LeafSelfPointer<0x10616770, 256>;

	// FUNCTION: ENGINE 0x10616780
	template struct LeafSelf<0x10616780>;

	// FUNCTION: ENGINE 0x10616790
	template struct LeafWord<0x10616790, 256>;

	// FUNCTION: ENGINE 0x106167A0
	template struct LeafCount<0x106167A0, 16, 0, 4>;

	// FUNCTION: ENGINE 0x106167B0
	template struct LeafArray<0x106167B0, 16>;

	// FUNCTION: ENGINE 0x106167D0
	template struct LeafInlineArray<0x106167D0, 0, 4>;

	// FUNCTION: ENGINE 0x106167F0
	template struct LeafInlineArray<0x106167F0, 0, 4>;

	// FUNCTION: ENGINE 0x10616800
	template struct LeafSelfPointer<0x10616800, 1024>;

	// FUNCTION: ENGINE 0x10616810
	template struct LeafSelf<0x10616810>;

	// FUNCTION: ENGINE 0x10616820
	template struct LeafWord<0x10616820, 1024>;

	// FUNCTION: ENGINE 0x10616830
	template struct LeafInlineIsEmpty<0x10616830, 4, 256>;

	// FUNCTION: ENGINE 0x10616840
	template struct LeafSelf<0x10616840>;

	// FUNCTION: ENGINE 0x10616850
	template struct LeafInlineCount<0x10616850, 8, 32>;

	// FUNCTION: ENGINE 0x106168B0
	template struct LeafSelf<0x106168B0>;

	// FUNCTION: ENGINE 0x106168C0
	template void LeafNothing<0x106168C0>();

	// FUNCTION: ENGINE 0x106168D0
	template struct LeafInlineCount<0x106168D0, 4, 256>;

	// FUNCTION: ENGINE 0x10616980
	template void LeafNothing<0x10616980>();

	// FUNCTION: ENGINE 0x10616990
	template void LeafNothing<0x10616990>();

	// FUNCTION: ENGINE 0x106169A0
	template void LeafNothing<0x106169A0>();

	// FUNCTION: ENGINE 0x106169B0
	template int LeafDereference<0x106169B0>(const int*);

	// FUNCTION: ENGINE 0x106169C0
	template struct LeafPairOfPointers<0x106169C0>;

	// FUNCTION: ENGINE 0x106169E0
	template int LeafZero<0x106169E0>();

	// FUNCTION: ENGINE 0x106169F0
	template int LeafZero<0x106169F0>();

	// FUNCTION: ENGINE 0x10616A00
	template void LeafSwap<0x10616A00>(int*, int*);

	// FUNCTION: ENGINE 0x10616A20
	template int LeafFirstArgument<0x10616A20>(int);

	// FUNCTION: ENGINE 0x10616F80
	template struct LeafZeroThree<0x10616F80>;

	// FUNCTION: ENGINE 0x10617060
	template void LeafNothing<0x10617060>();

	// FUNCTION: ENGINE 0x106170A0
	template void LeafNothing<0x106170A0>();

	// FUNCTION: ENGINE 0x106170B0
	template void LeafNothing<0x106170B0>();

	// FUNCTION: ENGINE 0x106170C0
	template int LeafDereference<0x106170C0>(const int*);

	// FUNCTION: ENGINE 0x106170D0
	template void LeafSwap<0x106170D0>(int*, int*);

	// FUNCTION: ENGINE 0x106184B0
	template struct LeafWord<0x106184B0, 16>;

	// FUNCTION: ENGINE 0x106184C0
	template struct LeafWord<0x106184C0, 60>;

	// FUNCTION: ENGINE 0x10618590
	template void LeafNothing<0x10618590>();

	// FUNCTION: ENGINE 0x106185A0
	template struct LeafZeroTwoIgnoring<0x106185A0>;

	// FUNCTION: ENGINE 0x106185C0
	template struct LeafCount<0x106185C0, 8, 0, 4>;

	// FUNCTION: ENGINE 0x106185D0
	template struct LeafArray<0x106185D0, 8>;

	// FUNCTION: ENGINE 0x106185E0
	template struct LeafArray<0x106185E0, 8>;

	// FUNCTION: ENGINE 0x106185F0
	template struct LeafZeroTwoIgnoring<0x106185F0>;

	// FUNCTION: ENGINE 0x10618610
	template struct LeafWordsEqual<0x10618610, 0, 4>;

	// FUNCTION: ENGINE 0x10618620
	template struct LeafArray<0x10618620, 4>;

	// FUNCTION: ENGINE 0x10618630
	template struct LeafSelfPointer<0x10618630, 32>;

	// FUNCTION: ENGINE 0x10618640
	template struct LeafInlineCount<0x10618640, 4, 8>;

	// FUNCTION: ENGINE 0x10618650
	template struct LeafInlineArray<0x10618650, 0, 4>;

	// FUNCTION: ENGINE 0x10618660
	template struct LeafSelfPointer<0x10618660, 704>;

	// FUNCTION: ENGINE 0x10618670
	template struct LeafInlineCount<0x10618670, 44, 16>;

	// FUNCTION: ENGINE 0x106186E0
	template struct LeafTwoWords<0x106186E0>;

	// FUNCTION: ENGINE 0x106187D0
	template struct LeafSelf<0x106187D0>;

	// FUNCTION: ENGINE 0x106187E0
	template struct LeafWord<0x106187E0, 32>;

	// FUNCTION: ENGINE 0x106187F0
	template void LeafNothing<0x106187F0>();

	// FUNCTION: ENGINE 0x10618860
	template struct LeafCount<0x10618860, 8, 0, 4>;

	// FUNCTION: ENGINE 0x10618870
	template struct LeafArray<0x10618870, 8>;

	// FUNCTION: ENGINE 0x10618880
	template struct LeafArray<0x10618880, 8>;

	// FUNCTION: ENGINE 0x10618D70
	template void LeafNothing<0x10618D70>();

	// FUNCTION: ENGINE 0x10618DA0
	template void LeafNothing<0x10618DA0>();

	// FUNCTION: ENGINE 0x10618FF0
	template void LeafNothing<0x10618FF0>();

	// FUNCTION: ENGINE 0x10619110
	template void LeafNothing<0x10619110>();

	// FUNCTION: ENGINE 0x10619A90
	template struct LeafInitTwo<0x10619A90, 0, 0>;

	// FUNCTION: ENGINE 0x1061B180
	template void LeafNothing<0x1061B180>();

	// FUNCTION: ENGINE 0x1061B1F0
	template struct LeafSelf<0x1061B1F0>;

	// FUNCTION: ENGINE 0x1061B200
	template struct LeafWord<0x1061B200, 0>;

	// FUNCTION: ENGINE 0x1061B450
	template struct LeafByte<0x1061B450, 740>;

	// FUNCTION: ENGINE 0x1061B730
	template struct LeafEqualsWord<0x1061B730>;

	// FUNCTION: ENGINE 0x1061B7A0
	template struct LeafPairOfPointers<0x1061B7A0>;

	// FUNCTION: ENGINE 0x1061B7C0
	template struct LeafTwoWords<0x1061B7C0>;

	// FUNCTION: ENGINE 0x1061B800
	template void LeafNothing<0x1061B800>();

	// FUNCTION: ENGINE 0x1061BF70
	template struct LeafWord<0x1061BF70, 0>;

	// FUNCTION: ENGINE 0x1061BFB0
	template struct LeafWord<0x1061BFB0, 8>;

	// FUNCTION: ENGINE 0x1061BFC0
	template struct LeafWord<0x1061BFC0, 12>;

	// FUNCTION: ENGINE 0x1061C000
	template struct LeafWord<0x1061C000, 28>;

	// FUNCTION: ENGINE 0x1061C3D0
	template struct LeafWord<0x1061C3D0, 20>;

	// FUNCTION: ENGINE 0x1061C3E0
	template struct LeafWord<0x1061C3E0, 24>;

	// FUNCTION: ENGINE 0x1061C3F0
	template struct LeafAddress<0x1061C3F0, 8>;

	// FUNCTION: ENGINE 0x1061C9F0
	template struct LeafWord<0x1061C9F0, 72>;

	// FUNCTION: ENGINE 0x1061DAE0
	template struct LeafSelf<0x1061DAE0>;

	// FUNCTION: ENGINE 0x1061E800
	template void LeafNothing<0x1061E800>();

	// FUNCTION: ENGINE 0x1061ED30
	template struct LeafSelf<0x1061ED30>;

	// FUNCTION: ENGINE 0x1061ED40
	template struct LeafSelf<0x1061ED40>;

	// FUNCTION: ENGINE 0x1061ED50
	template struct LeafInlineArray<0x1061ED50, 0, 4>;

	// FUNCTION: ENGINE 0x1061ED60
	template struct LeafSelf<0x1061ED60>;

	// FUNCTION: ENGINE 0x1061EDF0
	template struct LeafSelf<0x1061EDF0>;

	// FUNCTION: ENGINE 0x1061EE00
	template struct LeafSelf<0x1061EE00>;

	// FUNCTION: ENGINE 0x1061F1B0
	template struct LeafWord<0x1061F1B0, 1856>;

	// FUNCTION: ENGINE 0x1061F290
	template struct LeafWord<0x1061F290, 1636>;

	// FUNCTION: ENGINE 0x1061F2B0
	template struct LeafWord<0x1061F2B0, 12>;

	// FUNCTION: ENGINE 0x1061FF00
	template struct LeafByte<0x1061FF00, 1664>;
}
