#include "code/core/heap.h"
#include "code/core/memory/rangemap.h"

namespace core
{
	// FUNCTION: ENGINE 0x10646140
	RangeMap::RangeMap()
		: pairs(0), count(0), capacity(0)
	{
	}

	// FUNCTION: ENGINE 0x10646150
	RangeMap::~RangeMap()
	{
	}

	// FUNCTION: ENGINE 0x10646160
	unsigned int RangeMap::BufferSize(unsigned int maxRanges)
	{
		return (maxRanges + 1) * 16;
	}

	// FUNCTION: ENGINE 0x10646170
	void RangeMap::Init(int defaultValue, unsigned int maxRanges, Pair* buffer)
	{
		pairs = buffer;
		capacity = maxRanges * 2 + 2;
		pairs[0].address = 0;
		pairs[0].value = defaultValue;
		count = 1;
		this->defaultValue = defaultValue;
	}

	// FUNCTION: ENGINE 0x106461A0
	void RangeMap::Reset()
	{
		pairs = 0;
		count = 0;
		capacity = 0;
	}

	// FUNCTION: ENGINE 0x106461B0
	bool RangeMap::RemoveValue(int value)
	{
		Pair* p = pairs;
		unsigned int n = count;
		unsigned int i = 0;
		while (i < n)
		{
			if (p->value == value)
			{
				break;
			}
			i++;
			p++;
		}
		if (i == n)
		{
			return false;
		}
		Pair* write = p;
		unsigned int j = i + 1;
		p++;
		unsigned int removed = 1;
		if (j < n)
		{
			Pair* previous = write - 1;
			do
			{
				int v = p->value;
				if (v == value)
				{
					p++;
					removed++;
				}
				else
				{
					// A run equal to the one kept before it merges into it (and the very first run is never kept
					// when it is the one being removed)
					if (previous < pairs || previous->value == v)
					{
						removed++;
					}
					else
					{
						write->address = p->address;
						write->value = p->value;
						write++;
						previous++;
					}
					p++;
				}
				j++;
			} while (j < count);
		}
		count -= removed;
		return true;
	}

	// FUNCTION: ENGINE 0x10646250
	bool RangeMap::ReplaceValue(int oldValue, int newValue)
	{
		Pair* p = pairs;
		unsigned int i = 0;
		while (i < count)
		{
			if (p->value == oldValue)
			{
				break;
			}
			i++;
			p++;
		}
		if (i == count)
		{
			return false;
		}
		unsigned int removed = 0;
		Pair* write = p;
		for (; i < count; i++, p++)
		{
			if (p->value == oldValue)
			{
				p->value = newValue;
			}
			Pair* previous = write - 1;
			if (previous < pairs || previous->value == p->value)
			{
				removed++;
				continue;
			}
			if (write != p)
			{
				*write = *p;
			}
			write++;
		}
		count -= removed;
		return true;
	}

	// FUNCTION: ENGINE 0x106462E0
	void RangeMap::Shift(unsigned int index, unsigned int by)
	{
		Pair* source = &pairs[count - 1];
		Pair* destination = source + by;
		unsigned int n = count - index;
		while (n != 0)
		{
			destination->address = source->address;
			destination->value = source->value;
			destination--;
			source--;
			n--;
		}
	}

	// FUNCTION: ENGINE 0x10646310
	unsigned int RangeMap::Find(unsigned int address)
	{
		unsigned int n = count;
		if (n == 1)
		{
			return 0;
		}
		Pair* p = pairs;
		if (p[1].address > address)
		{
			return 0;
		}
		if (p[n - 1].address <= address)
		{
			return n - 1;
		}
		unsigned int low = 1;
		unsigned int high = n - 2;
		while (low <= high)
		{
			// Overflow-free midpoint
			unsigned int middle = (high >> 1) + (low >> 1);
			if ((low & 1) && (high & 1))
			{
				middle++;
			}
			if (p[middle].address > address)
			{
				high = middle - 1;
			}
			else if (p[middle + 1].address > address)
			{
				return middle;
			}
			else
			{
				low = middle + 1;
			}
		}
		return (unsigned int)-1;
	}

	// FUNCTION: ENGINE 0x10646390
	RangeMap* RangeMap::Construct()
	{
		// An explicit constructor call (a Visual C++ extension); the original keeps this in edx across the call,
		// which placement new (with its null test) does not reproduce
		this->RangeMap::RangeMap();
		return this;
	}

	// FUNCTION: ENGINE 0x106463A0
	void RangeMap::Create(int defaultValue, unsigned int maxRanges, int heap)
	{
		Pair* buffer = (Pair*)HeapAlloc(heap, BufferSize(maxRanges));
		this->heap = heap;
		Init(defaultValue, maxRanges, buffer);
	}

	// FUNCTION: ENGINE 0x106463E0
	void RangeMap::Destroy()
	{
		if (pairs != 0)
		{
			HeapFree(heap, pairs);
		}
	}

	// FUNCTION: ENGINE 0x10646550
	int RangeMap::Get(unsigned int address)
	{
		return pairs[Find(address)].value;
	}

	// FUNCTION: ENGINE 0x10646570
	void RangeMap::Free()
	{
		Destroy();
	}

	// FUNCTION: ENGINE 0x10646400
	// EQUIVALENT: every block in the original's order; the original keeps `i` in edi and `end` in ebx (later
	// `value`), ours keeps `i` in ebx and an `i * 8` temporary in edi, reloading `end` and `value` from the
	// stack; the original also repeats the `key == start` test once more before the insert (9 %)
	int RangeMap::Set(unsigned int start, unsigned int end, int value, int* previous)
	{
		unsigned int i = Find(start);
		if (previous != 0)
		{
			*previous = pairs[i].value;
		}
		unsigned int last = count - 1;
		if (i < last && pairs[i + 1].address < end)
		{
			return 2;
		}
		Pair* p = &pairs[i];
		unsigned int key = p->address;
		if (key == start && ((i < last && p[1].address == end) || (i == last && end == 0xFFFFFFFF)))
		{
			return 1;
		}
		if (key == start)
		{
			if (i != 0 && p[-1].value == value)
			{
				// Same value as the run before: that run simply grows over [start, end)
				p->address = end;
				return 0;
			}
			Shift(i, 1);
			pairs[i + 1].address = end;
			pairs[i].address = start;
			pairs[i].value = value;
			count++;
			return 0;
		}
		if (i < last && p[1].address == end)
		{
			if (p[1].value != value)
			{
				Shift(i + 1, 1);
				pairs[i + 1].address = start;
				pairs[i + 1].value = value;
				count++;
				return 0;
			}
			// Same value as the run after: it now begins at start
			p[1].address = start;
			return 0;
		}
		// Splits the run: [key, start) old, [start, end) value, [end, ...) old
		int old = p->value;
		Shift(i, 2);
		pairs[i].address = key;
		pairs[i].value = old;
		pairs[i + 1].address = start;
		pairs[i + 1].value = value;
		pairs[i + 2].address = end;
		pairs[i + 2].value = old;
		count += 2;
		return 0;
	}
}
