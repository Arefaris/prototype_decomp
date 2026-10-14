#include <string.h>

#include "code/core/asynctask.h"
#include "code/core/criticalsection.h"
#include "code/core/heap.h"
#include "code/core/strings.h"
#include "code/core/time.h"

// kernel32, dllimport with the relinker's undecorated slot names
extern "C"
{
	__declspec(dllimport) void* __stdcall GetCurrentProcess();
	__declspec(dllimport) int __stdcall GetProcessAffinityMask(void* process, unsigned long* processMask,
		unsigned long* systemMask);
}
#pragma comment(linker, "/alternatename:__imp__GetCurrentProcess@0=__imp__GetCurrentProcess")
#pragma comment(linker, "/alternatename:__imp__GetProcessAffinityMask@12=__imp__GetProcessAffinityMask")

extern "C"
{
	long _InterlockedAnd(long volatile*, long);
	long _InterlockedExchange(long volatile*, long);
	__int64 _InterlockedCompareExchange64(__int64 volatile*, __int64, __int64);
	void __movsd(unsigned long*, unsigned long*, unsigned int);
}
#pragma intrinsic(_InterlockedAnd, _InterlockedExchange, _InterlockedCompareExchange64, __movsd)

namespace core
{
	// FUNCTION: ENGINE 0x10B7EB60
	// Sets the bits of `mask` in a 64-bit word atomically; the word before
	static unsigned __int64 AtomicOr64(unsigned __int64* value, unsigned __int64 mask)
	{
		unsigned __int64 old;
		unsigned __int64 seen = _InterlockedCompareExchange64((__int64 volatile*)value, 0, 0);
		unsigned __int64 expected = ~seen;
		while (expected != seen)
		{
			old = seen;
			expected = seen;
			seen = _InterlockedCompareExchange64((__int64 volatile*)value, seen | mask, expected);
		}
		return old;
	}

	// FUNCTION: ENGINE 0x10B7EBD0
	// Stops the workers (one stop task each), waits for them and frees them and the queue (the compiler passes the
	// system in esi)
	static void DestroyAsyncTaskSystem(AsyncTaskSystem* system)
	{
		AsyncTask stop;
		memset(&stop, 0, sizeof(stop));
		stop.function = 0;
		stop.kind = 0;
		for (unsigned int i = 0; i < system->workerCount; i++)
		{
			PushAsyncTasks(&system->queue, &stop, 1);
		}
		for (unsigned int i = 0; i < system->workerCount; i++)
		{
			WaitThread(&system->workers[i].thread);
			DestroyThread(&system->workers[i].thread);
		}
		HeapFree(gAsyncTaskHeap, system->workers);
		DestroyAsyncTaskQueue(&system->queue);
	}

	// FUNCTION: ENGINE 0x10B7EC90
	// Runs a chain of tasks and then the tasks they spawn, on the calling thread; false when it met the task that
	// stops a worker (the compiler passes the tasks in eax)
	static bool RunAsyncTasks(AsyncTask* task, unsigned int count, AsyncTaskQueue* queue, int processor, int index,
		AsyncTask* buffer)
	{
		AsyncTaskState state;
		SetThreadDataValue(gAsyncTaskSlot, (int)&state);
		state.processor = processor;
		state.index = index;
		for (;;)
		{
			state.hasResult = false;
			state.count = 0;
			AsyncTaskGroup* group = task->group;
			if (group != 0)
			{
				unsigned __int64* word = &group->done[task->slot >> 6];
				unsigned __int64 bit = (unsigned __int64)1 << (task->slot & 63);
				if (bit == (AtomicOr64(word, bit) & bit))
				{
					EventSignal(group, 1);
					break;
				}
			}
			const AsyncTaskFunction* function = task->function;
			if (function == 0)
			{
				SetThreadDataValue(gAsyncTaskSlot, 0);
				return false;
			}
			unsigned int start = (unsigned int)GetTicks();
			function->function(task->data, task->callback);
			unsigned int end = (unsigned int)GetTicks();
			if (task->timing != 0)
			{
				task->timing->start = start;
				task->timing->end = end;
				task->timing->processor = processor;
				_InterlockedExchange(&task->timing->done, 1);
			}
			if (count > 1)
			{
				PushAsyncTasks(queue, task + 1, count - 1);
			}
			if (task->event != 0)
			{
				EventSignal(task->event, 1);
			}
			if (task->callback != 0 && state.hasResult)
			{
				task->callback->OnResult(state.result);
			}
			if (group != 0)
			{
				EventSignal(group, 1);
			}
			unsigned int spawned = state.count;
			if (spawned == 0)
			{
				break;
			}
			if (spawned > 0)
			{
				// The size in bytes as a shift (tasks are 32 bytes), copied as dwords
				__movsd((unsigned long*)buffer, (unsigned long*)state.tasks, (spawned << 5) >> 2);
			}
			task = buffer;
			count = spawned;
		}
		SetThreadDataValue(gAsyncTaskSlot, 0);
		return true;
	}

	// FUNCTION: ENGINE 0x10B7EE70
	// A worker thread: takes tasks off the queue and runs them until it meets the stop task
	static int AsyncTaskWorkerMain(void* argument)
	{
		AsyncTask buffer[16];
		AsyncTaskWorker* worker = (AsyncTaskWorker*)argument;
		AsyncTaskQueue* queue = worker->queue;
		unsigned int count;
		do
		{
			count = PopAsyncTasks(queue, buffer);
		}
		while (RunAsyncTasks(buffer, count, queue, worker->processor, worker->index, buffer));
		return 0;
	}

	// FUNCTION: ENGINE 0x10B7EEC0
	void ShutdownAsyncTasks()
	{
		DestroyAsyncTaskSystem(&gAsyncTasks);
	}

	// FUNCTION: ENGINE 0x10B7EED0
	void InitAsyncTaskGroup(AsyncTaskGroup* group)
	{
		group->done[0] = 0;
		group->done[1] = 0;
		EventInit(group, 0xFFFF);
		group->slots = 0;
		group->added = 0;
	}

	// FUNCTION: ENGINE 0x10B7EF00
	// Closes the group (the event counts down from 0xFFFF: what was not added is signalled now) and waits for it
	void WaitAsyncTaskGroup(AsyncTaskGroup* group)
	{
		unsigned int added = group->added;
		if (added == 0)
		{
			EventSignal(group, 0xFFFF);
			return;
		}
		group->added = 0xFFFF;
		if (added < 0xFFFF)
		{
			EventSignal(group, 0xFFFF - added);
		}
		EventWait(group);
	}

	// FUNCTION: ENGINE 0x10B7EF50
	// Closes the group; whether all of its tasks have run
	bool CloseAsyncTaskGroup(AsyncTaskGroup* group)
	{
		unsigned int added = group->added;
		group->added = 0xFFFF;
		if (added < 0xFFFF)
		{
			EventSignal(group, 0xFFFF - added);
		}
		return AtomicRead(&group->count) == 0;
	}

	// FUNCTION: ENGINE 0x10B7EF90
	// EQUIVALENT: same stores; the original loads added and count into registers before adding and keeps the task
	// pointer in edx while computing the next slot (saving esi)
	// Puts a task (that counts `count` times) into the group: false when the group is full
	bool AddToAsyncTaskGroup(AsyncTaskGroup* group, AsyncTask* task, unsigned int count)
	{
		unsigned int added = group->added + count;
		if (added >= 0xFFFF)
		{
			return false;
		}
		unsigned int slot = group->slots;
		if (slot >= 0x80)
		{
			return false;
		}
		group->added = added;
		group->slots = slot + 1;
		task->group = group;
		task->slot = (unsigned char)slot;
		return true;
	}

	// FUNCTION: ENGINE 0x10B7EFD0
	void SignalAsyncTaskGroup(AsyncTaskGroup* group, int count)
	{
		EventSignal(group, count);
	}

	// FUNCTION: ENGINE 0x10B7EFE0
	unsigned int GetAsyncTaskInfo(unsigned int* workers, int* unknown)
	{
		unsigned int count = gAsyncTasks.workerCount;
		if (workers != 0)
		{
			*workers = count;
		}
		if (unknown != 0)
		{
			*unknown = 0;
		}
		return count;
	}

	// FUNCTION: ENGINE 0x10B7F000
	void SubmitAsyncTasks(AsyncTask* tasks, unsigned int count, int unused)
	{
		if (count != 0)
		{
			PushAsyncTasks(&gAsyncTasks.queue, tasks, count);
		}
	}

	// FUNCTION: ENGINE 0x10B7F030
	// EQUIVALENT: the original pushes the three arguments again and calls; ours jumps (a sibling call)
	void QueueAsyncTasks(AsyncTask* tasks, unsigned int count, int unused)
	{
		SubmitAsyncTasks(tasks, count, unused);
	}

	// FUNCTION: ENGINE 0x10B7F050
	// Runs tasks on the calling thread: chain by chain, or task by task when `single` is set
	void RunAsyncTasksHere(AsyncTask* tasks, unsigned int count, int single)
	{
		AsyncTask buffer[16];
		while (count > 0)
		{
			if (single == 0)
			{
				unsigned int length = (tasks->flags >> 1) + 1;
				RunAsyncTasks(tasks, length, &gAsyncTasks.queue, -1, -1, buffer);
				count -= length;
				tasks += length;
			}
			else
			{
				RunAsyncTasks(tasks, 1, &gAsyncTasks.queue, -1, -1, buffer);
				count--;
				tasks++;
			}
		}
	}

	// FUNCTION: ENGINE 0x10B7F0D0
	// EQUIVALENT: as QueueAsyncTasks
	void RunAsyncTasksNow(AsyncTask* tasks, unsigned int count, int single)
	{
		RunAsyncTasksHere(tasks, count, single);
	}

	// FUNCTION: ENGINE 0x10B7F0F0
	// Called by a running task: these tasks run on the same worker once it returns
	void SpawnAsyncTasks(const AsyncTask* tasks, unsigned int count)
	{
		int value = 0;
		GetThreadDataValue(gAsyncTaskSlot, &value);
		AsyncTaskState* state = (AsyncTaskState*)value;
		for (unsigned int i = 0; i < count; i++)
		{
			state->tasks[i] = tasks[i];
		}
		state->count = count;
	}

	// FUNCTION: ENGINE 0x10B7F170
	// EQUIVALENT: as QueueAsyncTasks
	void SpawnAsyncTasksNow(const AsyncTask* tasks, unsigned int count)
	{
		SpawnAsyncTasks(tasks, count);
	}

	// FUNCTION: ENGINE 0x10B7F190
	// Copies out up to max of the tasks the running task spawned; their number (all of them without a buffer)
	unsigned int GetSpawnedAsyncTasks(AsyncTask* tasks, unsigned int max)
	{
		int value = 0;
		GetThreadDataValue(gAsyncTaskSlot, &value);
		AsyncTaskState* state = (AsyncTaskState*)value;
		if (tasks == 0 || max == 0)
		{
			return state->count;
		}
		unsigned int count;
		if (max > state->count)
		{
			count = state->count;
		}
		else
		{
			count = max;
		}
		for (unsigned int i = 0; i < count; i++)
		{
			tasks[i] = state->tasks[i];
		}
		return count;
	}

	// FUNCTION: ENGINE 0x10B7F210
	// The processor of the worker running the calling task (-1 outside a task)
	int GetAsyncTaskProcessor()
	{
		int value = 0;
		GetThreadDataValue(gAsyncTaskSlot, &value);
		AsyncTaskState* state = (AsyncTaskState*)value;
		if (state == 0)
		{
			return -1;
		}
		return state->processor;
	}

	// FUNCTION: ENGINE 0x10B7F250
	int GetAsyncTaskWorkerIndex()
	{
		int value = 0;
		GetThreadDataValue(gAsyncTaskSlot, &value);
		AsyncTaskState* state = (AsyncTaskState*)value;
		if (state == 0)
		{
			return -1;
		}
		return state->index;
	}

	// FUNCTION: ENGINE 0x10B7F290
	// EQUIVALENT: the original branches on the comparison (`jne` / `mov al, al` / `xor al, al`); every form
	// tried gives sete
	bool IsAsyncTaskTimingDone(AsyncTaskTiming* timing)
	{
		if (_InterlockedAnd(&timing->done, -1) == 1)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10B7F2D0
	AsyncTaskCallback::AsyncTaskCallback()
	{
	}

	// FUNCTION: ENGINE 0x10B7F2E0
	void AsyncTaskCallback::SetResult(int result)
	{
		int value = 0;
		GetThreadDataValue(gAsyncTaskSlot, &value);
		AsyncTaskState* state = (AsyncTaskState*)value;
		state->result = result;
		state->hasResult = true;
	}

	// FUNCTION: ENGINE 0x10B7F320
	void AsyncTaskCallback::ClearResult()
	{
		int value = 0;
		GetThreadDataValue(gAsyncTaskSlot, &value);
		AsyncTaskState* state = (AsyncTaskState*)value;
		state->hasResult = false;
	}

	// FUNCTION: ENGINE 0x10B7F350
	bool AsyncTaskCallback::GetResult(int* result)
	{
		int value = 0;
		GetThreadDataValue(gAsyncTaskSlot, &value);
		AsyncTaskState* state = (AsyncTaskState*)value;
		if (state->hasResult)
		{
			*result = state->result;
			return true;
		}
		return false;
	}
}

namespace core
{
	// FUNCTION: ENGINE 0x10B7FA80
	bool AsyncTaskJob::Submit(int unused)
	{
		state = 3;
		node.Submit(unused);
		node.ClearChildren();
		return true;
	}

	// FUNCTION: ENGINE 0x10B7FB30
	// EQUIVALENT: the original stores the next processor index after the processor list entry and its address;
	// every statement order tried stores it first
	// Creates the queue and starts `count` workers named <name><4 hex digits>; with `useAffinity` each worker is
	// pinned to the next processor set in both masks (the compiler passes the system in esi)
	static void CreateAsyncTaskSystem(AsyncTaskSystem* system, unsigned int count, unsigned int processMask,
		unsigned int systemMask, bool useAffinity, int indexBase, int processorBase, int priority, const char* name)
	{
		system->workers = 0;
		system->workerCount = count;
		if (count > 0)
		{
			AllocThreadDataSlot(&gAsyncTaskSlot, 0);
			InitAsyncTaskQueue(&system->queue);
			system->workers = (AsyncTaskWorker*)HeapAlloc(gAsyncTaskHeap, count * sizeof(AsyncTaskWorker));
			unsigned int next = 0;
			for (unsigned int i = 0; i < count; i++)
			{
				int* processor = 0;
				int processors[2];
				unsigned int chosen = i;
				if (useAffinity)
				{
					processors[1] = -1;
					while (!((processMask & (1 << next)) && (systemMask & (1 << next))))
					{
						next = (next + 1) & 31;
					}
					chosen = next;
					next = (next + 1) & 31;
					processor = processors;
					processors[0] = chosen;
				}
				system->workers[i].processor = chosen + processorBase;
				system->workers[i].index = i + indexBase;
				system->workers[i].queue = &system->queue;
				char threadName[256];
				unsigned int length = 0;
				StrNCpy(threadName, name, sizeof(threadName) - 5, &length);
				unsigned int digits = i;
				for (int digit = 3; digit >= 0; digit--)
				{
					threadName[length + digit] = gHexDigits[digits & 0xF];
					digits >>= 4;
				}
				threadName[length + 4] = 0;
				StartThread(&system->workers[i].thread, AsyncTaskWorkerMain, &system->workers[i], priority, 0x8000,
					gAsyncTaskHeap, processor, threadName);
			}
		}
	}

	// FUNCTION: ENGINE 0x10B7FD00
	void InitAsyncTasks(int heap, const AsyncTaskConfig* config)
	{
		gAsyncTaskHeap = heap;
		unsigned long processMask;
		unsigned long systemMask;
		GetProcessAffinityMask(GetCurrentProcess(), &processMask, &systemMask);
		int processors = 0;
		unsigned int bit = 1;
		for (int i = 0; i < 32; i++)
		{
			if (processMask & bit)
			{
				processors++;
			}
			bit <<= 1;
		}
		int count = config->workers;
		if (count <= 0)
		{
			if (count <= -processors)
			{
				count = 1;
			}
			else
			{
				count += processors;
			}
		}
		if ((unsigned int)count >= 7)
		{
			count = 7;
		}
		CreateAsyncTaskSystem(&gAsyncTasks, count, processMask, processMask, false, 0, 0, config->priority,
			"core::AsyncTaskWorker");
	}
}
