// ravenphysics::StackAllocator (assert path code/ravenphysics/common/src/stackallocator.cpp): the physics library's
// scratch allocator. Allocations bump a pointer inside a caller-supplied buffer and are released in one go back to a
// marker; with the fill flag set, allocations are filled with 0xDC and released ranges with 0xCC. The class and
// member names are guesses (no RTTI).
#ifndef RAVENPHYSICS_COMMON_STACKALLOCATOR_H
#define RAVENPHYSICS_COMMON_STACKALLOCATOR_H

namespace ravenphysics
{
	class StackAllocator
	{
	public:
		// 0x10686040
		StackAllocator(void* buffer, unsigned int size, bool fill);
		// Re-initialises over a buffer (0x10686090)
		void Init(void* buffer, unsigned int size, bool fill);
		// Opens a nested level and returns the current position (0x106860F0)
		void* Mark();
		// Gives everything back down to mark and closes the level (0x10686100)
		void Release(void* mark);
		// The number of open levels (0x10686130)
		int GetDepth() const;
		// size bytes aligned to align, or null when the buffer is exhausted (0x10686170)
		void* Alloc(unsigned int size, unsigned int align);
		// count objects of T, the byte size rounded up to the alignment
		template<class T>
		T* AllocArray(int count, int align);

		char* begin;
		char* end;
		char* current;
		int depth;
		bool fill;
		unsigned int highWater;
		bool unknown18;
	};

	// Defined outside the class, so the compiler keeps it out of line like the engine does
	template<class T>
	T* StackAllocator::AllocArray(int count, int align)
	{
		return (T*)Alloc((count * sizeof(T) + align - 1) & ~(align - 1), align);
	}

	// The library's scratch stack, a single buffer for the whole library (its state is in globals, 0x1127D408 on;
	// "!sLock" asserts). The member functions ignore their object, so a local empty object stands in for it
	class ScratchStack
	{
	public:
		// size bytes aligned to align, or null when the buffer is exhausted (0x10666FE0)
		void* Alloc(unsigned int size, int align);
		// Takes the library's scratch stack lock off again, asserting it was set (0x10667250; name guess)
		void Unlock();
		// count objects of T, the byte size rounded up to the alignment
		template<class T>
		T* AllocArray(int count, int align);
		// One object of T, aligned to 16 (the copies the engine emits take an argument they do not use)
		template<class T>
		T* AllocOne(int unused);
	};

	// Defined outside the class, so the compiler keeps it out of line like the engine does
	template<class T>
	T* ScratchStack::AllocArray(int count, int align)
	{
		return (T*)Alloc((count * sizeof(T) + align - 1) & ~(align - 1), align);
	}

	template<class T>
	T* ScratchStack::AllocOne(int unused)
	{
		(void)unused;
		return (T*)Alloc(sizeof(T), 16);
	}

	// Marks the scratch stack on construction and gives back everything allocated since on destruction
	// (0x106671A0 / 0x106671C0)
	class ScratchStackFrame
	{
	public:
		ScratchStackFrame();
		~ScratchStackFrame();

		void* mark;
		int depth;
	};

	// Marks the allocator on construction and releases back to the mark on destruction (0x10686140 / 0x10686160)
	class StackAllocatorScope
	{
	public:
		StackAllocatorScope(StackAllocator* allocator);
		~StackAllocatorScope();

		StackAllocator* allocator;
		void* mark;
		int depth;
	};
}

#endif
