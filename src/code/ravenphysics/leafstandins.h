// Stand-ins for the tiny leaf functions of 0x106A0000 - 0x106C0000: bare accessors, element addressing, word
// initialisers and empty functions the engine keeps out of line. The image names no owner for them, so every stand-in
// is a template whose first parameter is the address of the engine function and whose members are guesses; a unit
// that recovers the real classes should move the functions onto them.
#ifndef RAVENPHYSICS_LEAFSTANDINS_H
#define RAVENPHYSICS_LEAFSTANDINS_H

namespace ravenphysics
{
	class StackAllocator;

	// Bytes in front of the member a stand-in reads or writes
	template <int Offset>
	struct LeafPadding
	{
		char padding[Offset];
	};

	template <>
	struct LeafPadding<0>
	{
	};

	// An element of the given size
	template <int Size>
	struct LeafElement
	{
		char bytes[Size];
	};

	// An element type of its own per engine function, for the scratch allocators' array functions
	template <int Function, int Size>
	struct LeafSized
	{
		char bytes[Size];
	};

	// The address of the member at Offset
	template <int Function, int Offset>
	struct LeafAddress : LeafPadding<Offset>
	{
		char* Get();

		char member;
	};

	// The word at Offset
	template <int Function, int Offset>
	struct LeafWord : LeafPadding<Offset>
	{
		int Get() const;

		int member;
	};

	template <int Function, int Offset>
	struct LeafHalf : LeafPadding<Offset>
	{
		unsigned short Get() const;

		unsigned short member;
	};

	template <int Function, int Offset>
	struct LeafSignedHalf : LeafPadding<Offset>
	{
		int Get() const;

		short member;
	};

	template <int Function, int Offset>
	struct LeafUnsignedHalf : LeafPadding<Offset>
	{
		int Get() const;

		unsigned short member;
	};

	template <int Function, int Offset>
	struct LeafByte : LeafPadding<Offset>
	{
		unsigned char Get() const;

		unsigned char member;
	};

	template <int Function, int Offset>
	struct LeafFloat : LeafPadding<Offset>
	{
		float Get() const;

		float member;
	};

	template <int Function>
	struct LeafSelf
	{
		LeafSelf* Get();
	};

	template <int Function>
	void LeafNothing();

	template <int Function>
	int LeafZero();

	template <int Function>
	bool LeafFalse();

	// The second argument of a function of two
	template <int Function>
	int LeafSecondArgument(int first, int second);

	// The element of an array pointer at index
	template <int Function, int Size>
	struct LeafArray
	{
		LeafElement<Size>* At(int index);

		LeafElement<Size>* items;
	};

	// The word at Offset set from the argument
	template <int Function, int Offset>
	struct LeafSetWord : LeafPadding<Offset>
	{
		void Set(int newValue);

		int member;
	};

	// Two words set to constants
	template <int Function, int First, int Second>
	struct LeafInitTwo
	{
		LeafInitTwo();

		int first;
		int second;
	};

	// Three zero words
	template <int Function>
	struct LeafZeroThree
	{
		LeafZeroThree();

		int first;
		int second;
		int third;
	};

	// Two words taken from the arguments
	template <int Function>
	struct LeafTwoWords
	{
		LeafTwoWords(int newFirst, int newSecond);

		int first;
		int second;
	};

	// Two words set from the arguments
	template <int Function>
	struct LeafSetTwoWords
	{
		void Set(int newFirst, int newSecond);

		int first;
		int second;
	};

	// Reference counter: increment and decrement (interlocked)
	template <int Function>
	struct LeafIncrement
	{
		long Get();

		long member;
	};

	template <int Function>
	struct LeafDecrement
	{
		long Get();

		long member;
	};

	// A byte split around one bit
	template <int Bit>
	struct LeafBitField
	{
		unsigned char before : Bit;
		unsigned char flag : 1;
		unsigned char after : 7 - Bit;
	};

	template <>
	struct LeafBitField<0>
	{
		unsigned char flag : 1;
		unsigned char after : 7;
	};

	template <int Bit>
	struct LeafSignedBitField
	{
		char before : Bit;
		char flag : 1;
		char after : 7 - Bit;
	};

	template <>
	struct LeafSignedBitField<0>
	{
		char flag : 1;
		char after : 7;
	};

	// A bit of the byte at Offset
	template <int Function, int Offset, int Bit>
	struct LeafBit : LeafPadding<Offset>
	{
		bool Get() const;

		LeafBitField<Bit> member;
	};

	// A one-bit signed field
	template <int Function, int Offset, int Bit>
	struct LeafSignedBit : LeafPadding<Offset>
	{
		char Get() const;

		LeafSignedBitField<Bit> member;
	};

	// The element of a short array at the short index; the array pointer at Offset
	template <int Function, int Offset>
	struct LeafHalfIndexed : LeafPadding<Offset>
	{
		unsigned short At(unsigned short index) const;

		unsigned short* items;
	};

	// An array of Size bytes per element from a scratch allocator: pointer and count
	template <int Function, int Size>
	struct LeafCreate
	{
		void Create(int count, StackAllocator* stack);

		void* items;
		int count;
	};

	// The same with a capacity behind an empty count
	template <int Function, int Size>
	struct LeafCreateCapacity
	{
		void Create(int newCapacity, StackAllocator* stack);

		void* items;
		int count;
		int capacity;
	};

	// The next element of a counted array
	template <int Function, int Size>
	struct LeafNext
	{
		LeafElement<Size>* Next();

		LeafElement<Size>* items;
		int count;
	};

	// Appends a copy of an element to a counted array
	template <int Function, int Size>
	struct LeafPush
	{
		void Push(const LeafElement<Size>* value);

		LeafElement<Size>* items;
		int count;
	};

	// Three words: the first from the first argument, the second zero, the third from the second argument
	template <int Function>
	struct LeafInitThree
	{
		LeafInitThree(int newFirst, int newThird);

		int first;
		int second;
		int third;
	};

	// Three words: zero, zero and the argument
	template <int Function>
	struct LeafInitThreeLast
	{
		LeafInitThreeLast(int newThird);

		int first;
		int second;
		int third;
	};

	// Three zero words and a fourth from the argument
	template <int Function>
	struct LeafInitFour
	{
		LeafInitFour(int newFourth);

		int first;
		int second;
		int third;
		int fourth;
	};
	// A stack-allocated array that rounds its byte size up to 16: pointer, count, capacity and the allocator
	template <int Function, int Size>
	struct LeafCreateStacked
	{
		void Create(int newCapacity);

		void* items;
		int count;
		int capacity;
		StackAllocator* stack;
	};

	// The end of, and the last element of, a counted array
	template <int Function, int Size>
	struct LeafEnd
	{
		LeafElement<Size>* End();

		LeafElement<Size>* items;
		int count;
	};

	template <int Function, int Size>
	struct LeafLast
	{
		LeafElement<Size>* Last();

		LeafElement<Size>* items;
		int count;
	};

	// Whether two words of the object are equal
	template <int Function, int First, int Second>
	struct LeafWordsEqual
	{
		bool Get() const;

		int words[Second / 4 + 1];
	};

	// The number of elements between two pointers of the object
	template <int Function, int Size, int Begin, int End>
	struct LeafCount
	{
		int Get() const;

		LeafElement<Size>* pointers[End / 4 + 1];
	};

	// The array helper's size and element functions over a begin / end pair
	template <int Function, int Size>
	struct LeafHelperSize
	{
		int Get(LeafHelperSize* array);

		LeafElement<Size>* begin;
		LeafElement<Size>* end;
	};

	template <int Function, int Size>
	struct LeafHelperGet
	{
		LeafElement<Size>* Get(LeafHelperGet* array, int index);

		LeafElement<Size>* begin;
		LeafElement<Size>* end;
	};
}

#endif
