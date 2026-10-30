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
	// The word at Offset set to zero
	template <int Function, int Offset>
	struct LeafClearWord : LeafPadding<Offset>
	{
		void Clear();

		int member;
	};

	// The word at Offset plus one
	template <int Function, int Offset>
	struct LeafWordPlusOne : LeafPadding<Offset>
	{
		int Get() const;

		int member;
	};

	// The bucket of a key in a table of count buckets
	template <int Function>
	struct LeafBucket
	{
		unsigned short Get(unsigned int key) const;

		unsigned char padding[12];
		unsigned short count;
	};

	// Whether the first word equals the word an argument points at
	template <int Function>
	struct LeafEqualsWord
	{
		bool Get(const int* other) const;

		int member;
	};

	// Whether two words of the object equal those of another
	template <int Function>
	struct LeafEqualsPair
	{
		bool Get(const LeafEqualsPair* other) const;

		int first;
		int second;
	};

	// An inline array of elements at Offset
	template <int Function, int Offset, int Size>
	struct LeafInlineArray : LeafPadding<Offset>
	{
		LeafElement<Size>* At(int index);

		LeafElement<Size> items[1];
	};

	// An inline array of words at Offset (indexed from there)
	template <int Function, int Offset>
	struct LeafInlineWord : LeafPadding<Offset>
	{
		int Get(int index) const;

		int items[1];
	};

	// A constructor taking a short, a word and a word
	template <int Function>
	struct LeafInitShortWordWord
	{
		LeafInitShortWordWord(unsigned short newFirst, int newSecond, int newThird);

		int first;
		int second;
		int third;
	};

	// Counts: adds to a short total and bumps a short count
	template <int Function>
	struct LeafAddShort
	{
		void Add(unsigned short value);

		unsigned char padding[6];
		unsigned short count;
		unsigned short total;
	};

	// Two words that stay zero, the constructor taking an argument it does not use
	template <int Function>
	struct LeafZeroTwoIgnoring
	{
		LeafZeroTwoIgnoring(int unused);

		int first;
		int second;
	};

	// A word taken from the argument (a pointer), a zero short
	template <int Function>
	struct LeafInitWordShort
	{
		LeafInitWordShort(int newFirst);

		int first;
		unsigned short second;
	};

	template <int Function>
	struct LeafInitWordShortShort
	{
		LeafInitWordShortShort(int newFirst, unsigned short newThird);

		int first;
		unsigned short second;
		unsigned short pad;
		unsigned short third;
	};

	// Free functions of one or two words
	template <int Function>
	int LeafFirstArgument(int first);

	template <int Function>
	int LeafDereference(const int* pointer);

	template <int Function>
	void LeafSwap(int* first, int* second);

	template <int Function>
	void LeafCopyWord(int* destination, const int* source);

	// The words two pointers point at
	template <int Function>
	struct LeafPairOfPointers
	{
		LeafPairOfPointers(const int* newFirst, const int* newSecond);

		int first;
		int second;
	};

	// A word taken from a pointer, the second from the argument
	template <int Function>
	struct LeafPairPointerWord
	{
		LeafPairPointerWord(const int* newFirst, int newSecond);

		int first;
		int second;
	};

	// Whether the word at Offset is less than the argument's
	template <int Function, int Offset>
	struct LeafLessThan : LeafPadding<Offset>
	{
		int Get(const LeafLessThan* other) const;

		unsigned int member;
	};
	// Whether the count at +4 is zero
	template <int Function>
	struct LeafIsEmpty
	{
		bool Get() const;

		int unknown0;
		int count;
	};

	// A pointer to the object itself at Offset
	template <int Function, int Offset>
	struct LeafSelfPointer : LeafPadding<Offset>
	{
		LeafSelfPointer* Init();

		void* self;
	};

	// The number of elements of an inline array before its end pointer, and whether the end is at the start
	template <int Function, int Size, int Count>
	struct LeafInlineCount
	{
		int Get() const;

		LeafElement<Size> items[Count];
		LeafElement<Size>* end;
	};

	template <int Function, int Size, int Count>
	struct LeafInlineIsEmpty
	{
		bool Get() const;

		LeafElement<Size> items[Count];
		LeafElement<Size>* end;
	};
	// Copies count elements into the array from a block
	template <int Function, int Size>
	struct LeafCopyIn
	{
		void Copy(const void* source);

		void* items;
		int count;
	};

	// Takes the count and the elements of another array
	template <int Function, int Size>
	struct LeafAssign
	{
		void Assign(const LeafAssign* other);

		void* items;
		int count;
	};
}

#endif
