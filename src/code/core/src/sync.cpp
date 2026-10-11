#include "code/core/criticalsection.h"

// The kernel32 imports, declared as the import-table slots themselves: the toolchain has no SDK headers, and the
// import library the relinker generates names the slots without the __stdcall decoration (__imp__Name, not
// __imp__Name@N). A call through the slot is the same `call dword ptr [__imp__Name]` a dllimport declaration gives.
extern "C"
{
	extern void (__stdcall* _imp__InitializeCriticalSection)(void* section);
	extern void (__stdcall* _imp__DeleteCriticalSection)(void* section);
	extern void (__stdcall* _imp__LeaveCriticalSection)(void* section);
	extern void (__stdcall* _imp__EnterCriticalSection)(void* section);
	extern void* (__stdcall* _imp__CreateSemaphoreA)(void* attributes, long initial, long maximum, const char* name);
	extern int (__stdcall* _imp__CloseHandle)(void* handle);
	extern int (__stdcall* _imp__ReleaseSemaphore)(void* semaphore, long count, long* previous);
	extern unsigned long (__stdcall* _imp__WaitForSingleObject)(void* handle, unsigned long milliseconds);
	extern void* (__stdcall* _imp__CreateEventA)(void* attributes, int manualReset, int initialState, const char* name);
	extern int (__stdcall* _imp__ResetEvent)(void* event);
	extern int (__stdcall* _imp__SetEvent)(void* event);

	long _InterlockedAnd(long volatile*, long);
	long _InterlockedCompareExchange(long volatile*, long, long);
}
#pragma intrinsic(_InterlockedAnd, _InterlockedCompareExchange)

namespace core
{
	// A counted event: waiters block while the count is not zero; EventSignal counts down and sets the event when
	// it reaches zero
	struct Event
	{
		long volatile count;
		void* handle;
	};

	// FUNCTION: ENGINE 0x1063D220
	// Counts down by `count` without going below zero; the count before (the compiler passes the event in esi and
	// the count in edx)
	static unsigned int EventCountDown(Event* event, unsigned int count)
	{
		unsigned int old = _InterlockedAnd(&event->count, -1);
		for (;;)
		{
			unsigned int value = old <= count ? 0 : old - count;
			unsigned int seen = _InterlockedCompareExchange(&event->count, value, old);
			if (seen == old)
			{
				return old;
			}
			old = seen;
		}
	}

	// FUNCTION: ENGINE 0x1063D260
	void CriticalSectionInit(void* section)
	{
		_imp__InitializeCriticalSection(section);
	}

	// FUNCTION: ENGINE 0x1063D270
	void CriticalSectionDelete(void* section)
	{
		_imp__DeleteCriticalSection(section);
	}

	// FUNCTION: ENGINE 0x1063D280
	void CriticalSectionLeave(void* section)
	{
		_imp__LeaveCriticalSection(section);
	}

	// FUNCTION: ENGINE 0x1063D290
	void CriticalSectionEnter(void* section)
	{
		_imp__EnterCriticalSection(section);
	}

	// FUNCTION: ENGINE 0x1063D2A0
	void SemaphoreCreate(void* semaphore, int count)
	{
		*(void**)semaphore = _imp__CreateSemaphoreA(0, count, 0x7FFFFFFF, 0);
	}

	// FUNCTION: ENGINE 0x1063D2C0
	void SemaphoreDestroy(void* semaphore)
	{
		_imp__CloseHandle(*(void**)semaphore);
	}

	// FUNCTION: ENGINE 0x1063D2D0
	void SemaphoreRelease(void* semaphore, int count)
	{
		_imp__ReleaseSemaphore(*(void**)semaphore, count, 0);
	}

	// FUNCTION: ENGINE 0x1063D2F0
	void SemaphoreWait(void* semaphore)
	{
		_imp__WaitForSingleObject(*(void**)semaphore, 0xFFFFFFFF);
	}

	// FUNCTION: ENGINE 0x1063D300
	bool SemaphoreWaitTimeout(void* semaphore, int milliseconds)
	{
		return _imp__WaitForSingleObject(*(void**)semaphore, milliseconds) == 0x102;
	}

	// FUNCTION: ENGINE 0x1063D320
	void EventInit(void* event, int count)
	{
		((Event*)event)->count = count;
		((Event*)event)->handle = _imp__CreateEventA(0, 1, count == 0, 0);
	}

	// FUNCTION: ENGINE 0x1063D350
	void EventDestroy(void* event)
	{
		_imp__WaitForSingleObject(((Event*)event)->handle, 0xFFFFFFFF);
		_imp__CloseHandle(((Event*)event)->handle);
	}

	// FUNCTION: ENGINE 0x1063D370
	long AtomicRead(long volatile* value)
	{
		return _InterlockedAnd(value, -1);
	}

	// FUNCTION: ENGINE 0x1063D390
	void EventReset(void* event, int count)
	{
		_InterlockedCompareExchange(&((Event*)event)->count, count, 0);
		if ((unsigned int)count > 0)
		{
			_imp__WaitForSingleObject(((Event*)event)->handle, 0xFFFFFFFF);
			_imp__ResetEvent(((Event*)event)->handle);
		}
	}

	// FUNCTION: ENGINE 0x1063D3D0
	void EventSignal(void* event, int count)
	{
		if (count != 0)
		{
			unsigned int old = EventCountDown((Event*)event, count);
			if (old != 0 && (unsigned int)count >= old)
			{
				_imp__SetEvent(((Event*)event)->handle);
			}
		}
	}

	// FUNCTION: ENGINE 0x1063D400
	void EventWait(void* event)
	{
		long count = _InterlockedAnd(&((Event*)event)->count, -1);
		if (count != 0)
		{
			_imp__WaitForSingleObject(((Event*)event)->handle, 0xFFFFFFFF);
		}
	}
}
