// container::ArrayDynamic<T, container::AllocatorNew> over operator new[] / delete[]: what the reflected classes'
// element arrays are (RTTI: ArrayDynamic<struct engine::FmvSubtitleManager::SubTitleEnty, struct
// container::AllocatorNew>). It is a partial specialisation of the primary template in arraydynamic.h, whose
// members are the ones the camera director instantiates and differ from these (begin / end / capacity, an
// Allocate that leaves the storage empty, and a Reserve that keeps the old elements); the ones here were read off
// the reflection unit. Member names are guesses.
#ifndef CONTAINER_ARRAYDYNAMICALLOCATORNEW_H
#define CONTAINER_ARRAYDYNAMICALLOCATORNEW_H

#include "code/container/arraycdynamic.h"
#include "code/container/arraydynamicstatic.h"
#include "code/container/arraydynamic.h"
#include "code/content/metatype.h"

namespace container
{
	// How Erase moves the elements down: 1 with a loop of its own (the engine's compiler inlines the assignment of
	// small elements), 0 with a call of AssignRange (larger elements; a class of this kind specialises it), 2 with
	// CopyRange (pointers, whose loop keeps the distance between its two pointers in a register)
	template<class T> struct ArrayEraseInline
	{
		enum
		{
			value = 1
		};
	};
	template<class T> struct ArrayEraseInline<T*>
	{
		enum
		{
			value = 2
		};
	};

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
		// Another array's elements, in room for as many as it has room for
		ArrayDynamic(const ArrayDynamic& other)
		{
			unsigned int count = other.Capacity();
			if (count != 0)
			{
				begin = (T*)operator new[](count * sizeof(T));
				if (begin != 0)
				{
					end = begin;
					capacity = begin + count;
					end = UninitializedCopyN(other.begin, other.Size(), begin);
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
		ArrayDynamic& operator=(const ArrayDynamic& other)
		{
			if (begin == 0)
			{
				if (Create(other.Capacity()))
				{
					end = ConstructCopiesN(other.begin, other.Size(), begin);
				}
			}
			else
			{
				unsigned int count = other.Size();
				unsigned int size = Size();
				if (count <= size)
				{
					end = AssignRange(other.begin, other.end, begin);
				}
				else if (count <= Capacity())
				{
					AssignRange(other.begin, other.begin + size, begin);
					end = ConstructCopiesN(other.begin + size, count - size, end);
				}
				else
				{
					end = begin;
				}
			}
			return *this;
		}
		~ArrayDynamic()
		{
			Destroy(begin, end);
			end = begin;
			if (begin != 0)
			{
				operator delete[](begin);
			}
		}
		T* Begin()
		{
			return begin;
		}
		T* End()
		{
			return end;
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
			Destroy(begin, end);
			end = begin;
		}
		void Free()
		{
			if (begin != 0)
			{
				Destroy(begin, end);
				operator delete[](begin);
			}
			capacity = 0;
			end = 0;
			begin = 0;
		}
		// Moves the elements behind position down over it and answers position
		T* Erase(T* position)
		{
			if (ArrayEraseInline<T>::value == 1)
			{
				T* last = end;
				for (T* next = position + 1; next != last; next++)
				{
					next[-1] = *next;
				}
			}
			else if (ArrayEraseInline<T>::value == 2)
			{
				CopyRange(position + 1, end, position);
			}
			else
			{
				AssignRange(position + 1, end, position);
			}
			end--;
			Destroy(end);
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
				Destroy(from);
			}
		}
		// Removes [first, last) by moving the elements behind it down (they are not destroyed)
		void Erase(T* first, T* last)
		{
			end = AssignRange(last, end, first);
		}
		// Grows by copies of value or shrinks to count elements
		void Resize(unsigned int count, const T& value)
		{
			if (begin == 0)
			{
				Create(count);
			}
			unsigned int size = Size();
			if (size < count)
			{
				Insert(end, count - size, value);
			}
			else if (count < size)
			{
				Erase(begin + count, end);
			}
		}
		void Resize(unsigned int count)
		{
			T blank;
			Resize(count, blank);
		}
		// Makes room for count elements, keeping the ones that fit
		void Reserve(int count)
		{
			int size = end - begin;
			if (count != capacity - begin)
			{
				int keep = count < size ? count : size;
				T* storage = (T*)operator new[](count * sizeof(T));
				if (storage == 0)
				{
					keep = 0;
					count = 0;
				}
				else
				{
					for (int i = 0; i < keep; i++)
					{
						ConstructCopyAt(storage + i, begin[i]);
					}
				}
				if (begin != 0)
				{
					Destroy(begin, end);
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
		// The same for one copy of value; answers position, or the old end when it does not fit
		T* Insert(T* position, const T& value)
		{
			if (end + 1 <= capacity)
			{
				ShiftUp(position, 1);
				if (position != 0)
				{
					new (position) T(value);
				}
				return position;
			}
			return end;
		}

		T* begin;
		T* end;
		T* capacity;
		AllocatorNew allocator;
	};
}

namespace content
{
	// The element access of an array of pointers for its meta type: the engine's copy has the insertion and the
	// removal expanded with loops of their own, and keeps the default element (a null pointer) in a static of the
	// helper (Default)
	template<class P> class ArrayDynamicHelper<container::ArrayDynamic<P*, container::AllocatorNew> >
		: public ArrayDynamicHelperBase
	{
	public:
		typedef container::ArrayDynamic<P*, container::AllocatorNew> A;
		typedef P* T;

		static T& Default()
		{
			static T sDefault;
			return sDefault;
		}

		virtual int Size(void* array)
		{
			return ((A*)array)->Size();
		}
		virtual void* Get(void* array, int index)
		{
			return &(*(A*)array)[index];
		}
		virtual void* GetConst(void* array, int index)
		{
			return &(*(A*)array)[index];
		}
		virtual void Insert(void* array, int index, int unused)
		{
			A* a = (A*)array;
			if (a->Size() >= a->Capacity())
			{
				a->Reserve(a->Size() + 1);
			}
			T* position = a->begin + index;
			T* from = a->end;
			if (from + 1 <= a->capacity)
			{
				T* to = from + 1;
				a->end = to;
				while (from != position)
				{
					from--;
					to--;
					if (to != 0)
					{
						*to = *from;
					}
				}
				if (position != 0)
				{
					*position = Default();
				}
			}
		}
		virtual void Erase(void* array, int index, int unused)
		{
			A* a = (A*)array;
			T* position = a->begin + index;
			T* last = a->end;
			T* destination = position;
			for (T* source = position + 1; source != last; source++, destination++)
			{
				*destination = *source;
			}
			a->end--;
		}
		virtual int Capacity(void* array)
		{
			return ((A*)array)->Capacity();
		}
		virtual void Expand(void* array, unsigned int count)
		{
			A* a = (A*)array;
			if (a->Capacity() == 0)
			{
				a->Allocate(count);
			}
			else if (count + a->Size() > a->Capacity())
			{
				a->Reserve(count + a->Size());
			}
		}
	};
}

#endif
