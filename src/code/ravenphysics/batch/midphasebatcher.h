// The mid phase's pair batches (assert path code/ravenphysics/batch/src/midphasebatcher.cpp). Names and layout are
// guesses.
#ifndef RAVENPHYSICS_BATCH_MIDPHASEBATCHER_H
#define RAVENPHYSICS_BATCH_MIDPHASEBATCHER_H

#include "code/core/asynctask.h"
#include "code/ravenphysics/common/stackallocator.h"

namespace ravenphysics
{
	class CollisionObject;
	class NarrowPhaseBatcher;

	// Two objects whose bounds overlap
	struct ObjectPair
	{
		CollisionObject* first;
		CollisionObject* second;
	};

	// Collects pairs into a window of a larger array and hands full windows on
	class PairBatch
	{
	public:
		// Starts a window of 20 pairs at the current offset (0x10691BD0)
		void Begin();
		// Adds a pair to the window (0x10691BF0)
		void Add(CollisionObject* first, CollisionObject* second);
		// Queues the window when it holds pairs (0x10691C20)
		void Flush();

		// The unit's copies of the window's small accessors (0x10691710 - 0x10691750; names are guesses)
		void SetCount(int newCount);
		// Counts one more pair and gives its slot (0x10691720)
		ObjectPair* NextSlot();
		int GetCapacity();
		ObjectPair* GetEnd();
		int GetCount();

		// Takes the buffer the windows are cut from
		void SetBuffer(ObjectPair* newBuffer, int newTotal)
		{
			buffer = newBuffer;
			offset = 0;
			total = newTotal;
		}
		// Forgets the window
		void Clear()
		{
			entries = 0;
			count = 0;
			capacity = 0;
		}

		ObjectPair* entries;
		int count;
		int capacity;
		ObjectPair* buffer;
		int offset;
		int total;
	};

	// One counter of the library's statistics: two values under a name (0x10658200 adds it to the log)
	struct StatEntry
	{
		int first;
		int second;
		int unknown8;
		const char* name;
	};

	// A fixed-size log of statistics, filled from several threads
	class StatLog
	{
	public:
		// Copies the entry into the next free slot, false once the log is full (0x10658200; the engine returns
		// one byte - `mov al, 1` and a bare `ret 4` - so the result is a bool, not the word the callers ignore)
		bool Add(const StatEntry& entry);

		StatEntry* entries;
		int capacity;
		long* count;
	};

	// The profiler's pool of records and the statistics log, as the context keeps them side by side (six words)
	struct ProfilerPools
	{
		void* slots;      // 0x00 (32-byte records)
		int capacity;     // 0x04
		long* counter;    // 0x08
		StatLog log;      // 0x0C
	};

	// What a batch of pairs is worked off with by the task that picks it up (0x38 bytes; the entry of the task is
	// 0x106B54F0)
	struct MidPhaseTask
	{
		NarrowPhaseBatcher* narrowPhase;   // 0x00
		ObjectPair* entries;               // 0x04
		int count;                         // 0x08
		void* work;                        // 0x0C
		long* users;                       // 0x10
		int index;                         // 0x14
		ProfilerPools pools;               // 0x18
		StackAllocator* allocators;        // 0x30
		int allocatorCount;                // 0x34
	};

	// The scratch allocators of the workers (0x1C bytes each) and the unit's copies of its accessors
	struct StackAllocatorArray
	{
		StackAllocator* At(int index);
		void Create(int count, ScratchStack* stack);
		void Set(StackAllocator* newItems, int newCount);

		StackAllocator* items;
		int count;
	};

	// A second array that is only ever set from outside (0x10691830)
	struct TaskArraySecond
	{
		void Set(void* newItems, int newCount);

		void* items;
		int count;
	};

	// The tasks queued so far (items of 0x38 bytes) and their accessors (0x10691780 - 0x106918F0; names are
	// guesses)
	struct MidPhaseTaskArray
	{
		// Counts one more task and gives its slot (0x10691780)
		MidPhaseTask* NextSlot();
		int GetCapacity();
		int GetCount();
		void Set(MidPhaseTask* newItems, int newCapacity);
		void Create(int newCapacity, ScratchStack* stack);

		MidPhaseTask* items;
		int count;
		int capacity;
	};

	// The same three words with another element (0x10691900)
	struct TaskArrayThird
	{
		void Set(void* newItems, int newCapacity);

		void* items;
		int count;
		int capacity;
	};

	// Collects the object pairs of the mid phase in batches and hands them to the narrow phase batcher
	class MidPhaseBatcher
	{
	public:
		// Every pointer and counter starts at zero (0x10659030)
		MidPhaseBatcher();
		// Takes the narrow phase, the event, the profiler pool and the work to batch (0x10691920; name guess)
		void Init(NarrowPhaseBatcher* narrowPhaseBatcher, void* gate, const ProfilerPools* newPools, void* newWork);
		// Queues what is left and, for the last of the callers sharing the batcher, flushes the narrow phase's
		// batches and reports the statistics (0x10691C30)
		void Finish();
		// Asserts that every batch the mid phase queued has been picked up (0x10691690; name guess)
		void Complete();
		// Turns the window of pairs into a task, submits it and starts a new window (0x10691AC0; name guess)
		void QueueBatch();

		PairBatch pairs;                 // 0x00
		StackAllocatorArray allocators;  // 0x18
		unsigned int workerCount;        // 0x20
		MidPhaseTaskArray tasks;         // 0x24
		core::AsyncTask task;            // 0x30
		int pendingTasks;                // 0x50
		void* event;                     // 0x54
		NarrowPhaseBatcher* narrowPhase; // 0x58
		void* work;                      // 0x5C
		long* users;                     // 0x60
		ProfilerPools pools;             // 0x64
	};

	// The id the mid phase task is registered under (0x1127E490) and its registration (0x106916E0 / 0x10691700)
	extern int gMidPhaseTaskId;
	// The entry of the task the mid phase queues (0x106B54F0, another unit)
	void MidPhaseTaskRun(MidPhaseTask* task);
	void RegisterMidPhaseTask();
	void UnregisterMidPhaseTask();
}

#endif
