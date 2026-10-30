// Small helpers of the broad phase's tables that the engine keeps out of line: a run of elements taken from the heap in
// 128-byte blocks, the aligned allocation behind it, bit sets of one bit per slot and swaps of small records. The units carry
// no assert, so the names are stand-ins named after what the functions do.
#ifndef RAVENPHYSICS_ALIGNEDRUNS_H
#define RAVENPHYSICS_ALIGNEDRUNS_H

namespace ravenphysics
{
	// A block of 128-byte units from the heap; the parameter names the engine function that carries the code
	template <int Function>
	void* AllocateAligned128(unsigned int size);

	// The same as a method that does not use its object (0x10681F30)
	struct Aligned128Source
	{
		void* Allocate(unsigned int size);
	};

	// A run of count elements in one block of 128-byte units: begin and end, both zero when the heap has no room
	template <class T>
	struct ElementRun
	{
		// Takes the block; false when there is none
		bool Reserve(unsigned int count);

		T* begin;
		T* end;
	};

	struct Element4
	{
		int word;
	};

	struct Element12
	{
		int words[3];
	};

	struct Element24
	{
		int words[6];
	};

	// One bit per slot (0x10682220 answers whether a bit is set; 0x10681F60 / 0x10681F90 raise and clear one; 0x10681FC0
	// sets it to a value)
	struct BitSetHolder
	{
		unsigned char* bits;
	};

	bool TestBit(const BitSetHolder* holder, unsigned short index);
	void SetBit(unsigned char* bits, unsigned int index);
	void ClearBit(unsigned char* bits, unsigned int index);
	void AssignBit(unsigned char* bits, unsigned short index, bool value);

	// Exchanges two records (0x10682250 / 0x10682270)
	void SwapWords(int* first, int* second);
	void SwapTriples(Element12* first, Element12* second);
}

#endif
