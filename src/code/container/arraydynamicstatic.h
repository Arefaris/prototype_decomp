// container::ArrayDynamic over container::AllocatorCoreStatic<Heap, Align> (RTTI: ArrayDynamic<class math::Plane,
// struct container::AllocatorCoreStatic<12,16> > and others): begin / end / capacity pointers and the (empty)
// allocator, 16 bytes. Its members differ from the instantiations the camera director uses (code/container/
// arraydynamic.h), so this allocator gets a partial specialisation of its own; the names are guesses.
#ifndef CONTAINER_ARRAYDYNAMICSTATIC_H
#define CONTAINER_ARRAYDYNAMICSTATIC_H

#include "code/container/arraydynamic.h"
#include "code/content/metatype.h"

namespace container
{
	// Allocates from the heap fixed by the template argument, Align-byte aligned
	template<int Heap, int Align> struct AllocatorCoreStatic
	{
		static void* Alloc(unsigned int size)
		{
			return core::HeapAllocAligned(Heap, size, Align);
		}
		static void Free(void* block)
		{
			core::HeapFreeAligned(Heap, block);
		}
	};

	// Copy-constructs count elements from first into raw storage at dest; answers the end of the copies
	template<class T> T* ConstructCopiesN(const T* first, unsigned int count, T* dest)
	{
		while (count != 0)
		{
			count--;
			if (dest != 0)
			{
				new (dest) T(*first);
			}
			first++;
			dest++;
		}
		return dest;
	}

	// Assigns [first, last) to dest; answers the end of the copies
	template<class T> T* AssignRange(const T* first, const T* last, T* dest)
	{
		for (; first != last; first++, dest++)
		{
			*dest = *first;
		}
		return dest;
	}

	// The same as ConstructCopiesN under another name (the engine keeps two identical instances)
	template<class T> T* UninitializedCopyN(const T* first, unsigned int count, T* dest)
	{
		while (count != 0)
		{
			count--;
			if (dest != 0)
			{
				new (dest) T(*first);
			}
			first++;
			dest++;
		}
		return dest;
	}

	// Copy-constructs count copies of value into raw storage at dest; answers the end
	template<class T> T* ConstructFill(T* dest, unsigned int count, const T& value)
	{
		while (count != 0)
		{
			count--;
			if (dest != 0)
			{
				new (dest) T(value);
			}
			dest++;
		}
		return dest;
	}

	// Copy-constructs value at p (null: nothing)
	template<class T> inline void ConstructCopyAt(T* p, const T& value)
	{
		if (p != 0)
		{
			new (p) T(value);
		}
	}

	template<class T, int Heap, int Align> class ArrayDynamic<T, AllocatorCoreStatic<Heap, Align> >
	{
	public:
		typedef T Element;
		typedef AllocatorCoreStatic<Heap, Align> Allocator;

		ArrayDynamic()
		{
			begin = 0;
			end = 0;
			capacity = 0;
		}
		// Room for count elements (empty when the allocation fails)
		explicit ArrayDynamic(unsigned int count)
		{
			Create(count);
		}
		ArrayDynamic(unsigned int count, const Allocator& newAllocator)
		{
			Create(count);
		}
		ArrayDynamic(const ArrayDynamic& other);
		~ArrayDynamic()
		{
			Destroy(begin, end);
			end = begin;
			if (begin != 0)
			{
				Allocator::Free(begin);
			}
		}
		ArrayDynamic& operator=(const ArrayDynamic& other);

		unsigned int Size() const
		{
			return end - begin;
		}
		bool IsEmpty() const
		{
			return begin == end;
		}
		bool IsFull() const
		{
			return end == capacity;
		}
		unsigned int Capacity() const
		{
			return capacity - begin;
		}
		T* Begin()
		{
			return begin;
		}
		T* End()
		{
			return end;
		}
		T& operator[](int index)
		{
			return begin[index];
		}
		const T& operator[](int index) const
		{
			return begin[index];
		}
		// Room for count elements; false (and an empty array) when count is 0 or the allocation fails
		bool Create(unsigned int count)
		{
			if (count != 0)
			{
				begin = (T*)Allocator::Alloc(count * sizeof(T));
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
		void Allocate(unsigned int count)
		{
			if (count != 0)
			{
				begin = (T*)Allocator::Alloc(count * sizeof(T));
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
		// Appends value when there is room
		void PushBack(const T& value)
		{
			if (end < capacity)
			{
				T* p = end;
				end = p + 1;
				ConstructCopyAt(p, value);
			}
		}
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
				Allocator::Free(begin);
			}
			capacity = 0;
			end = 0;
			begin = 0;
		}
		T* Erase(T* position)
		{
			AssignRange(position + 1, end, position);
			end--;
			Destroy(end);
			return position;
		}
		// Moves [position, end) up by count elements (the vacated elements are destroyed)
		void ShiftUp(T* position, int count)
		{
			T* from = end;
			T* to = end + count;
			end = to;
			while (from != position)
			{
				from--;
				to--;
				ConstructCopyAt(to, *from);
				Destroy(from);
			}
		}
		void Reserve(int count);
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
		Allocator allocator;
	};

	template<class T, int Heap, int Align>
	ArrayDynamic<T, AllocatorCoreStatic<Heap, Align> >::ArrayDynamic(const ArrayDynamic& other)
	{
		unsigned int count = other.Capacity();
		if (count != 0)
		{
			begin = (T*)Allocator::Alloc(count * sizeof(T));
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

	template<class T, int Heap, int Align> ArrayDynamic<T, AllocatorCoreStatic<Heap, Align> >&
	ArrayDynamic<T, AllocatorCoreStatic<Heap, Align> >::operator=(const ArrayDynamic& other)
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

	template<class T, int Heap, int Align> void ArrayDynamic<T, AllocatorCoreStatic<Heap, Align> >::Reserve(int count)
	{
		int size = end - begin;
		if (count != capacity - begin)
		{
			int keep = count < size ? count : size;
			T* storage = (T*)Allocator::Alloc(count * sizeof(T));
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
				Destroy(begin, end);
				Allocator::Free(begin);
			}
			begin = storage;
			end = storage + keep;
			capacity = storage + count;
		}
	}
}

namespace content
{
	template<class T, int Heap, int Align>
	class ArrayDynamicHelper<container::ArrayDynamic<T, container::AllocatorCoreStatic<Heap, Align> > >
		: public ArrayDynamicHelperBase
	{
	public:
		typedef container::ArrayDynamic<T, container::AllocatorCoreStatic<Heap, Align> > A;

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
			a->Insert(a->Begin() + index, Default());
		}
		virtual void Erase(void* array, int index, int unused)
		{
			A* a = (A*)array;
			a->Erase(a->Begin() + index);
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
