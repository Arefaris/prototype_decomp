// The user slots of threads and fibers (unit 0x106469A0 - 0x10646D06, file name threadslots.cpp and all names
// guessed): eight slots per Thread record and eight per fiber, allocated from a bit mask each; a new slot is set to
// its default in every thread (or every fiber of every thread) that exists, and the defaults are what new threads and
// fibers start with (GetThreadSlotDefaults, AddFiber in thread.cpp). Once the thread system runs, allocation happens
// under the thread lock. The fiber slots are what the engine uses as thread-local values.
#include "code/core/criticalsection.h"
#include "code/core/thread.h"

namespace core
{
	// GLOBAL: ENGINE 0x1127A9B4
	static unsigned int sThreadDataSlots;
	// GLOBAL: ENGINE 0x1127A9B8
	static unsigned int sThreadSlots;

	// FUNCTION: ENGINE 0x106469A0
	static bool AllocThreadDataSlotLocked(int* slot, int value)
	{
		unsigned int used = sThreadDataSlots;
		unsigned int bit = 1;
		for (unsigned int i = 0; i < 8; i++, bit += bit)
		{
			if ((bit & used) == 0)
			{
				sThreadDataSlots = used | bit;
				*slot = i;
				gThreadSlotDefaults[i] = value;
				for (Thread* thread = gThreads; thread != 0; thread = thread->next)
				{
					thread->slots[i] = value;
				}
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106469F0
	static bool FreeThreadDataSlotLocked(int slot)
	{
		unsigned int bit = 1 << slot;
		if (sThreadDataSlots & bit)
		{
			sThreadDataSlots &= ~bit;
			gThreadSlotDefaults[slot] = 0;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10646A20
	bool AllocThreadDataSlot(int* slot, int value)
	{
		if (gThreadsReady)
		{
			CriticalSectionEnter(gThreadLock);
			bool result = AllocThreadDataSlotLocked(slot, value);
			CriticalSectionLeave(gThreadLock);
			return result;
		}
		return AllocThreadDataSlotLocked(slot, value);
	}

	// FUNCTION: ENGINE 0x10646A70
	bool FreeThreadDataSlot(int slot)
	{
		if (gThreadsReady)
		{
			CriticalSectionEnter(gThreadLock);
			bool result = FreeThreadDataSlotLocked(slot);
			CriticalSectionLeave(gThreadLock);
			return result;
		}
		return FreeThreadDataSlotLocked(slot);
	}

	// FUNCTION: ENGINE 0x10646AB0
	bool SetThreadDataValue(int slot, int value)
	{
		((Thread*)GetThreadData())->slots[slot] = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10646AD0
	bool GetThreadDataValue(int slot, int* value)
	{
		Thread* thread = (Thread*)GetThreadData();
		if (thread != 0)
		{
			*value = thread->slots[slot];
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10646AF0
	bool ExchangeThreadDataValue(int slot, int* previous, int value)
	{
		Thread* thread = (Thread*)GetThreadData();
		if (thread != 0)
		{
			*previous = thread->slots[slot];
			thread->slots[slot] = value;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10646B20
	Thread* NextThread(Thread* thread)
	{
		Thread* next;
		if (thread == 0)
		{
			CriticalSectionEnter(gThreadLock);
			next = gThreads;
		}
		else
		{
			next = thread->next;
		}
		if (next == 0)
		{
			CriticalSectionLeave(gThreadLock);
		}
		return next;
	}

	// FUNCTION: ENGINE 0x10646B60
	Fiber* NextFiber(Thread* thread, Fiber* fiber)
	{
		if (fiber == 0)
		{
			return thread->fibers;
		}
		return fiber->next;
	}

	// FUNCTION: ENGINE 0x10646B80
	static bool AllocThreadSlotLocked(int* slot, int value)
	{
		unsigned int used = sThreadSlots;
		unsigned int bit = 1;
		for (unsigned int i = 0; i < 8; i++, bit += bit)
		{
			if ((bit & used) == 0)
			{
				sThreadSlots = used | bit;
				*slot = i;
				gFiberSlotDefaults[i] = value;
				for (Thread* thread = gThreads; thread != 0; thread = thread->next)
				{
					for (Fiber* fiber = thread->fibers; fiber != 0; fiber = fiber->next)
					{
						fiber->slots[i] = value;
					}
				}
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10646BE0
	static bool FreeThreadSlotLocked(int slot)
	{
		unsigned int bit = 1 << slot;
		if (sThreadSlots & bit)
		{
			sThreadSlots &= ~bit;
			gFiberSlotDefaults[slot] = 0;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10646C10
	bool AllocThreadSlot(int* slot, int value)
	{
		if (gThreadsReady)
		{
			CriticalSectionEnter(gThreadLock);
			bool result = AllocThreadSlotLocked(slot, value);
			CriticalSectionLeave(gThreadLock);
			return result;
		}
		return AllocThreadSlotLocked(slot, value);
	}

	// FUNCTION: ENGINE 0x10646C60
	bool FreeThreadSlot(int slot)
	{
		if (gThreadsReady)
		{
			CriticalSectionEnter(gThreadLock);
			bool result = FreeThreadSlotLocked(slot);
			CriticalSectionLeave(gThreadLock);
			return result;
		}
		return FreeThreadSlotLocked(slot);
	}

	// FUNCTION: ENGINE 0x10646CA0
	bool SetThreadValue(int slot, int value)
	{
		GetCurrentFiber()->slots[slot] = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10646CC0
	bool GetThreadValue(int slot, int* value)
	{
		Fiber* fiber = GetCurrentFiber();
		if (fiber != 0)
		{
			*value = fiber->slots[slot];
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10646CE0
	bool ExchangeThreadValue(int slot, int* previous, int value)
	{
		Fiber* fiber = GetCurrentFiber();
		if (fiber != 0)
		{
			*previous = fiber->slots[slot];
			fiber->slots[slot] = value;
			return true;
		}
		return false;
	}
}
