// The chained slot tables of the broad phase (0x106822D0 - 0x10683240); see chaintable.h.
#include <string.h>
#include "code/core/heap.h"
#include "code/ravenphysics/chaintable.h"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x106822D0
	// EQUIVALENT: the same walk of the chain and the same stores; the registers and the order of the loads differ, 33.6 %
	void ChainLinks::Unlink(unsigned int bucket, unsigned short slot)
	{
		unsigned short* head = &heads[bucket];
		unsigned short current = *head;
		if (current == slot)
		{
			*head = next[current];
			next[current] = 0xFFFF;
			return;
		}
		unsigned short previous = current;
		current = next[current];
		while (current != slot)
		{
			previous = current;
			current = next[current];
		}
		next[previous] = next[current];
		next[current] = 0xFFFF;
	}

	// FUNCTION: ENGINE 0x106822A0
	void ChainLinks::PushFront(int bucket, unsigned short slot)
	{
		unsigned short* head = &heads[bucket];
		unsigned short first = *head;
		*head = slot;
		next[slot] = first;
	}

	// FUNCTION: ENGINE 0x10682340
	unsigned char ByteChainTable::Release(unsigned short slot)
	{
		unsigned char bucket = slotBuckets[slot];
		Unlink(bucket, slot);
		slotBuckets[slot] = 0xFF;
		return bucket;
	}

	// FUNCTION: ENGINE 0x10682370
	void ByteChainTable::Link(unsigned char bucket, unsigned short slot)
	{
		slotBuckets[slot] = bucket;
		unsigned short* head = &heads[bucket];
		unsigned short first = *head;
		*head = slot;
		next[slot] = first;
	}

	// FUNCTION: ENGINE 0x106826B0
	unsigned char CountedByteChainTable::Release(unsigned short slot)
	{
		unsigned char bucket = slotBuckets[slot];
		Unlink(bucket, slot);
		slotBuckets[slot] = 0xFF;
		counts[bucket]--;
		return bucket;
	}

	// FUNCTION: ENGINE 0x106826F0
	// EQUIVALENT: the same stores in the same order; ours doubles the bucket once for every address, the engine scales it in each, 23.3 %
	unsigned short* CountedByteChainTable::Link(unsigned char bucket, unsigned short slot)
	{
		slotBuckets[slot] = bucket;
		unsigned short* head = &heads[bucket];
		unsigned short first = *head;
		*head = slot;
		next[slot] = first;
		unsigned short* count = &counts[bucket];
		++*count;
		return count;
	}

	// FUNCTION: ENGINE 0x10682730
	unsigned short WordChainTable::Release(unsigned short slot)
	{
		unsigned short bucket = slotBuckets[slot];
		Unlink(bucket, slot);
		slotBuckets[slot] = 0xFFFF;
		return bucket;
	}

	// FUNCTION: ENGINE 0x10682770
	void WordChainTable::Link(unsigned short bucket, unsigned short slot)
	{
		slotBuckets[slot] = bucket;
		unsigned short* head = &heads[bucket];
		unsigned short first = *head;
		*head = slot;
		next[slot] = first;
	}

	// FUNCTION: ENGINE 0x106827B0
	// EQUIVALENT: the same stores in the same order; ours doubles the bucket once for every address, the engine scales it in each, 44.9 %
	unsigned short* CountedWordChainTable::Link(unsigned short bucket, unsigned short slot)
	{
		slotBuckets[slot] = bucket;
		unsigned short* head = &heads[bucket];
		unsigned short first = *head;
		*head = slot;
		next[slot] = first;
		counts[bucket]++;
		return &counts[bucket];
	}

	// FUNCTION: ENGINE 0x10682B60
	void WordChainTable::FreeBucket(unsigned short bucket)
	{
		unsigned short current = heads[bucket];
		if (current != 0xFFFF)
		{
			unsigned short following;
			do
			{
				following = next[current];
				next[current] = 0xFFFF;
				slotBuckets[current] = 0xFFFF;
				current = following;
			}
			while (following != 0xFFFF);
		}
		heads[bucket] = 0xFFFF;
	}

	// FUNCTION: ENGINE 0x10682BC0
	// EQUIVALENT: the same calls and stores in the same order; ours keeps the bucket count in another register from the start, 25.5 %
	void ChainLinks::Create(unsigned short slotCount, int bucketCount, int unused)
	{
		next = (unsigned short*)core::HeapAllocAligned(core::GetCurrentHeap(), slotCount * 2, 16);
		nextCount = slotCount;
		heads = (unsigned short*)core::HeapAllocAligned(core::GetCurrentHeap(), bucketCount * 2, 16);
		headCount = bucketCount;
		memset(heads, 0xFF, bucketCount * 2);
		memset(next, 0xFF, nextCount * 2);
	}

	// FUNCTION: ENGINE 0x10682C30
	void ChainLinks::Release(int unused)
	{
		if (next)
		{
			core::FreeAligned(next);
			next = 0;
			nextCount = 0;
		}
		if (heads)
		{
			core::FreeAligned(heads);
			heads = 0;
			headCount = 0;
		}
	}
}
