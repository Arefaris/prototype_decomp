// The core's asynchronous tasks (all names guessed except core::AsyncTaskCallback, from RTTI, and the worker
// thread name "core::AsyncTaskWorker"): tasks are 32-byte records pushed onto one lock-free queue of 1024 slots
// that a pool of worker threads drains. A task runs a function on its data; a run of tasks can be pushed as one
// chain (each one queues the rest of the chain when it has run), a task can signal a counted event, count down a
// task group and report a result to a callback object. While a task runs, the worker's per-thread state (a core
// thread-data slot) collects the tasks it spawns and the result it sets.
// Units: asynctask.cpp (0x10B7EB10 onwards) and asynctaskqueue.cpp (0x10B81B70 - 0x10B827A0).
#ifndef CORE_ASYNCTASK_H
#define CORE_ASYNCTASK_H

#include "code/core/thread.h"

namespace core
{
	class AsyncTaskCallback;

	// What a task runs
	struct AsyncTaskFunction
	{
		int id;
		void (*function)(void* data, AsyncTaskCallback* callback);
	};

	// Filled in when a task has run (ticks are the low words of core::GetTicks)
	struct AsyncTaskTiming
	{
		unsigned int start;
		unsigned int end;
		int processor;
		long volatile done;
	};

	// A set of up to 128 tasks one can wait for: a counted event, one "has run" bit per task (a task whose bit is
	// already set when it comes up does not run again), the next free bit and the number of tasks added
	struct AsyncTaskGroup
	{
		long volatile count;
		void* handle;
		unsigned __int64 volatile done[2];
		unsigned int slots;
		unsigned int added;
	};

	struct AsyncTask
	{
		// Bit 0: the task closes its chain; bits 1 - 7: the number of tasks that follow it in its chain
		unsigned char flags;
		// The task's position from the end of its chain
		unsigned char index;
		unsigned char kind;
		// The task's bit in its group
		unsigned char slot;
		void* data;
		// Null for the task that stops a worker
		const AsyncTaskFunction* function;
		int unknownC;
		AsyncTaskCallback* callback;
		// A counted event (code/core/criticalsection.h), signalled once when the task has run
		void* event;
		AsyncTaskTiming* timing;
		AsyncTaskGroup* group;
	};

	// A task to build: what it runs and on what, and the tasks that run after it (a tree flattened into chains of
	// AsyncTask records when it is submitted)
	struct AsyncTaskNode
	{
		int type;
		const AsyncTaskFunction* function;
		void* data;
		AsyncTaskCallback* callback;
		void* event;
		AsyncTaskTiming* timing;
		unsigned int childCount;
		AsyncTaskNode* firstChild;
		AsyncTaskNode* lastChild;
		AsyncTaskNode* next;

		// Flattens the tree into a stack buffer of 32 tasks and submits it
		void Submit(int unused);
		void ClearChildren();
	};

	// A node with a state and the timing record its task fills in
	class AsyncTaskJob
	{
	public:
		// 1: idle or done; 3: submitted; 4: run on the calling thread
		int state;
		int unknown4[3];
		AsyncTaskTiming timing;
		AsyncTaskNode node;

		bool Submit(int unused);
	};

	// The per-thread state of a running task (a core thread-data slot points at it while the task runs)
	struct AsyncTaskState
	{
		// The tasks the running task spawns: they run on the same worker when it is done
		AsyncTask tasks[16];
		unsigned int count;
		bool hasResult;
		int result;
		int processor;
		int index;
	};

	// The queue the workers drain (asynctaskqueue.cpp): 1024 task slots behind lock-free counters, three semaphores
	struct AsyncTaskQueue
	{
		unsigned __int64 volatile freeSlots[18];
		unsigned __int64 volatile readState;
		unsigned __int64 volatile usedSlots[18];
		long volatile writeIndex;
		int unknown12C;
		unsigned __int64 volatile space;
		void* spaceSemaphore;
		void* taskSemaphore;
		void* fullSemaphore;
		int unknown144[3];
		AsyncTask tasks[1024];
	};

	// A worker thread record
	struct AsyncTaskWorker
	{
		Thread thread;
		int processor;
		int index;
		AsyncTaskQueue* queue;
	};

	// The task system: the queue and the workers
	struct AsyncTaskSystem
	{
		AsyncTaskQueue queue;
		AsyncTaskWorker* workers;
		unsigned int workerCount;
	};

	class AsyncTaskCallback
	{
	public:
		AsyncTaskCallback();
		// Told the result the task set, on the worker, once the task has run
		virtual void OnResult(int result) = 0;
		// The running task's result (stored in the worker's state; the callback object itself is not touched)
		void SetResult(int result);
		void ClearResult();
		bool GetResult(int* result);
	};

	// asynctaskqueue.cpp
	void InitAsyncTaskQueue(AsyncTaskQueue* queue);
	void DestroyAsyncTaskQueue(AsyncTaskQueue* queue);
	void PushAsyncTasks(AsyncTaskQueue* queue, AsyncTask* tasks, unsigned int count);
	unsigned int PopAsyncTasks(AsyncTaskQueue* queue, AsyncTask* tasks);

	// What InitAsyncTasks reads: the number of workers (zero or less: that many fewer than the processors, at least
	// one; at most seven) and their priority
	struct AsyncTaskConfig
	{
		int workers;
		int unknown4;
		int priority;
	};

	// asynctask.cpp
	extern int gAsyncTaskSlot;
	extern AsyncTaskSystem gAsyncTasks;
	extern int gAsyncTaskHeap;
	void InitAsyncTasks(int heap, const AsyncTaskConfig* config);
	void ShutdownAsyncTasks();
	void InitAsyncTaskGroup(AsyncTaskGroup* group);
	void WaitAsyncTaskGroup(AsyncTaskGroup* group);
	bool IsAsyncTaskGroupDone(AsyncTaskGroup* group);
	bool AddToAsyncTaskGroup(AsyncTaskGroup* group, AsyncTask* task, unsigned int count);
	void SubmitAsyncTasks(AsyncTask* tasks, unsigned int count, int unused);
	bool IsAsyncTaskTimingDone(AsyncTaskTiming* timing);
}

#endif
