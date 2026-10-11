// The core threads and fibers (all names guessed): every thread the core creates (and the main thread) has a
// Thread record in a global list, reachable from the thread through a TLS slot; each thread runs as a fiber and can
// switch between fibers of its own. Threads and fibers carry eight user slots each, initialised from global
// defaults (the slot registration is the unit at 0x106469A0). Unit 0x10644890 - 0x106452F6 (file name thread.cpp
// guessed). All access to the lists goes through one critical section.
#ifndef CORE_THREAD_H
#define CORE_THREAD_H

namespace core
{
	struct Thread;

	struct Fiber
	{
		int (*function)(void* argument);
		void* argument;
		Thread* thread;
		Fiber* next;
		Fiber* previous;
		int slots[8];
		void* handle;
		void* stack;
		int unknown3C;
		bool trackStack;
	};

	struct Thread
	{
		Thread* next;
		Thread* previous;
		// The fiber the thread itself runs as
		Fiber fiber;
		Fiber* current;
		Fiber* fibers;
		Fiber* lastFiber;
		volatile bool running;
		int exitCode;
		int priority;
		int slots[8];
		int unknown84;
		unsigned int unknown88;
		unsigned long id;
		void* handle;
		char name[0x20];
	};

	// The thread system's state
	extern Thread gMainThread;
	extern Thread* gLastThread;
	extern Thread* gThreads;
	extern int gFiberSlotDefaults[8];
	extern int gThreadSlotDefaults[8];
	extern unsigned char gThreadLock[0x18];
	extern bool gThreadsReady;

	// 0x1063C130 / 0x1063C150 (another unit): start-up and shut-down of a lock the thread system brings along
	void InitThreadHook();
	void ShutdownThreadHook();

	void InitThreadLock();
	void ShutdownThreadLock();
	inline void GetThreadSlotDefaults(Thread* thread);
	void AddThread(Thread* thread);
	void RemoveThread(Thread* thread);
	void AddFiber(Thread* thread, Fiber* fiber);
	inline void RemoveFiber(Thread* thread, Fiber* fiber);
	void ThreadNop();
	// Windows XP and later: turns the calling fiber back into a thread
	void LeaveFiberMode();
	bool IsCurrentThread(Thread* thread);
	// Waits for the thread (or ends it: the calling thread exits, another is terminated while it still runs)
	void DestroyThread(Thread* thread);
	int GetThreadValue(Thread* thread);
	bool IsThreadBusy(Thread* thread);
	int GetZero();
	void SetThreadPriority(Thread* thread, int priority);
	int GetThreadPriority(Thread* thread);
	unsigned long SuspendThread(Thread* thread);
	unsigned long ResumeThread(Thread* thread);
	// False (with the exit code) once the thread has finished
	bool IsThreadRunning(Thread* thread, int* exitCode);
	int WaitThread(Thread* thread);
	// 0x10644DC0: the calling thread's Thread (as an int, the way the file units take it)
	int GetThreadData();
	void ThreadSleep(int milliseconds);
	Fiber* GetCurrentFiber();
	void DestroyFiber(Fiber* fiber);
	void SwitchFiber(Fiber* fiber);
	int GetZero2();
	int GetZero3();
	void* GetFiberArgument(Fiber* fiber);
	void InitMainThread(Thread* thread);
	void ShutdownMainThread();
	unsigned long CreateThread(Thread* thread, int (*function)(void* argument), void* argument, int priority,
		int stackSize, int* processor, const char* name);
	void StartThread(Thread* thread, int (*function)(void* argument), void* argument, int priority, int stackSize,
		int unused, int* processor, const char* name);
	// Starts the thread system (the argument is unused)
	void InitMemoryStage3(int count);
	void ShutdownThreads();
	void SetThreadValue(int value);
	void ClearThreadValue(int unused);
	void CreateFiber(Fiber* fiber, int (*function)(void* argument), void* argument, int unused1, int stackSize,
		int track, int unused2, int unused3);
	void CreateFiber(Fiber* fiber, int (*function)(void* argument), void* argument, int stackSize, int a, int b);
	void CreateFiber(Fiber* fiber, int (*function)(void* argument), void* argument, int stackSize, int b);
	void CreateTrackedFiber(Fiber* fiber, int (*function)(void* argument), void* argument, int stackSize, int a, int b);
	void CreateTrackedFiber(Fiber* fiber, int (*function)(void* argument), void* argument, int stackSize, int b);
}

#endif
