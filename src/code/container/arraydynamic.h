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

	// Copies [first, last) to dest (front to back)
	template<class T> inline T* Copy(T* first, T* last, T* dest)
	{
		for (; first != last; ++first, ++dest)
		{
			*dest = *first;
		}
		return dest;
	}

	// A growable array over an AllocatorCoreAligned<16>: begin / end / capacity, then the allocator's heap (probably
	// container::ArrayDynamic with a stateful allocator; names guessed)
	template<class T> class ArrayDynamicHeap
	{
	public:
		ArrayDynamicHeap(unsigned int count, const AllocatorCoreAligned<16>& newAllocator) : allocator(newAllocator)
		{
			if (count != 0)
			{
				begin = (T*)allocator.Alloc(count * sizeof(T));
				if (begin != 0)
				{
					capacity = begin + count;
					end = begin;
					return;
				}
			}
			else
			{
				begin = 0;
			}
			end = 0;
			capacity = 0;
		}
		~ArrayDynamicHeap()
		{
			end = begin;
			if (begin != 0)
			{
				allocator.Free(begin);
			}
		}
		bool Allocate(unsigned int count);
		void Clear();
		T* Find(const T& value)
		{
			T* item = begin;
			while (item != end && *item != value)
			{
				item++;
			}
			return item;
		}
		bool PushBack(const T& value)
		{
			if (end < capacity)
			{
				T* item = end++;
				if (item != 0)
				{
					*item = value;
				}
				return true;
			}
			return false;
		}
		void Erase(T* item)
		{
			Copy(item + 1, end, item);
			end--;
		}

		T* begin;
		T* end;
		T* capacity;
		AllocatorCoreAligned<16> allocator;
	};

	template<class T> bool ArrayDynamicHeap<T>::Allocate(unsigned int count)
	{
		if (count != 0)
		{
			begin = (T*)allocator.Alloc(count * sizeof(T));
			if (begin != 0)
			{
				capacity = begin + count;
				end = begin;
				return true;
			}
		}
		else
		{
			begin = 0;
		}
		end = 0;
		capacity = 0;
		return false;
	}

	template<class T> void ArrayDynamicHeap<T>::Clear()
	{
		end = begin;
		if (begin != 0)
		{
			allocator.Free(begin);
		}
	}
}

#endif
