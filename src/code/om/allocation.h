// The om library's allocation: every class has its own operator new and operator delete that ask the allocator for
// exactly sizeof(Type) bytes of __alignof(Type), and pass a tag that names the allocation (the engine's tag functions
// answer an empty string). The tag is a function of its own, out of line in the unit of the class (its address is the
// last of the three members the macro declares).
#ifndef OM_ALLOCATION_H
#define OM_ALLOCATION_H

#include <stddef.h>

namespace om
{
	// 0x105B7570: the memory of the size and alignment (the tag names the allocation)
	void* Allocate(const char* tag, unsigned int size, unsigned int alignment);
	// 0x105B7590: gives it back
	void Release(void* memory, unsigned int size, unsigned int alignment);
}

#define OM_ALLOCATION(Type) \
	static void* operator new(size_t) \
	{ \
		return om::Allocate(Type::AllocationTag(), sizeof(Type), __alignof(Type)); \
	} \
	static void operator delete(void* memory) \
	{ \
		om::Release(memory, sizeof(Type), __alignof(Type)); \
	} \
	static const char* AllocationTag()

#endif
