#include "code/ravenphysics/common/hashtable.h"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x10686570
	unsigned short PointerHashTable::Find(unsigned int key)
	{
		unsigned short bucket = ((key >> 3 ^ key) >> 4) % bucketCount;
		unsigned short slot = buckets[bucket];
		while (slot != 0xffff && keys[slot] != key)
		{
			slot = next[slot];
		}
		return slot;
	}
}
