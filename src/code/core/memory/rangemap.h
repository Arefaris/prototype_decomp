// A map from address ranges to heap indices (class, member and file names guessed; the unit is
// 0x10646140 - 0x1064654A). The pairs are sorted by address; each marks where a run begins and which value
// (heap index) applies from there on, the first pair starting at 0 with the default value. The memory system
// registers a heap's regions with Set (0x1063AE10) and answers "which heap owns this address" through Find.
// Placed under memory/ because of that use; the original's sub-directory for this file is not known.
#ifndef CORE_MEMORY_RANGEMAP_H
#define CORE_MEMORY_RANGEMAP_H

namespace core
{
	class RangeMap
	{
	public:
		struct Pair
		{
			unsigned int address;
			int value;
		};

		RangeMap();
		// Re-runs the constructor on this and returns this
		RangeMap* Construct();
		void Reset();
		// Bytes needed for maxRanges ranges (two pairs each, plus the first)
		unsigned int BufferSize(unsigned int maxRanges);
		void Init(int defaultValue, unsigned int maxRanges, Pair* buffer);
		// Allocates the buffer from heap and initialises
		void Create(int defaultValue, unsigned int maxRanges, int heap);
		void Destroy();
		// Drops every run with this value (neighbours with equal values merge); false when there is none
		bool RemoveValue(int value);
		bool ReplaceValue(int oldValue, int newValue);
		// Moves the pairs from index on up by `by` slots
		void Shift(unsigned int index, unsigned int by);
		// Index of the run containing address (-1 when the search fails)
		unsigned int Find(unsigned int address);
		// Marks [start, end) with value; *previous receives the value found at start. Returns 0 when done,
		// 1 when the run was already exactly this, 2 when the range crosses an existing boundary
		int Set(unsigned int start, unsigned int end, int value, int* previous);

		Pair* pairs;
		unsigned int count;
		unsigned int capacity;
		int defaultValue;
		int heap;
	};
}

#endif
