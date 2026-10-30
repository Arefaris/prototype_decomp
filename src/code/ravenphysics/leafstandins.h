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
}

#endif
