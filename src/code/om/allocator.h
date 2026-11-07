// The om library's allocators (RTTI: om::Allocator, om::DefaultAllocator; the free functions' names are guesses): the
// allocator that is in force answers every allocation of the om classes (om::Allocate / om::Release, allocation.h).
// The tracked forms put the alignment and the size of the block in the two words in front of the block that is handed
// out, so that a block can be given back without knowing them.
#ifndef OM_ALLOCATOR_H
#define OM_ALLOCATOR_H

namespace om
{
	class Allocator
	{
	public:
		Allocator()
		{
		}
		virtual ~Allocator()
		{
		}
		// Slot 1: memory of the size and alignment (the tag names the allocation)
		virtual void* Allocate(const char* tag, unsigned int size, unsigned int alignment) = 0;
		// Slot 2: gives it back
		virtual void Release(void* memory, unsigned int size, unsigned int alignment) = 0;
		// Slot 3 (0x105B7600): a block that remembers its alignment and size
		virtual void* AllocateTracked(const char* tag, unsigned int size, unsigned int alignment);
		// Slot 4 (0x105B7460): gives such a block back
		virtual void ReleaseTracked(void* memory);
	};

	// Allocates from the heap the core module calls the default one
	class DefaultAllocator : public Allocator
	{
	public:
		// 0x105B75D0
		DefaultAllocator();
		// Slots 1 and 2 (0x105B73D0 / 0x105B73F0)
		virtual void* Allocate(const char* tag, unsigned int size, unsigned int alignment);
		virtual void Release(void* memory, unsigned int size, unsigned int alignment);
	};

	// 0x110B6448: the allocator that is in force until another is set
	extern DefaultAllocator gDefaultAllocator;
	// 0x110B6444: the allocator that is in force
	extern Allocator* gAllocator;

	// 0x105B7430: makes another allocator the one in force (null brings the default one back); answers the old one
	Allocator* SetAllocator(Allocator* allocator);
	// 0x105B7450
	Allocator* GetAllocator();
	// 0x105B75B0: the larger of two numbers
	unsigned int Max(const unsigned int& first, const unsigned int& second);
	// 0x105B7490 / 0x105B74B0: the tracked forms through an allocator
	void* AllocateTrackedFrom(Allocator* allocator, const char* tag, unsigned int size, unsigned int alignment);
	void ReleaseTrackedFrom(Allocator* allocator, void* memory);
	// 0x105B74D0 / 0x105B7500: the plain forms through an allocator (nothing for an empty block)
	void* AllocateFrom(Allocator* allocator, const char* tag, unsigned int size, unsigned int alignment);
	void ReleaseFrom(Allocator* allocator, void* memory, unsigned int size, unsigned int alignment);
	// 0x105B7530 / 0x105B7550: the tracked forms through the allocator in force
	void* AllocateTracked(const char* tag, unsigned int size, unsigned int alignment);
	void ReleaseTracked(void* memory);
}

#endif
