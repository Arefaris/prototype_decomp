// The core module's thread-synchronisation wrappers (unit 0x1063D220 - 0x1063D428, file name sync.cpp guessed; all
// names guessed): critical sections (the address of a CRITICAL_SECTION, 24 bytes), semaphores (the address of a
// handle) and counted events (two words: a count and a manual-reset event handle).
#ifndef CORE_CRITICALSECTION_H
#define CORE_CRITICALSECTION_H

namespace core
{
	void CriticalSectionInit(void* section);
	void CriticalSectionDelete(void* section);
	void CriticalSectionLeave(void* section);
	void CriticalSectionEnter(void* section);
	// 0x1063D2A0 - 0x1063D300
	void SemaphoreCreate(void* semaphore, int count);
	void SemaphoreDestroy(void* semaphore);
	void SemaphoreRelease(void* semaphore, int count);
	void SemaphoreWait(void* semaphore);
	// True when the wait timed out
	bool SemaphoreWaitTimeout(void* semaphore, int milliseconds);
	// 0x1063D370: an interlocked read
	long AtomicRead(long volatile* value);
	// 0x1063D320 - 0x1063D400: an event with a count (two words: the count, a manual-reset event handle)
	void EventInit(void* event, int count);
	void EventDestroy(void* event);
	void EventReset(void* event, int count);
	void EventSignal(void* event, int count);
	void EventWait(void* event);
	// 0x10644B40: Sleep
	void ThreadSleep(int milliseconds);
	// 0x10644DC0: the calling thread's core data (TlsGetValue)
	int GetThreadData();
}

#endif
