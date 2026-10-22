// The om library's thread (RTTI: om::Thread, derived by om::TaskThread and by the threads of the audio renderer
// drivers): a core thread that is created when it is first started, can be suspended and resumed and runs the virtual
// Run when it starts.
#ifndef OM_THREAD_H
#define OM_THREAD_H

#include "code/core/thread.h"

namespace om
{
	class Thread;

	// Called on the new thread before Run (RTTI: om::ThreadEntryCallback)
	class ThreadEntryCallback
	{
	public:
		virtual void OnThreadEntry(Thread* thread) = 0;
	};

	// Where a thread may run (the second word is the processor, -1 for any)
	struct ThreadSettings
	{
		int unknown0;
		int processor;
	};

	class Thread
	{
	public:
		// 0x105C2390
		Thread(const char* newName, const ThreadSettings* settings, ThreadEntryCallback* newCallback);
		// 0x105C2470: not virtual; asks a running thread to stop and waits for it
		~Thread();
		// Slot 0: the body of the thread
		virtual void Run() = 0;
		// Slot 1 (0x105C2570)
		virtual int GetUnknown1()
		{
			return 0;
		}

		// 0x105C23E0: starts the thread, or lets a suspended one go on
		void Start();
		// 0x105C2440
		void Suspend();
		// 0x105C24B0: true once the destructor has asked the thread to stop
		bool IsStopping();
		// 0x105C24C0: waits for the thread and destroys it
		void Stop();
		// 0x105C2510
		void SetPriority(int newPriority);
		// 0x105C2550
		bool IsCurrentThread();
		// 0x105C2360: the function every thread starts in
		static int EntryPoint(void* thread);

		core::Thread thread;  // 4
		const char* name;  // 0xB8
		ThreadEntryCallback* callback;  // 0xBC
		bool stopping;  // 0xC0
		bool started;
		bool created;
		int priority;  // 0xC4
		int processor;  // 0xC8
	};

	// 0x105C2350: the callback given to the threads created from now on
	void SetThreadEntryCallback(ThreadEntryCallback* callback);
	// 0x11276810
	extern ThreadEntryCallback* gThreadEntryCallback;

	// The platform layer of the threads (names guessed): what the om library calls for a core thread
	// 0x105C2290: starts a core thread under a name with the function, its argument, priority and stack size
	void StartThread(core::Thread* thread, const char* name, int (*function)(void* argument), void* argument, int priority,
		int stackSize);
	// 0x105C22C0 - 0x105C2310 and 0x105C2540
	void DestroyThread(core::Thread* thread);
	unsigned long ResumeThread(core::Thread* thread);
	unsigned long SuspendThread(core::Thread* thread);
	int WaitThread(core::Thread* thread);
	void SetThreadPriority(core::Thread* thread, int priority);
	void ThreadSleep(int milliseconds);
	void SleepMilliseconds(int milliseconds);
	// 0x105C2320: true on the thread whose core data the argument is
	bool IsCurrentCoreThread(int thread);
}

#endif
