// A growable array over an allocator of a fixed heap: begin / end / capacity, then the (empty) allocator, 16 bytes.
// The stream packages' lists (AllocatorCoreStatic<12,16>) are probably container::ArrayDynamic like the ones in
// arraydynamicstatic.h, but their Allocate is out of line and PushBack answers whether there was room, so this form is
// kept apart under its own name. Member names are guesses.
#ifndef CONTAINER_STATICARRAY_H
#define CONTAINER_STATICARRAY_H

#include "code/container/arraydynamicstatic.h"

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
				Allocator::Free(begin);
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

	// A fixed-size array over an allocator of a fixed heap: begin / end, a third pointer the users leave alone, and
	// no allocator member (12 bytes; probably the same template as the camera director's ArrayDynamic)
	template<class T, class Allocator> class ArrayFixedStatic
	{
	public:
		typedef T Element;

		// count uninitialised elements (an empty array when count is 0 or the allocation fails)
		ArrayFixedStatic(unsigned int count, const Allocator& allocator)
		{
			if (count > 0)
			{
				begin = (T*)Allocator::Alloc(count * sizeof(T));
				if (begin != 0)
				{
					end = begin + count;
					return;
				}
			}
			begin = 0;
			end = 0;
		}
		~ArrayFixedStatic()
		{
			if (begin != 0)
			{
				Allocator::Free(begin);
			}
		}

		T* begin;
		T* end;
		T* capacity;
	};

	template<class T, class Allocator> bool ArrayDynamicStatic<T, Allocator>::Allocate(unsigned int count)
	{
		if (count != 0)
		{
			begin = (T*)Allocator::Alloc(count * sizeof(T));
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
