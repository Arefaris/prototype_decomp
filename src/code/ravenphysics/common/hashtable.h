// A fixed-capacity hash table of 32-bit keys with 16-bit slot indices (chained buckets, a free list of slots).
// Name and layout are guesses; the key is hashed by its address bits, so it is used for pointers.
#ifndef RAVENPHYSICS_COMMON_HASHTABLE_H
#define RAVENPHYSICS_COMMON_HASHTABLE_H

namespace ravenphysics
{
	class PointerHashTable
	{
	public:
		// The slot of key, 0xFFFF when it is not in the table (0x10686570)
		unsigned short Find(unsigned int key);

		unsigned short* next;
		int unknown4;
		unsigned short* buckets;
		unsigned short bucketCount;
		unsigned short* slotBuckets;
		int unknown14;
		unsigned int* keys;
		int unknown1C;
		unsigned short* freeSlots;
		int freeCount;
	};
}

#endif
