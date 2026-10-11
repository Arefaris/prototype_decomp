// container::ArrayCDynamic<T, N> (RTTI names instantiations such as
// container::ArrayCDynamic<struct engine::SupportingLimbDefinition::SmoothingVelocityMap::Entry,3>): up to N elements
// stored inline, followed by the end pointer. Member names are guesses; the units that use it instantiate it
// explicitly, so every member has a copy there.
#ifndef CONTAINER_ARRAYCDYNAMIC_H
#define CONTAINER_ARRAYCDYNAMIC_H

#include "code/container/arraydynamic.h"
#include <new>

namespace container
{
	// Copies [first, last) to dest (front to back)
	template<class T> void CopyRange(T* first, T* last, T* dest)
	{
		for (; first != last; first++, dest++)
		{
			*dest = *first;
		}
	}

	// Copy-constructs value at p (null: nothing)
	template<class T> void ConstructAt(T* p, const T& value)
	{
		if (p != 0)
		{
			*p = value;
		}
	}

	// Copy-constructs count copies of value into raw storage at dest
	template<class T> void UninitializedFill(T* dest, unsigned int count, const T& value)
	{
		while (count != 0)
		{
			count--;
			if (dest != 0)
			{
				*dest = value;
			}
			dest++;
		}
	}

	template<class T, int N> class ArrayCDynamic
	{
	public:
		typedef T Element;

		T* Items()
		{
			return (T*)storage;
		}
		const T* Items() const
		{
			return (const T*)storage;
		}

		ArrayCDynamic()
		{
			end = Items();
		}
		~ArrayCDynamic()
		{
			end = Items();
		}
		void Clear()
		{
			end = Items();
		}
		T* Begin()
		{
			return Items();
		}
		const T* Begin() const
		{
			return Items();
		}
		T* End()
		{
			return end;
		}
		const T* End() const
		{
			return end;
		}
		bool IsEmpty() const
		{
			return Items() == end;
		}
		int Size() const
		{
			return end - Items();
		}
		T& operator[](int index)
		{
			return Items()[index];
		}
		const T& operator[](int index) const
		{
			return Items()[index];
		}
		// Moves [position, end) up by count elements
		void ShiftUp(T* position, int count)
		{
			T* from = end;
			T* to = end + count;
			end = to;
			while (from != position)
			{
				from--;
				to--;
				ConstructAt(to, *from);
			}
		}
		// Inserts count copies of value before position; answers position, or the end when they do not fit
		T* Insert(T* position, unsigned int count, const T& value);
		T* Insert(T* position, const T& value)
		{
			return Insert(position, 1, value);
		}
		void Erase(T* position)
		{
			T* last = end;
			T* from = position + 1;
			if (from != last)
			{
				T* to = from - 1;
				do
				{
					*to = *from;
					from++;
					to++;
				}
				while (from != last);
			}
			end--;
		}

		// Raw storage: the elements are constructed when inserted
		int storage[(N * sizeof(T) + 3) / 4];
		T* end;
	};

	template<class T, int N> T* ArrayCDynamic<T, N>::Insert(T* position, unsigned int count, const T& value)
	{
		T* last = end;
		if ((unsigned int)(Size() + count) < N + 1)
		{
			ShiftUp(position, count);
			UninitializedFill(position, count, value);
			last = position;
		}
		return last;
	}
}

#endif
