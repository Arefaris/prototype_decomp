// container::ArrayDynamic<T, Allocator> (RTTI names instantiations such as
// container::ArrayDynamic<class engine::camera::Camera *, struct container::AllocatorNew>): begin / end / end of
// storage pointers. Only the members the camera Director instantiates are reconstructed; their names are guesses.
// AllocatorNew allocates 16-byte aligned blocks from heap 0x79 through the core heap functions.
#ifndef CONTAINER_ARRAYDYNAMIC_H
#define CONTAINER_ARRAYDYNAMIC_H

#include "code/core/heap.h"

namespace container
{
	// Member functions of an empty object (the engine keeps them as __thiscall copies, 0x107DDBF0 / 0x107DDC10)
	struct AllocatorNew
	{
		void Free(void* block)
		{
			core::HeapFreeAligned(0x79, block);
		}
		void* Alloc(unsigned int size, unsigned int align)
		{
			return core::HeapAllocAligned(0x79, size, align);
		}
	};

	// The allocator of a heap chosen at run time, Align-byte aligned (RTTI names AllocatorCoreAligned<16>)
	template<int Align> struct AllocatorCoreAligned
	{
		void* Alloc(unsigned int size) const
		{
			return core::HeapAllocAligned(heap, size, Align);
		}
		void Free(void* block) const
		{
			core::HeapFreeAligned(heap, block);
		}

		int heap;
	};

	template<class T, class Allocator> class ArrayDynamic
	{
	public:
		T* begin;
		T* end;
		T* capacity;

		// count uninitialised elements (an empty array when count is 0 or the allocation fails); capacity is not set
		explicit ArrayDynamic(unsigned int count)
		{
			if (count > 0)
			{
				begin = (T*)Allocator().Alloc(count * sizeof(T), 16);
				if (begin != 0)
				{
					end = begin + count;
					return;
				}
			}
			begin = 0;
			end = 0;
		}
		~ArrayDynamic()
		{
			if (begin != 0)
			{
				Allocator().Free(begin);
			}
		}
		int Size() const
		{
			return (int)(end - begin);
		}
		T& operator[](int index)
		{
			return begin[index];
		}
		const T& operator[](int index) const
		{
			return begin[index];
		}
		// Replaces the storage with count uninitialised elements; false (and an empty array) when count is 0 or the
		// allocation fails
		bool Allocate(unsigned int count)
		{
			if (count > 0)
			{
				begin = (T*)Allocator().Alloc(count * sizeof(T), 16);
				if (begin != 0)
				{
					end = begin + count;
					return true;
				}
			}
			begin = 0;
			end = 0;
			return false;
		}
		// Allocate returning the array; the second argument is unused (its meaning is unknown)
		ArrayDynamic* Reserve(unsigned int count, int unused)
		{
			if (count > 0)
			{
				begin = (T*)Allocator().Alloc(count * sizeof(T), 16);
				if (begin != 0)
				{
					end = begin + count;
					return this;
				}
			}
			begin = 0;
			end = 0;
			return this;
		}
		void Clear()
		{
			if (begin != 0)
			{
				Allocator().Free(begin);
			}
			begin = 0;
			end = 0;
		}
	};
}

#endif
