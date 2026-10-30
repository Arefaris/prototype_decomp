// The slot hash tables of the broad phase: the engine's copies of the pointer hash table's insert, remove and find (0x10682EC0 -
// 0x106831E0); see chaintable.h. A unit of its own: the engine does not know which registers Unlink keeps.
#include "code/ravenphysics/chaintable.h"

namespace ravenphysics
{
	template <int Function>
	unsigned short SlotHashTable::Insert(unsigned int key)
	{
		unsigned short bucket = ((key >> 3 ^ key) >> 4) % (unsigned short)headCount;
		freeCount--;
		unsigned short slot = freeSlots[freeCount];
		slotBuckets[slot] = bucket;
		unsigned short head = heads[bucket];
		heads[bucket] = slot;
		next[slot] = head;
		keys[slot] = key;
		return slot;
	}

	template <int Function>
	void SlotHashTable::RemoveSlot(unsigned int slot)
	{
		unsigned short index = (unsigned short)slot;
		Unlink(slotBuckets[index], slot);
		slotBuckets[index] = 0xFFFF;
		keys[index] = 0;
		freeCount++;
		unsigned short* entry = freeSlots + freeCount - 1;
		if (entry)
		{
			*entry = (unsigned short)slot;
		}
	}

	template <int Function>
	unsigned short SlotHashTable::Find(unsigned int key)
	{
		unsigned short bucket = ((key >> 3 ^ key) >> 4) % (unsigned short)headCount;
		unsigned short slot = heads[bucket];
		while (slot != 0xFFFF && keys[slot] != key)
		{
			slot = next[slot];
		}
		return slot;
	}

	// FUNCTION: ENGINE 0x10682EC0
	template unsigned short SlotHashTable::Insert<0x10682EC0>(unsigned int);
	// FUNCTION: ENGINE 0x10682F70
	template unsigned short SlotHashTable::Insert<0x10682F70>(unsigned int);
	// FUNCTION: ENGINE 0x10683020
	template unsigned short SlotHashTable::Insert<0x10683020>(unsigned int);
	// FUNCTION: ENGINE 0x10682F20
	template void SlotHashTable::RemoveSlot<0x10682F20>(unsigned int);
	// FUNCTION: ENGINE 0x10683190
	template void SlotHashTable::RemoveSlot<0x10683190>(unsigned int);
	// FUNCTION: ENGINE 0x106831E0
	template void SlotHashTable::RemoveSlot<0x106831E0>(unsigned int);
	// FUNCTION: ENGINE 0x10682FD0
	template unsigned short SlotHashTable::Find<0x10682FD0>(unsigned int);
	// FUNCTION: ENGINE 0x10683080
	template unsigned short SlotHashTable::Find<0x10683080>(unsigned int);
}
