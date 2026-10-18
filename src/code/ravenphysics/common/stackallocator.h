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
		// Nothing is set up: the derived scratch allocators call Init
		StackAllocator()
		{
		}
		// 0x10686040
		StackAllocator(void* buffer, unsigned int size, bool fill);
		// Empty (0x106860E0)
		~StackAllocator();
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

	// A stack allocator that remembers what it was made for (name guess; the physics library builds these over its
	// scratch buffers)
	class ScratchAllocator : public StackAllocator
	{
	public:
		// 0x10656340: the owner, then the buffer the allocator runs over
		ScratchAllocator(int newOwner, void* buffer, unsigned int size);
		// Empty (0x10656570); runs the base's
		~ScratchAllocator();

		int owner;  // 0x1C
	};

	// The same object built in place, where the engine inlines the constructor and the destructor of the scratch
	// allocator
	class LocalScratchAllocator : public StackAllocator
	{
	public:
		int owner;  // 0x1C
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
		// The room left for a block aligned to align (0x10666F00; name guess)
		unsigned int GetFree(int align);
		// Takes size bytes from the heap for the stack, filled with 0xCC when fill is set (0x10666F30)
		static void Create(unsigned int size, int heap, bool fill);
		// Gives the buffer back (0x10666F90)
		static void Free();
		// size bytes aligned to align, or null when the buffer is exhausted (0x10666FE0)
		void* Alloc(unsigned int size, int align);
		// Always true (0x10667090; the argument is not used; name guess)
		bool IsReady(int unused);
		// Opens a level and returns the current position (0x106670A0)
		static void* Mark();
		// Gives everything back down to mark and closes the level (0x10667100)
		static void Release(void* mark);
		// The number of open levels (0x10667190)
		static int GetDepth();
		// Makes the rest of the buffer the stack allocator's and locks the scratch stack (0x106671D0; name guess)
		void HandOver(StackAllocator* allocator);
		// Locks the scratch stack: nothing may be taken from it until Unlock (0x10667200; name guess)
		void Lock();
		// Takes the library's scratch stack lock off again, asserting it was set (0x10667250; name guess)
		void Unlock();
		// count objects of T, the byte size rounded up to the alignment
		template<class T>
		T* AllocArray(int count, int align);
		// One object of T, aligned to 16 (the copies the engine emits take an argument they do not use)
		template<class T>
		T* AllocOne(int unused);

		static char* sBegin;               // 0x1127D408
		static unsigned int sHighWater;    // 0x1127D40C
		static int sDepth;                 // 0x1127D410
		static bool sFill;                 // 0x1127D414
		static bool sLock;                 // 0x1127D415
		static char* sEnd;                 // 0x1127D418
		static char* sCurrent;             // 0x1127D41C
		static int sUnknown;               // 0x1127D420
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
		// Opens the level again over an existing frame (0x106671A0, the constructor's body)
		ScratchStackFrame* Open();

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
