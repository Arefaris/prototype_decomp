// A growable array over an allocator of a fixed heap: begin / end / capacity, then the (empty) allocator, 16 bytes
// (the stream packages' lists use AllocatorCoreStatic<12,16>; the RTTI calls such arrays
// container::ArrayDynamic<T, struct container::AllocatorCoreStatic<12,16> >, but the camera director's ArrayDynamic
// has different members, so this form is kept apart under its own name). Member names are guesses.
#ifndef CONTAINER_ARRAYDYNAMICSTATIC_H
#define CONTAINER_ARRAYDYNAMICSTATIC_H

#include "code/container/map.h"

namespace container
{
	template<class T, class Allocator> class ArrayDynamicStatic
	{
	public:
		typedef T Element;

		ArrayDynamicStatic(unsigned int count, const Allocator& newAllocator)
		{
			Allocate(count);
		}
		~ArrayDynamicStatic()
		{
			end = begin;
			if (begin != 0)
			{
				allocator.Free(begin);
			}
		}
		bool Allocate(unsigned int count);
		T* Begin() const
		{
			return begin;
		}
		T* End() const
		{
			return end;
		}
		bool IsEmpty() const
		{
			return begin == end;
		}
		int Size() const
		{
			return end - begin;
		}
		T& operator[](int index)
		{
			return begin[index];
		}
		const T& operator[](int index) const
		{
			return begin[index];
		}
		void Reset()
		{
			end = begin;
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
		T* Find(const T& value)
		{
			T* item = begin;
			while (item != end && *item != value)
			{
				item++;
			}
			return item;
		}
		// Removes item by moving the last element into its place
		void EraseFast(T* item)
		{
			--end;
			if (item < end)
			{
				*item = *end;
			}
		}

		T* begin;
		T* end;
		T* capacity;
		Allocator allocator;
	};

	template<class T, class Allocator> bool ArrayDynamicStatic<T, Allocator>::Allocate(unsigned int count)
	{
		if (count != 0)
		{
			begin = (T*)allocator.Alloc(count * sizeof(T), 16);
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
}

#endif
