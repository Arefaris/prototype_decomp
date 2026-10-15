// container::ArrayDynamic<T, container::AllocatorNew> over operator new[] / delete[]: what the reflected classes'
// element arrays are (RTTI: ArrayDynamic<struct engine::FmvSubtitleManager::SubTitleEnty, struct
// container::AllocatorNew>). It is a partial specialisation of the primary template in arraydynamic.h, whose
// members are the ones the camera director instantiates and differ from these (begin / end / capacity, an
// Allocate that leaves the storage empty, and a Reserve that keeps the old elements); the ones here were read off
// the reflection unit. Member names are guesses.
#ifndef CONTAINER_ARRAYDYNAMICALLOCATORNEW_H
#define CONTAINER_ARRAYDYNAMICALLOCATORNEW_H

#include "code/container/arraycdynamic.h"
#include "code/container/arraydynamic.h"
#include "code/content/metatype.h"

namespace container
{
	template<class T> class ArrayDynamic<T, AllocatorNew>
	{
	public:
		typedef T Element;

		ArrayDynamic()
		{
			begin = 0;
			end = 0;
			capacity = 0;
		}
		unsigned int Size() const
		{
			return end - begin;
		}
		unsigned int Capacity() const
		{
			return capacity - begin;
		}
		T& operator[](int index)
		{
			return begin[index];
		}
		const T& operator[](int index) const
		{
			return begin[index];
		}
		// Room for count uninitialised elements; false (and an empty array) when count is 0 or the allocation fails
		bool Create(unsigned int count)
		{
			if (count != 0)
			{
				begin = (T*)operator new[](count * sizeof(T));
				if (begin != 0)
				{
					end = begin;
					capacity = begin + count;
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
		// The same, leaving the array empty
		void Allocate(unsigned int count)
		{
			if (count != 0)
			{
				begin = (T*)operator new[](count * sizeof(T));
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
		// Drops the elements (the storage stays)
		void Clear()
		{
			end = begin;
		}
		void Free()
		{
			if (begin != 0)
			{
				operator delete[](begin);
			}
			capacity = 0;
			end = 0;
			begin = 0;
		}
		// Moves the elements behind position down over it and answers position
		T* Erase(T* position)
		{
			T* last = end;
			for (T* next = position + 1; next != last; next++)
			{
				next[-1] = *next;
			}
			end--;
			return position;
		}
		// Moves [position, end) up by count elements (copy-constructing them backwards)
		void ShiftUp(T* position, int count)
		{
			T* from = end;
			end = from + count;
			T* to = end;
			while (from != position)
			{
				from--;
				to--;
				ConstructCopyAt(to, *from);
			}
		}
		// Makes room for count elements, keeping the ones that fit
		void Reserve(int count)
		{
			int size = end - begin;
			if (count != capacity - begin)
			{
				int keep = count < size ? count : size;
				T* storage = (T*)operator new[](count * sizeof(T));
				int i = 0;
				if (storage == 0)
				{
					keep = 0;
					count = 0;
				}
				else
				{
					for (; i < keep; i++)
					{
						ConstructCopyAt(storage + i, begin[i]);
					}
				}
				if (begin != 0)
				{
					operator delete[](begin);
				}
				end = storage + keep;
				begin = storage;
				capacity = storage + count;
			}
		}
		// Inserts count copies of value before position when they fit; answers position, or the old end when they
		// do not
		T* Insert(T* position, unsigned int count, const T& value)
		{
			T* result = end;
			if (end + count <= capacity)
			{
				ShiftUp(position, count);
				ConstructFill(position, count, value);
				result = position;
			}
			return result;
		}
		// The same for one copy of value; answers position
		T* Insert(T* position, const T& value)
		{
			if (end + 1 <= capacity)
			{
				ShiftUp(position, 1);
				ConstructCopyAt(position, value);
			}
			return position;
		}

		T* begin;
		T* end;
		T* capacity;
	};
}

#endif
