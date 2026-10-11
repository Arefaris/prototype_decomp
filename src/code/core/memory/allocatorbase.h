// The pieces every real allocator of the core module is built from (RTTI names core::AllocatorBase,
// core::AllocatorBase_Name, core::AllocatorBase_Safety; member and method names guessed from their users).
// AllocatorBase is 0x40 bytes: the name buffer at 0, the safety block (a critical section plus its mode) at 0x20.
// The methods live in another unit (0x10646D10 - 0x10646E10, see the work list); only their shapes are known here.
#ifndef CORE_MEMORY_ALLOCATORBASE_H
#define CORE_MEMORY_ALLOCATORBASE_H

namespace core
{
	struct AllocatorBase_Name
	{
		// 0x10646E00: SetName("unknown")
		AllocatorBase_Name();
		// 0x10646D10: empty
		~AllocatorBase_Name();
		// 0x10646D20: the buffer itself
		const char* GetName();
		// 0x10646D30: a bounded copy into the 32-byte buffer
		void SetName(const char* name);

		char name[32];
	};

	struct AllocatorBase_Safety
	{
		// 0x10646D50: flag 0, mode 1
		AllocatorBase_Safety();
		// 0x10646D70: deletes the critical section when the mode is 2
		~AllocatorBase_Safety();
		// 0x10646D80: changes the mode (2 creates the critical section, leaving 2 deletes it)
		void SetMode(int mode, void* owner);
		// 0x10646DC0
		int GetMode();
		// 0x10646DD0: empty
		void SetUnused(int value);
		// 0x10646DE0 / 0x10646DF0: enter / leave the critical section when the mode is 2
		void Lock();
		void Unlock();

		int section[6];
		int flag;
		int mode;
	};

	struct AllocatorBase : AllocatorBase_Name, AllocatorBase_Safety
	{
	};

	// Holds the allocator's lock for a scope. Constructed from the allocator itself: the conversion of `this` to
	// the AllocatorBase_Safety base is what the original's null-checked `this + 0x30` is.
	class AllocatorLock
	{
	public:
		AllocatorLock(AllocatorBase_Safety* safety)
			: safety(safety)
		{
			safety->Lock();
		}
		~AllocatorLock()
		{
			safety->Unlock();
		}

	private:
		AllocatorBase_Safety* safety;
	};
}

#endif
