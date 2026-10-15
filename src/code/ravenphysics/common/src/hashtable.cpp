#include "code/ravenphysics/common/hashtable.h"

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
}
