// The om library's thread (0x105C2290 - 0x105C2570).
#include "code/om/thread.h"

namespace om
{
	// FUNCTION: ENGINE 0x105C2290
	void StartThread(core::Thread* thread, const char* name, int (*function)(void* argument), void* argument, int priority,
		int stackSize)
	{
		core::StartThread(thread, function, argument, priority, stackSize, 0, 0, name);
	}

	// FUNCTION: ENGINE 0x105C22C0
	void DestroyThread(core::Thread* thread)
	{
		core::DestroyThread(thread);
	}

	// FUNCTION: ENGINE 0x105C22D0
	unsigned long ResumeThread(core::Thread* thread)
	{
		return core::ResumeThread(thread);
	}

	// FUNCTION: ENGINE 0x105C22E0
	unsigned long SuspendThread(core::Thread* thread)
	{
		return core::SuspendThread(thread);
	}

	// FUNCTION: ENGINE 0x105C22F0
	int WaitThread(core::Thread* thread)
	{
		return core::WaitThread(thread);
	}

	// FUNCTION: ENGINE 0x105C2300
	void SetThreadPriority(core::Thread* thread, int priority)
	{
		core::SetThreadPriority(thread, priority);
	}

	// FUNCTION: ENGINE 0x105C2310
	void ThreadSleep(int milliseconds)
	{
		core::ThreadSleep(milliseconds);
	}

	// FUNCTION: ENGINE 0x105C2320
	bool IsCurrentCoreThread(int thread)
	{
		return core::GetThreadData() == thread;
	}

	// FUNCTION: ENGINE 0x105C2350
	void SetThreadEntryCallback(ThreadEntryCallback* callback)
	{
		gThreadEntryCallback = callback;
	}

	// FUNCTION: ENGINE 0x105C2360
	int Thread::EntryPoint(void* argument)
	{
		Thread* thread = static_cast<Thread*>(argument);
		if (thread->callback != 0)
		{
			thread->callback->OnThreadEntry(thread);
		}
		thread->Run();
		return 0;
	}

	// FUNCTION: ENGINE 0x105C2390
	Thread::Thread(const char* newName, const ThreadSettings* settings, ThreadEntryCallback* newCallback) :
		name(newName),
		stopping(false),
		started(false),
		created(false),
		callback(newCallback),
		priority(2),
		processor(settings->processor)
	{
	}

	// FUNCTION: ENGINE 0x105C23E0
	void Thread::Start()
	{
		if (!started)
		{
			started = true;
			if (!created)
			{
				core::StartThread(&thread, EntryPoint, this, priority, 0x10000, 0, 0, name);
				created = true;
				return;
			}
			core::ResumeThread(&thread);
		}
	}

	// FUNCTION: ENGINE 0x105C2440
	void Thread::Suspend()
	{
		if (started)
		{
			core::SuspendThread(&thread);
			started = false;
		}
	}

	// FUNCTION: ENGINE 0x105C2470
	Thread::~Thread()
	{
		if (started)
		{
			stopping = true;
			core::WaitThread(&thread);
		}
		if (created)
		{
			core::DestroyThread(&thread);
		}
	}

	// FUNCTION: ENGINE 0x105C24B0
	bool Thread::IsStopping()
	{
		return stopping;
	}

	// FUNCTION: ENGINE 0x105C24C0
	void Thread::Stop()
	{
		if (started)
		{
			core::WaitThread(&thread);
			stopping = false;
			started = false;
			created = true;
		}
		if (created)
		{
			core::DestroyThread(&thread);
			created = false;
		}
	}

	// FUNCTION: ENGINE 0x105C2510
	void Thread::SetPriority(int newPriority)
	{
		priority = newPriority;
		if (started)
		{
			core::SetThreadPriority(&thread, newPriority);
		}
	}

	// FUNCTION: ENGINE 0x105C2540
	void SleepMilliseconds(int milliseconds)
	{
		core::ThreadSleep(milliseconds);
	}

	// FUNCTION: ENGINE 0x105C2550
	bool Thread::IsCurrentThread()
	{
		return core::GetThreadData() == reinterpret_cast<int>(&thread);
	}
}
