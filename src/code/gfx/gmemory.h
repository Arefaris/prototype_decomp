// The memory interface of the Scaleform GFx library inside the engine DLL (class names from the RTTI): GAllocator and its
// subclasses, and the global allocators the library allocates through. Names of methods are guesses.
#ifndef GFX_GMEMORY_H
#define GFX_GMEMORY_H

// The allocator interface; the first slot is the destructor
class GAllocator
{
public:
	GAllocator()
	{
	}
	virtual ~GAllocator()
	{
	}
	// slot 1 / 2 / 3: a block of the size, the release of a block, the block moved to another size
	virtual void* Alloc(unsigned int size) = 0;
	virtual void Free(void* block) = 0;
	virtual void* Realloc(void* block, unsigned int size) = 0;
	// slot 4 (0x10959470): nothing in the base
	virtual int Unknown10();
	// slot 5 / 6 (0x10964B70 / 0x10964BC0): a block aligned to the alignment, with extra bytes in front; its release
	virtual void* AllocAligned(unsigned int size, unsigned int alignment, unsigned int extra);
	virtual void FreeAligned(void* block);
};

// The allocator that checks what it hands out (vftable 0x10E8D39C, eight slots)
class GDebugAllocator : public GAllocator
{
public:
	// 0x10959500
	GDebugAllocator();
	virtual ~GDebugAllocator()
	{
	}
	virtual void* Alloc(unsigned int size);
	virtual void Free(void* block);
	virtual void* Realloc(void* block, unsigned int size);
	virtual int Unknown10();
	virtual void* AllocAligned(unsigned int size, unsigned int alignment, unsigned int extra);
	virtual void FreeAligned(void* block);
	virtual void Unknown1C();
};

// The two allocators of the library that exist from the start of the program (0x1131F7E8 / 0x1131F7A0)
class GStandardAllocator : public GAllocator
{
public:
	virtual void* Alloc(unsigned int size);
	virtual void Free(void* block);
	virtual void* Realloc(void* block, unsigned int size);
	virtual int Unknown10();
	virtual void* AllocAligned(unsigned int size, unsigned int alignment, unsigned int extra);
	virtual void FreeAligned(void* block);
};

class GStandardBlockAllocator : public GAllocator
{
public:
	virtual void* Alloc(unsigned int size);
	virtual void Free(void* block);
	virtual void* Realloc(void* block, unsigned int size);
	virtual int Unknown10();
};

extern GStandardAllocator gStandardAllocator;
extern GStandardBlockAllocator gStandardBlockAllocator;
extern GDebugAllocator gDefaultDebugAllocator;

// The global allocators (0x111ECBA0 / 0x111ECBA4 / 0x111ECBA8): where the library gets its memory from. Setting null
// goes back to the one that exists from the start.
class GMemory
{
public:
	// 0x10959510 / 0x10959530
	static void __stdcall SetGlobalAllocator(GAllocator* allocator);
	static GAllocator* __stdcall GetGlobalAllocator();
	// 0x10959540 / 0x10959560
	static void __stdcall SetDebugAllocator(GDebugAllocator* allocator);
	static GDebugAllocator* __stdcall GetDebugAllocator();
	// 0x10959570 / 0x10959590
	static void __stdcall SetBlockAllocator(GAllocator* allocator);
	static GAllocator* __stdcall GetBlockAllocator();
	// 0x109595A0 / 0x109595B0 / 0x109595C0 / 0x109595D0 / 0x109595E0: the global allocator's slots 1, 3, 2, 5 and 6
	static void* __stdcall Alloc(unsigned int size);
	static void* __stdcall Realloc(void* block, unsigned int size);
	static void __stdcall Free(void* block);
	static void* __stdcall AllocAligned(unsigned int size, unsigned int alignment, unsigned int extra);
	static void __stdcall FreeAligned(void* block);

	static GAllocator* sGlobalAllocator;
	static GDebugAllocator* sDebugAllocator;
	static GAllocator* sBlockAllocator;
};

#endif
