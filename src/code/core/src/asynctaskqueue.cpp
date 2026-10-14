#include <string.h>

#include "code/core/asynctask.h"
#include "code/core/criticalsection.h"

extern "C"
{
	long _InterlockedAnd(long volatile*, long);
	long _InterlockedCompareExchange(long volatile*, long, long);
	__int64 _InterlockedCompareExchange64(__int64 volatile*, __int64, __int64);
}
#pragma intrinsic(_InterlockedAnd, _InterlockedCompareExchange, _InterlockedCompareExchange64)

namespace core
{
	// The result of marking slots in one bitmap word: the new head position in the word (58: the run of marked
	// slots reaches the end of the word) and whether the head moved
	struct SlotMark
	{
		unsigned int position : 31;
		bool moved : 1;
	};

	inline unsigned __int64 AtomicRead64(unsigned __int64 volatile* value)
	{
		return _InterlockedCompareExchange64((__int64 volatile*)value, 0, 0);
	}

	inline unsigned __int64 AtomicCompareExchange64(unsigned __int64 volatile* value, unsigned __int64 exchange,
		unsigned __int64 comparand)
	{
		return _InterlockedCompareExchange64((__int64 volatile*)value, exchange, comparand);
	}

	// FUNCTION: ENGINE 0x10B81CE0
	// EQUIVALENT: the original tests the low and the high word of each masked value separately (a temporary in memory,
	// as from a two-word helper type); every u64 form tried merges them with `or`
	// The number of leading zero bits (64 for zero)
	static unsigned int CountLeadingZeros64(unsigned __int64 value)
	{
		unsigned int count = 64;
		if (value == 0)
		{
			return count;
		}
		if (value & 0xFFFFFFFF00000000)
		{
			value >>= 32;
			count -= 32;
		}
		if (value & 0xFFFF0000)
		{
			value >>= 16;
			count -= 16;
		}
		if (value & 0xFF00)
		{
			value >>= 8;
			count -= 8;
		}
		if (value & 0xF0)
		{
			value >>= 4;
			count -= 4;
		}
		if (value & 0xC)
		{
			value >>= 2;
			count -= 2;
		}
		if (value & 2)
		{
			count -= 1;
		}
		return count - 1;
	}

	// FUNCTION: ENGINE 0x10B81DB0
	// EQUIVALENT: the original branches for the minimum (first in ebx, count in edi); every one-sided form becomes
	// a cmovae and the two-sided ones and an inline Min add a register copy or swap the register arguments
	// Copies tasks into the ring at `start` (the compiler passes start in eax and count in ecx)
	static void CopyToRing(unsigned int start, unsigned int count, AsyncTaskQueue* queue, const AsyncTask* tasks)
	{
		unsigned int first = 1024 - start;
		if (first >= count)
		{
			first = count;
		}
		memcpy(&queue->tasks[start], tasks, first * sizeof(AsyncTask));
		count -= first;
		if (count != 0)
		{
			memcpy(queue->tasks, tasks + first, count * sizeof(AsyncTask));
		}
	}

	// FUNCTION: ENGINE 0x10B81E10
	// EQUIVALENT: as CopyToRing
	// Copies tasks out of the ring from `start` (the compiler passes start in eax and count in ecx)
	static void CopyFromRing(unsigned int start, unsigned int count, AsyncTaskQueue* queue, AsyncTask* tasks)
	{
		unsigned int first = 1024 - start;
		if (first >= count)
		{
			first = count;
		}
		memcpy(tasks, &queue->tasks[start], first * sizeof(AsyncTask));
		count -= first;
		if (count != 0)
		{
			memcpy(tasks + first, queue->tasks, count * sizeof(AsyncTask));
		}
	}

	// FUNCTION: ENGINE 0x10B81E70
	// The head starts at the first slot of the first word (the compiler passes the words in eax)
	static void InitSlotWords(unsigned __int64* words)
	{
		unsigned __int64* word = &words[1];
		words[0] = 0;
		*word = 58;
		// Spreads the second word over the rest (an overlapping forward copy)
		memcpy(word + 1, word, 16 * sizeof(*word));
	}

	// FUNCTION: ENGINE 0x10B81EA0
	// EQUIVALENT: same operations; the original lays out the moving branch first and keeps the position in memory
	// (the inverted conditions compile the same here)
	// Marks `count` slots from bit `start` of one word (bits count from the top); when the head sits at `start`
	// (or `restart` is set) the head moves past the run of marked slots and those marks are cleared (the compiler
	// passes count in ecx)
	static SlotMark MarkSlots(unsigned __int64* word, unsigned int start, unsigned int count,
		unsigned int limit, bool restart)
	{
		unsigned __int64 range = (((unsigned __int64)1 << count) - 1) << (64 - start - count);
		unsigned __int64 above = ~(((unsigned __int64)1 << (64 - start - count)) - 1);
		bool moved = false;
		unsigned int position = 58;
		unsigned __int64 seen = AtomicRead64(word);
		unsigned __int64 expected = ~seen;
		while (expected != seen)
		{
			unsigned int head = (unsigned int)seen & 0x3F;
			unsigned __int64 bits = seen & ~(unsigned __int64)0x3F;
			moved = false;
			if (restart || head == start)
			{
				unsigned int run = CountLeadingZeros64(~(bits | above)) - start;
				head = run + start;
				if (head >= limit)
				{
					head = 58;
				}
				bits &= ~((((unsigned __int64)1 << run) - 1) << (64 - run - start));
				moved = true;
			}
			else
			{
				bits |= range;
			}
			position = head;
			expected = seen;
			seen = AtomicCompareExchange64(word, bits | head, expected);
		}
		SlotMark mark;
		mark.position = position;
		mark.moved = moved;
		return mark;
	}

	// FUNCTION: ENGINE 0x10B82030
	// EQUIVALENT: same operations; the original keeps `restart` in al (saving the mark in ebp) and `start` in its
	// argument slot, ours cl and ebp
	// Marks `count` slots from `start` in a bitmap; the number of slots the head moved past
	static unsigned int MarkSlotRange(unsigned __int64* words, unsigned int start, unsigned int count)
	{
		unsigned int moved = 0;
		bool restart = false;
		while (count > 0 || restart)
		{
			unsigned int bit = start % 58;
			unsigned int index = start / 58;
			unsigned int limit = 58;
			if (index == 17)
			{
				limit = 38;
			}
			unsigned int marked = count;
			if (bit + marked > limit)
			{
				marked = limit - bit;
			}
			SlotMark mark = MarkSlots(&words[index], bit, marked, limit, restart);
			restart = false;
			if (mark.moved)
			{
				marked = mark.position;
				if (marked == 58)
				{
					marked = limit - bit;
					restart = true;
				}
				else
				{
					marked -= bit;
				}
				moved += marked;
			}
			start = (start + marked) & 0x3FF;
			if (marked >= count)
			{
				count = 0;
			}
			else
			{
				count -= marked;
			}
		}
		return moved;
	}

	// FUNCTION: ENGINE 0x10B82110
	void InitAsyncTaskQueue(AsyncTaskQueue* queue)
	{
		InitSlotWords(queue->freeSlots);
		queue->readState = 0;
		InitSlotWords(queue->usedSlots);
		queue->writeIndex = 0;
		queue->space = 1024;
		SemaphoreCreate(&queue->spaceSemaphore, 0);
		SemaphoreCreate(&queue->taskSemaphore, 0);
		SemaphoreCreate(&queue->overflowSemaphore, 0);
	}

	// FUNCTION: ENGINE 0x10B82180
	void DestroyAsyncTaskQueue(AsyncTaskQueue* queue)
	{
		SemaphoreDestroy(&queue->spaceSemaphore);
		SemaphoreDestroy(&queue->taskSemaphore);
		SemaphoreDestroy(&queue->overflowSemaphore);
	}

	// FUNCTION: ENGINE 0x10B821B0
	// EQUIVALENT: same operations and branches; register allocation differs from the reservation loop on (the
	// original keeps the queue in edi throughout and has one more stack slot)
	// Pushes tasks (chains of them: bits 1 - 7 of a chain head's flags count the tasks that follow it), waiting
	// while the ring has no room
	void PushAsyncTasks(AsyncTaskQueue* queue, AsyncTask* tasks, unsigned int count)
	{
		for (unsigned int i = 0; i < count; i++)
		{
			AsyncTask* task = &tasks[i];
			unsigned int length = task->flags >> 1;
			task->flags |= 1;
			task->index = (unsigned char)length;
			for (int left = length - 1; left >= 0; left--)
			{
				i++;
				task++;
				task->flags &= ~1;
				task->index = (unsigned char)left;
			}
		}
		// Reserve room
		for (;;)
		{
			bool wait = false;
			int free = 0;
			unsigned __int64 seen = AtomicRead64(&queue->space);
			unsigned __int64 expected = ~seen;
			while (expected != seen)
			{
				free = (int)seen;
				unsigned int waiting = (unsigned int)(seen >> 32);
				if (free < 0)
				{
					waiting++;
					wait = true;
				}
				else
				{
					free -= count;
					wait = false;
				}
				expected = seen;
				seen = AtomicCompareExchange64(&queue->space, ((unsigned __int64)waiting << 32) | (unsigned int)free,
					expected);
			}
			if (wait)
			{
				SemaphoreWait(&queue->spaceSemaphore);
				continue;
			}
			if (free < 0)
			{
				SemaphoreWait(&queue->overflowSemaphore);
			}
			break;
		}
		// Take the slots
		unsigned int start = 0;
		long index = _InterlockedAnd(&queue->writeIndex, -1);
		long expectedIndex = ~index;
		while (expectedIndex != index)
		{
			start = index;
			expectedIndex = index;
			index = _InterlockedCompareExchange(&queue->writeIndex, (index + count) & 0x3FF, expectedIndex);
		}
		CopyToRing(start, count, queue, tasks);
		unsigned int ready = MarkSlotRange(queue->usedSlots, start, count);
		if (ready > 0)
		{
			unsigned int waiting = 0;
			unsigned int left;
			unsigned __int64 seen = AtomicRead64(&queue->readState);
			unsigned __int64 expected = ~seen;
			while (expected != seen)
			{
				waiting = (unsigned int)(seen >> 56) & 0xFF;
				unsigned int available = (unsigned int)(seen >> 28) & 0xFFFFFFF;
				available += ready;
				left = ready >= waiting ? 0 : waiting - ready;
				expected = seen;
				seen = AtomicCompareExchange64(&queue->readState, ((((unsigned __int64)left << 28)
					| (available & 0xFFFFFFF)) << 28) | ((unsigned int)seen & 0xFFFFFFF), expected);
			}
			if (waiting > 0 && left < waiting)
			{
				SemaphoreRelease(&queue->taskSemaphore, waiting - left);
			}
		}
	}

	// FUNCTION: ENGINE 0x10B82400
	// EQUIVALENT: same operations and branches; register allocation and two stack slots differ
	// Waits for a chain of tasks and copies it out (at most 16 tasks, the chain head first); the number of tasks
	unsigned int PopAsyncTasks(AsyncTaskQueue* queue, AsyncTask* tasks)
	{
		unsigned int count;
		do
		{
			// Take the next task
			unsigned int start = 0;
			for (;;)
			{
				bool wait = false;
				unsigned __int64 seen = AtomicRead64(&queue->readState);
				unsigned __int64 expected = ~seen;
				while (expected != seen)
				{
					unsigned int available = (unsigned int)(seen >> 28) & 0xFFFFFFF;
					unsigned int waiting = (unsigned int)(seen >> 56) & 0xFF;
					unsigned int index = (unsigned int)seen & 0xFFFFFFF;
					start = index;
					if (available == 0)
					{
						waiting++;
						wait = true;
					}
					else
					{
						index = (index + 1) & 0x3FF;
						available--;
						wait = false;
					}
					expected = seen;
					seen = AtomicCompareExchange64(&queue->readState, ((((unsigned __int64)waiting << 28)
						| (available & 0xFFFFFFF)) << 28) | (index & 0xFFFFFFF), expected);
				}
				if (wait)
				{
					SemaphoreWait(&queue->taskSemaphore);
					continue;
				}
				break;
			}
			CopyFromRing(start, 1, queue, tasks);
			// Take the rest of its chain once it is ready
			unsigned int length = tasks->index;
			unsigned int first = 0;
			unsigned int taken = 0;
			if (length > 0)
			{
				bool done;
				do
				{
					done = true;
					unsigned __int64 seen = AtomicRead64(&queue->readState);
					unsigned __int64 expected = ~seen;
					while (expected != seen)
					{
						first = 0;
						taken = 0;
						unsigned int available = (unsigned int)(seen >> 28) & 0xFFFFFFF;
						unsigned int waiting = (unsigned int)(seen >> 56) & 0xFF;
						unsigned int index = (unsigned int)seen & 0xFFFFFFF;
						unsigned int past = (index - start - 1) & 0x3FF;
						if (past >= length)
						{
							break;
						}
						unsigned int needed = length - past;
						if (available < needed)
						{
							done = false;
						}
						else
						{
							first = index;
							index = (index + needed) & 0x3FF;
							available -= needed;
							taken = needed;
						}
						expected = seen;
						seen = AtomicCompareExchange64(&queue->readState, ((((unsigned __int64)waiting << 28)
							| (available & 0xFFFFFFF)) << 28) | (index & 0xFFFFFFF), expected);
					}
				}
				while (!done);
			}
			// Give the slots back
			count = 1;
			unsigned int freed;
			if (!(tasks->flags & 1))
			{
				freed = MarkSlotRange(queue->freeSlots, start, 1);
			}
			else
			{
				if (length > 0)
				{
					CopyFromRing(start + 1, length, queue, tasks + 1);
				}
				count = length + 1;
				if (length > 0 && first != start + 1)
				{
					freed = MarkSlotRange(queue->freeSlots, start, 1);
					freed += MarkSlotRange(queue->freeSlots, first, taken);
				}
				else
				{
					freed = MarkSlotRange(queue->freeSlots, start, count);
				}
			}
			if (freed > 0)
			{
				int free = 0;
				int newFree;
				int waiting = 0;
				int left;
				unsigned __int64 seen = AtomicRead64(&queue->space);
				unsigned __int64 expected = ~seen;
				while (expected != seen)
				{
					free = (int)seen;
					waiting = (int)(seen >> 32);
					newFree = free + freed;
					left = waiting;
					if (free > 0)
					{
						left = freed > (unsigned int)waiting ? 0 : waiting - freed;
					}
					else if (newFree > 0)
					{
						left = newFree >= waiting ? 0 : waiting - newFree;
					}
					expected = seen;
					seen = AtomicCompareExchange64(&queue->space, ((unsigned __int64)left << 32) | (unsigned int)newFree,
						expected);
				}
				if (free < 0 && newFree >= 0)
				{
					SemaphoreRelease(&queue->overflowSemaphore, 1);
				}
				if ((unsigned int)waiting > 0 && (unsigned int)left < (unsigned int)waiting)
				{
					SemaphoreRelease(&queue->spaceSemaphore, waiting - left);
				}
			}
		}
		while (!(tasks->flags & 1));
		return count;
	}
}
