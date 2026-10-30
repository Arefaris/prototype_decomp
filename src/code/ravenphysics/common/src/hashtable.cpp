#include "code/core/heap.h"
#include "code/ravenphysics/common/hashtable.h"
#include "code/ravenphysics/context.h"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x10686570
	unsigned short PointerHashTable::Find(unsigned int key)
	{
		// The bucket count is read back as a 16-bit value: the engine's modulo is a 32-bit divide by a zero-extended
		// word, which is what the cast of the 32-bit member compiles to.
		unsigned short bucket = ((key >> 3 ^ key) >> 4) % (unsigned short)bucketCount;
		unsigned short slot = buckets[bucket];
		while (slot != 0xffff && keys[slot] != key)
		{
			slot = next[slot];
		}
		return slot;
	}

	// FUNCTION: ENGINE 0x10686390
	void PointerHashTable::Release(EmptyArgument& unused)
	{
		if (slotBuckets)
		{
			core::FreeAligned(slotBuckets);
			slotBuckets = 0;
			unknown14 = 0;
		}
		if (next)
		{
			core::FreeAligned(next);
			next = 0;
			unknown4 = 0;
		}
		if (buckets)
		{
			core::FreeAligned(buckets);
			buckets = 0;
			bucketCount = 0;
		}
		if (keys)
		{
			core::FreeAligned(keys);
			keys = 0;
			unknown1C = 0;
		}
		if (freeSlots)
		{
			core::FreeAligned(freeSlots);
			freeSlots = 0;
			freeCount = 0;
			capacity = 0;
		}
	}

	// FUNCTION: ENGINE 0x10686410
	void ObjectRegistry::Release()
	{
		EmptyArgument nothing;
		if (slotBuckets)
		{
			core::FreeAligned(slotBuckets);
			slotBuckets = 0;
			slotBucketCount = 0;
		}
		if (next)
		{
			core::FreeAligned(next);
			next = 0;
			nextCount = 0;
		}
		if (buckets)
		{
			core::FreeAligned(buckets);
			buckets = 0;
			bucketCount = 0;
		}
		table.Release(nothing);
	}

	// FUNCTION: ENGINE 0x10686510
	unsigned short PointerHashTable::Insert(unsigned int key)
	{
		unsigned short bucket = ((key >> 3 ^ key) >> 4) % (unsigned short)bucketCount;
		freeCount--;
		unsigned short slot = freeSlots[freeCount];
		slotBuckets[slot] = bucket;
		unsigned short head = buckets[bucket];
		buckets[bucket] = slot;
		next[slot] = head;
		keys[slot] = key;
		return slot;
	}
}
