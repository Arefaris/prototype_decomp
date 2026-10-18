#include "code/core/criticalsection.h"
#include "code/core/debug.h"
#include "code/core/interlocked.h"
#include "code/ravenphysics/batch/midphasebatcher.h"
#include "code/ravenphysics/batch/narrowphasebatcher.h"
#include "code/ravenphysics/common/stackallocator.h"

#define MIDPHASEBATCHER_FILE "..\\..\\..\\code\\ravenphysics\\batch\\src\\midphasebatcher.cpp"

namespace ravenphysics
{
	int gMidPhaseTaskId;

	// A 16-byte block the mid phase takes from the scratch stack (0x106918F0 is the unit's copy of AllocOne for it)
	struct PaddedCounter
	{
		long value;
		long unused[3];
	};

	template PaddedCounter* ScratchStack::AllocOne<PaddedCounter>(int);

	// The reads of a counter other threads change (the engine's atomic helpers, inlined)
	inline long AtomicGet(long volatile* value)
	{
		return _InterlockedAnd(value, -1);
	}

	inline long AtomicIncrement(long volatile* value)
	{
		return _InterlockedIncrement(value);
	}

	inline long AtomicDecrement(long volatile* value)
	{
		return _InterlockedDecrement(value);
	}

	// FUNCTION: ENGINE 0x10691690
	void MidPhaseBatcher::Complete()
	{
		OLD_ASSERT_TEXT_AT(MIDPHASEBATCHER_FILE, 101, AtomicGet(users) == 0,
			"core::AtomicGet( mMidphaseBatchesCompletionSignal ) == 0");
	}

	// FUNCTION: ENGINE 0x106916E0
	void RegisterMidPhaseTask()
	{
		core::RegisterAsyncTaskFunction("Midphase", (void (*)(void*, core::AsyncTaskCallback*))MidPhaseTaskRun,
			&gMidPhaseTaskId);
	}

	// FUNCTION: ENGINE 0x10691700
	void UnregisterMidPhaseTask()
	{
		core::UnregisterAsyncTaskFunction(gMidPhaseTaskId);
	}

	// FUNCTION: ENGINE 0x10691710
	void PairBatch::SetCount(int newCount)
	{
		count = newCount;
	}

	// FUNCTION: ENGINE 0x10691720
	ObjectPair* PairBatch::NextSlot()
	{
		count++;
		return entries + count - 1;
	}

	// FUNCTION: ENGINE 0x10691730
	int PairBatch::GetCapacity()
	{
		return capacity;
	}

	// FUNCTION: ENGINE 0x10691740
	ObjectPair* PairBatch::GetEnd()
	{
		return entries + count;
	}

	// FUNCTION: ENGINE 0x10691750
	int PairBatch::GetCount()
	{
		return count;
	}

	// FUNCTION: ENGINE 0x10691760
	StackAllocator* StackAllocatorArray::At(int index)
	{
		return items + index;
	}

	// FUNCTION: ENGINE 0x10691780
	MidPhaseTask* MidPhaseTaskArray::NextSlot()
	{
		count++;
		return items + count - 1;
	}

	// FUNCTION: ENGINE 0x106917A0
	int MidPhaseTaskArray::GetCapacity()
	{
		return capacity;
	}

	// FUNCTION: ENGINE 0x106917B0
	int MidPhaseTaskArray::GetCount()
	{
		return count;
	}

	// FUNCTION: ENGINE 0x106917C0
	void StackAllocatorArray::Set(StackAllocator* newItems, int newCount)
	{
		items = newItems;
		count = newCount;
	}

	// FUNCTION: ENGINE 0x10691800
	void StackAllocatorArray::Create(int newCount, ScratchStack* stack)
	{
		items = (StackAllocator*)stack->Alloc(newCount * sizeof(StackAllocator), 16);
		count = newCount;
	}

	// FUNCTION: ENGINE 0x10691830
	void TaskArraySecond::Set(void* newItems, int newCount)
	{
		items = newItems;
		count = newCount;
	}

	// FUNCTION: ENGINE 0x10691890
	void MidPhaseTaskArray::Set(MidPhaseTask* newItems, int newCapacity)
	{
		items = newItems;
		count = 0;
		capacity = newCapacity;
	}

	// FUNCTION: ENGINE 0x106918B0
	void MidPhaseTaskArray::Create(int newCapacity, ScratchStack* stack)
	{
		items = (MidPhaseTask*)stack->Alloc(newCapacity * sizeof(MidPhaseTask), 16);
		capacity = newCapacity;
		count = 0;
	}

	// FUNCTION: ENGINE 0x10691900
	void TaskArrayThird::Set(void* newItems, int newCapacity)
	{
		items = newItems;
		count = 0;
		capacity = newCapacity;
	}

	// FUNCTION: ENGINE 0x10691920
	// EQUIVALENT: the same statements; the engine stores the window's buffer words right after the first allocation
	// and ours behind the next allocation's arguments (87.3 %)
	void MidPhaseBatcher::Init(NarrowPhaseBatcher* narrowPhaseBatcher, void* gate, const ProfilerPools* newPools,
		void* newWork)
	{
		pools = *newPools;
		narrowPhase = narrowPhaseBatcher;
		work = newWork;
		ScratchStack stack;
		pairs.buffer = (ObjectPair*)stack.Alloc(0x8000, 16);
		pairs.offset = 0;
		pairs.total = 0x1000;
		pairs.entries = 0;
		pairs.count = 0;
		pairs.capacity = 0;
		tasks.items = (MidPhaseTask*)stack.Alloc(0x7000, 16);
		tasks.count = 0;
		tasks.capacity = 0x200;
		workerCount = 0;
		core::GetAsyncTaskInfo(&workerCount, 0);
		unsigned int count = workerCount;
		allocators.items = (StackAllocator*)stack.Alloc(count * sizeof(StackAllocator), 16);
		allocators.count = count;
		for (unsigned int i = 0; i < workerCount; i++)
		{
			StackAllocator* allocator = allocators.items + i;
			allocator->Init(stack.Alloc(0x40000, 0x80), 0x40000, false);
		}
		pendingTasks = 0;
		event = gate;
		core::AsyncTaskNode node;
		node.Clear();
		node.Set(gMidPhaseTaskId, 0, 0, event);
		core::AsyncTaskNode::Flattened flattened;
		node.Flatten(&flattened, &task, 0x20, 0, 0, 2);
		users = (long*)stack.Alloc(0x10, 0x10);
		_InterlockedExchange(users, 1);
		node.Destroy();
	}

	// FUNCTION: ENGINE 0x10691A90
	NarrowPhaseJob* NarrowPhaseJob::ResetProfile()
	{
		unknown24 = 0;
		unknown28 = 0;
		profileEvents = 0;
		profileCapacity = 0;
		profileCounter = 0;
		unknown11C = 0;
		unknown120 = 0;
		unknown124 = 0;
		return this;
	}

	// FUNCTION: ENGINE 0x10691AC0
	// EQUIVALENT: the same reads, writes and atomic operations in the same order; the engine keeps the constant 1 in
	// no register and the zero in ebx, ours the 1 in ecx (10 %)
	void MidPhaseBatcher::QueueBatch()
	{
		tasks.count++;
		MidPhaseTask* entry = tasks.items + tasks.count - 1;
		entry->narrowPhase = narrowPhase;
		entry->entries = pairs.entries;
		entry->count = pairs.count;
		entry->work = work;
		entry->users = users;
		entry->index = pendingTasks;
		entry->pools = pools;
		entry->allocators = allocators.items;
		entry->allocatorCount = allocators.count;
		task.data = entry;
		task.timing = 0;
		if (pools.counter != 0)
		{
			int slot = _InterlockedIncrement(pools.counter) - 1;
			if (slot < pools.capacity)
			{
				Record32* record = (Record32*)((char*)pools.slots + (slot << 5));
				if (record != 0)
				{
					task.timing = (core::AsyncTaskTiming*)record;
					record->name = 0;
					record->unknown8 = -1;
					record->kind = 5;
					record->unknown10 = false;
					record->start = 0;
					record->end = 0;
					record->unknown11 = true;
				}
			}
			else
			{
				_InterlockedDecrement(pools.counter);
			}
		}
		pendingTasks++;
		_InterlockedIncrement(users);
		core::SubmitAsyncTasks(&task, 1, 2);
		pairs.offset += 20;
		pairs.entries = pairs.buffer + pairs.offset;
		pairs.count = 0;
		pairs.capacity = 20;
	}

	// FUNCTION: ENGINE 0x10691BD0
	void PairBatch::Begin()
	{
		entries = buffer + offset;
		count = 0;
		capacity = 20;
	}

	// FUNCTION: ENGINE 0x10691BF0
	void PairBatch::Add(CollisionObject* first, CollisionObject* second)
	{
		count++;
		ObjectPair* slot = entries + count - 1;
		slot->first = first;
		slot->second = second;
		if (count == capacity)
		{
			reinterpret_cast<MidPhaseBatcher*>(this)->QueueBatch();
		}
	}

	// FUNCTION: ENGINE 0x10691C20
	void PairBatch::Flush()
	{
		if ((unsigned int)count > 0)
		{
			reinterpret_cast<MidPhaseBatcher*>(this)->QueueBatch();
		}
	}

	// FUNCTION: ENGINE 0x10691C30
	void MidPhaseBatcher::Finish()
	{
		pairs.Flush();
		OLD_ASSERT_TEXT_AT(MIDPHASEBATCHER_FILE, 109, pairs.count == 0, "0 == mPairList.GetPairList().Size()");
		long value = _InterlockedDecrement(users);
		OLD_ASSERT_TEXT_AT(MIDPHASEBATCHER_FILE, 111, value >= 0, "value >= 0");
		if (value == 0)
		{
			NarrowPhaseJob job;
			job.Init(narrowPhase, -1);
			job.FlushAll();
			job.Complete();
		}
		StatEntry entry;
		entry.first = tasks.count;
		entry.second = tasks.capacity;
		entry.name = "MP Batches";
		entry.unknown8 = 0;
		pools.log.Add(entry);
		entry.first = pairs.offset;
		entry.second = pairs.total;
		entry.name = "MP Pairs";
		entry.unknown8 = 0;
		pools.log.Add(entry);
		core::EventSignal(event, 0x7ffe - pendingTasks);
	}
}
