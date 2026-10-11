// Thin wrappers around the kernel32 critical-section calls (0x1063D260 - 0x1063D290, names guessed): each takes
// the address of a CRITICAL_SECTION (24 bytes) and calls Initialize / Delete / Leave / Enter through the import.
#ifndef CORE_CRITICALSECTION_H
#define CORE_CRITICALSECTION_H

namespace core
{
	void CriticalSectionInit(void* section);
	void CriticalSectionDelete(void* section);
	void CriticalSectionLeave(void* section);
	void CriticalSectionEnter(void* section);
	// 0x1063D2D0: ReleaseSemaphore(*semaphore, count, 0)
	void SemaphoreRelease(void* semaphore, int count);
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
