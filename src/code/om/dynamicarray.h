// om::DynamicArray<T, Count> (RTTI: om::DynamicArray<class om::String, unsigned short> and the arrays of the
// engine's reflected classes): a growable array of objects with a 16-bit size and capacity. The memory comes from the
// om allocator (4-byte aligned, tagged with an empty string). Only the members the engine's reflection instances use
// are described.
#ifndef OM_DYNAMICARRAY_H
#define OM_DYNAMICARRAY_H

#include "code/om/allocation.h"
#include <new>

namespace om
{
	template<class T, class Count> class DynamicArray
	{
	public:
		DynamicArray() :
			data(0),
			size(0),
			capacity(0)
		{
		}
		DynamicArray(const DynamicArray& other)
		{
			data = Allocate(other.size);
			capacity = other.size;
			size = other.size;
			CopyElements(data, other.data, other.size);
		}
		~DynamicArray()
		{
			DestroyElements();
			ReleaseElements(data, capacity);
		}
		// 0x105BD670 (the string array's)
		DynamicArray& operator=(const DynamicArray& other)
		{
			if (this != &other)
			{
				DestroyElements();
				ReleaseElements(data, capacity);
				data = Allocate(other.size);
				capacity = other.size;
				size = other.size;
				CopyElements(data, other.data, other.size);
			}
			return *this;
		}

		T& operator[](Count index)
		{
			return data[index];
		}
		// Makes room for one more element at the end and answers its place (the capacity grows by one)
		T& Append()
		{
			Count newSize = size + 1;
			if (newSize > capacity)
			{
				T* elements = Allocate(newSize);
				CopyElements(elements, data, size);
				DestroyElements();
				ReleaseElements(data, capacity);
				data = elements;
				capacity = newSize;
			}
			size = newSize;
			return data[newSize - 1];
		}
		// Takes every element out and gives the memory back
		void Clear()
		{
			DestroyElements();
			ReleaseElements(data, capacity);
			size = 0;
			capacity = 0;
			data = 0;
		}
		// Takes every element out (the memory stays)
		void Empty()
		{
			DestroyElements();
			size = 0;
		}
		// Takes the memory for a number of elements (the array is empty)
		void Reserve(Count count)
		{
			data = Allocate(count);
			capacity = count;
		}

		T* Allocate(Count count)
		{
			return static_cast<T*>(om::Allocate(AllocationTag(), count * sizeof(T), 4));
		}
		void ReleaseElements(T* elements, Count count)
		{
			om::Release(elements, count * sizeof(T), 4);
		}
		void DestroyElements()
		{
			T* element = data;
			if (size > 0)
			{
				unsigned int remaining = size;
				do
				{
					element->~T();
					element++;
					remaining--;
				}
				while (remaining != 0);
			}
		}
		void CopyElements(T* destination, const T* source, Count count)
		{
			for (Count i = 0; i < count; i++)
			{
				if (destination != 0)
				{
					new (destination) T(*source);
				}
				destination++;
				source++;
			}
		}
		OM_ALLOCATION(DynamicArray);

		T* data;  // 0
		Count size;  // 4
		Count capacity;  // 6
	};

	template<class T, class Count> const char* DynamicArray<T, Count>::AllocationTag()
	{
		return "";
	}
}

#endif
