// Tables of slots chained in buckets by 16-bit links (the broad phase's lookup tables). The unit carries no assert and no
// RTTI, so every class here is a stand-in named after what its functions do and every member is a guess: ChainLinks is the
// part all of them share (the link of each slot and the first slot of each bucket); the variants add the bucket each slot
// is filed in (one byte or one word per slot) and, for the counted ones, how many slots each bucket holds.
#ifndef RAVENPHYSICS_CHAINTABLE_H
#define RAVENPHYSICS_CHAINTABLE_H

namespace ravenphysics
{
	class ChainLinks
	{
	public:
		// Takes the slots' links and the buckets' heads from the heap, all set to 0xFFFF (0x10682BC0; the third
		// argument is not used)
		void Create(unsigned short slotCount, int bucketCount, int unused);
		// Gives both blocks back (0x10682C30)
		void Release(int unused);
		// Takes a slot out of the chain of its bucket and clears its link (0x106822D0)
		void Unlink(unsigned int bucket, unsigned short slot);

		unsigned short* next;         // 0x00
		int nextCount;                // 0x04
		unsigned short* heads;        // 0x08
		int headCount;                // 0x0C
	};

	// A table that keeps the bucket of every slot in a byte
	class ByteChainTable : public ChainLinks
	{
	public:
		// Takes a slot out of its bucket and returns the bucket it was in (0x10682340)
		unsigned char Release(unsigned short slot);
		// Files a slot at the head of a bucket (0x10682370)
		void Link(unsigned char bucket, unsigned short slot);

		unsigned char* slotBuckets;   // 0x10
		int slotBucketCount;          // 0x14
	};

	// The same with the number of slots of each bucket
	class CountedByteChainTable : public ByteChainTable
	{
	public:
		// 0x106826B0 / 0x106826F0 (the last one answers the address of the bucket's count)
		unsigned char Release(unsigned short slot);
		unsigned short* Link(unsigned char bucket, unsigned short slot);

		unsigned short* counts;       // 0x18
		int countCount;               // 0x1C
	};

	// A table that keeps the bucket of every slot in a word
	class WordChainTable : public ChainLinks
	{
	public:
		// 0x10682730 / 0x10682770: as the byte table's
		unsigned short Release(unsigned short slot);
		void Link(unsigned short bucket, unsigned short slot);
		// Empties a bucket: every slot of its chain loses its link and its bucket (0x10682B60)
		void FreeBucket(unsigned short bucket);

		unsigned short* slotBuckets;  // 0x10
		int slotBucketCount;          // 0x14
	};

	class CountedWordChainTable : public WordChainTable
	{
	public:
		// 0x106827B0: the address of the bucket's count
		unsigned short* Link(unsigned short bucket, unsigned short slot);
		// Empties a bucket and its count (0x10683230)
		void ClearBucket(unsigned short bucket);

		unsigned short* counts;       // 0x18
		int countCount;               // 0x1C
	};

	// A set of 32-bit keys with a slot each, filed in the buckets of a word table (the broad phase keeps several; the
	// functions are the same code under different template instances, so the parameter names the engine function)
	class SlotHashTable : public WordChainTable
	{
	public:
		// Files a key under the next free slot and returns the slot (the code of PointerHashTable::Insert)
		template <int Function>
		unsigned short Insert(unsigned int key);
		// Takes a slot out of its bucket and onto the free list again
		template <int Function>
		void RemoveSlot(unsigned int slot);
		// The slot of a key, 0xFFFF when it is not in the table
		template <int Function>
		unsigned short Find(unsigned int key);

		unsigned int* keys;           // 0x18
		int keyCount;                 // 0x1C
		unsigned short* freeSlots;    // 0x20
		unsigned int freeCount;       // 0x24
		unsigned int capacity;        // 0x28
	};
}

#endif
