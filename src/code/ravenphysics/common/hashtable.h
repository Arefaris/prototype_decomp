// A fixed-capacity hash table of 32-bit keys with 16-bit slot indices (chained buckets, a free list of slots).
// Name and layout are guesses; the key is hashed by its address bits, so it is used for pointers.
#ifndef RAVENPHYSICS_COMMON_HASHTABLE_H
#define RAVENPHYSICS_COMMON_HASHTABLE_H

#include "code/ravenphysics/common/stackallocator.h"

namespace ravenphysics
{
	class PointerHashTable
	{
	public:
		// The slot of key, 0xFFFF when it is not in the table (0x10686570)
		unsigned short Find(unsigned int key);
		// Empties the table: the chains and the buckets back to 0xFFFF and the free list rebuilt from capacity
		// (0x10658AE0; the code sits in the context unit's range, but the class is this one's)
		void Reset();

		unsigned short* next;
		int unknown4;
		unsigned short* buckets;
		unsigned int bucketCount;
		unsigned short* slotBuckets;
		int unknown14;
		unsigned int* keys;
		int unknown1C;
		unsigned short* freeSlots;
		unsigned int freeCount;
		// How many slots the table was built with: the free list is this long after a reset (name guess)
		unsigned int capacity;
	};

	// A set of 32-bit keys that hands out a 16-bit slot per distinct key: the slots are chained per bucket, and the
	// keys are also kept in the order they were first added. Everything is allocated from the scratch stack in one go
	// when the table is built, so it cannot grow. The manager keeps the physics objects' ids in one; the name and the
	// members are guesses (no RTTI).
	class KeyTable
	{
	public:
		// 0x106883B0: splits the scratch stack between the chains and the buckets and marks every slot free
		void Init(unsigned short slots, unsigned short buckets, ScratchStack* stack);
		// 0x107E7120: the chains, the buckets, the keys and the order list all hold count entries
		void Create(unsigned int count, ScratchStack* stack);
		// The slot of key, or 0xFFFF when the key is not in the table (0x107E6BC0)
		unsigned short Find(unsigned int key) const;
		// The first slot from slot on that holds key, or 0xFFFF (0x107E5AB0)
		unsigned short FindFrom(unsigned short slot, unsigned int key) const;
		// The same from the slot after the one given (0x107E6C00)
		unsigned short FindAfter(unsigned short slot, unsigned int key) const;
		// Adds key when it is not in the table yet and gives it the next slot (0x107E6C40)
		void Insert(unsigned int key);

		unsigned short* next;          // +0x00, one chain link per slot
		unsigned int slotCount;        // +0x04
		unsigned short* buckets;       // +0x08, the first slot of each bucket's chain
		unsigned int bucketCount;      // +0x0C
		unsigned int* keys;            // +0x10, the key of every slot
		unsigned int count;            // +0x14
		unsigned int capacity;         // +0x18
		unsigned int* order;           // +0x1C, the keys in the order they were added
		unsigned int orderCount;       // +0x20
		unsigned int orderCapacity;    // +0x24
	};
}

#endif
