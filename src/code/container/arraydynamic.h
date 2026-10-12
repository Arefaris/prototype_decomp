// container::ArrayDynamic<T, Allocator> (RTTI names instantiations such as
// container::ArrayDynamic<class engine::camera::Camera *, struct container::AllocatorNew>): begin / end / end of
// storage pointers. Only the members the camera Director instantiates are reconstructed; their names are guesses.
// AllocatorNew allocates 16-byte aligned blocks from heap 0x79 through the core heap functions.
#ifndef CONTAINER_ARRAYDYNAMIC_H
#define CONTAINER_ARRAYDYNAMIC_H

#include "code/core/heap.h"
#include <new>

namespace container
{
	template<class T> inline void Swap(T& a, T& b)
	{
		T t = a;
		a = b;
		b = t;
	}

	template<class T> inline void Construct(T* p, const T& value)
	{
		new (p) T(value);
	}

	template<class T> inline void Destroy(T* p)
	{
		p->~T();
	}

	template<class T> inline void Destroy(T* first, T* last)
	{
		for (; first != last; ++first)
		{
			Destroy(first);
		}
	}

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
		// Heap 1 by default
		AllocatorCoreAligned()
		{
			heap = 1;
		}
		explicit AllocatorCoreAligned(int newHeap)
		{
			heap = newHeap;
		}

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
		typedef T Element;

		ArrayDynamicHeap()
		{
			begin = 0;
			end = 0;
			capacity = 0;
		}
		ArrayDynamicHeap(unsigned int count, const AllocatorCoreAligned<16>& newAllocator) : allocator(newAllocator)
		{
			Allocate(count);
		}
		ArrayDynamicHeap(T* first, T* last, const AllocatorCoreAligned<16>& newAllocator);
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
					Construct(item, value);
				}
				return true;
			}
			return false;
		}
		unsigned int Size() const
		{
			return end - begin;
		}
		unsigned int Capacity() const
		{
			return capacity - begin;
		}
		// Room for one more element at the end (uninitialised), or null when the array is full
		T* Grow()
		{
			if (end < capacity)
			{
				return end++;
			}
			return 0;
		}
		bool IsEmpty() const
		{
			return begin == end;
		}
		void Reset()
		{
			end = begin;
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
		void Reserve(int count);
		void Swap(ArrayDynamicHeap& other)
		{
			container::Swap(begin, other.begin);
			container::Swap(end, other.end);
			container::Swap(capacity, other.capacity);
			container::Swap(allocator.heap, other.allocator.heap);
		}
		// Moves [position, end) up by count elements (copy-constructing them backwards)
		void ShiftUp(T* position, int count)
		{
			T* source = end;
			end += count;
			T* dest = end;
			while (source != position)
			{
				--source;
				--dest;
				Construct(dest, *source);
			}
		}
		T* Insert(T* position, const T& value)
		{
			if (end + 1 > capacity)
			{
				return end;
			}
			ShiftUp(position, 1);
			Construct(position, value);
			return position;
		}
		T* Erase(T* item)
		{
			Copy(item + 1, end, item);
			end--;
			return item;
		}

		T* begin;
		T* end;
		T* capacity;
		AllocatorCoreAligned<16> allocator;
	};

	template<class T> inline bool ArrayDynamicHeap<T>::Allocate(unsigned int count)
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

	template<class T> void ArrayDynamicHeap<T>::Reserve(int count)
	{
		int size = end - begin;
		if (count != capacity - begin)
		{
			int keep = count < size ? count : size;
			T* storage = (T*)allocator.Alloc(count * sizeof(T));
			if (storage == 0)
			{
				keep = 0;
				count = 0;
			}
			else
			{
				for (int i = 0; i < keep; i++)
				{
					Construct(storage + i, begin[i]);
				}
			}
			if (begin != 0)
			{
				allocator.Free(begin);
			}
			begin = storage;
			end = storage + keep;
			capacity = storage + count;
		}
	}

	// The iterator category tag of pointers
	struct RandomAccessTag
	{
		RandomAccessTag()
		{
		}
	};

	// The number of elements of [first, last) (calls, not inlined: templates without inline)
	template<class T> unsigned int DistanceImpl(T* first, T* last, RandomAccessTag tag)
	{
		return last - first;
	}

	template<class T> unsigned int Distance(T* first, T* last)
	{
		return DistanceImpl(first, last, RandomAccessTag());
	}

	// UninitializedCopy's inline twin (the range constructor inlines its copy loop)
	template<class T> inline T* ConstructCopies(T* first, unsigned int count, T* dest)
	{
		while (count != 0)
		{
			count--;
			Construct(dest, *first);
			first++;
			dest++;
		}
		return dest;
	}

	// A copy of [first, last) in storage of exactly that size
	template<class T> ArrayDynamicHeap<T>::ArrayDynamicHeap(T* first, T* last, const AllocatorCoreAligned<16>& newAllocator)
		: allocator(newAllocator)
	{
		unsigned int count = Distance(first, last);
		if (Allocate(count))
		{
			end = ConstructCopies(first, count, begin);
		}
	}

	// Copy-constructs count elements of first into raw storage at dest; answers the end of the copies
	template<class T> T* UninitializedCopy(T* first, unsigned int count, T* dest)
	{
		while (count != 0)
		{
			count--;
			Construct(dest, *first);
			first++;
			dest++;
		}
		return dest;
	}

	// Moves the elements of array into heap, with no spare capacity
	template<class T> void Compact(ArrayDynamicHeap<T>& array, int heap)
	{
		T* old = array.begin;
		unsigned int count = Distance(old, array.end);
		T* storage;
		T* storageEnd;
		T* storageCapacity;
		if (count != 0)
		{
			storage = (T*)core::HeapAllocAligned(heap, count * sizeof(T), 16);
			if (storage != 0)
			{
				storageCapacity = storage + count;
				storageEnd = UninitializedCopy(old, count, storage);
			}
			else
			{
				storageEnd = 0;
				storageCapacity = 0;
			}
		}
		else
		{
			storage = 0;
			storageEnd = 0;
			storageCapacity = 0;
		}
		T* previous = array.begin;
		array.begin = storage;
		array.end = storageEnd;
		array.capacity = storageCapacity;
		int previousHeap = array.allocator.heap;
		array.allocator.heap = heap;
		if (previous != 0)
		{
			core::HeapFreeAligned(previousHeap, previous);
		}
	}

	// Compact through a copy: the array takes over an exact-size copy in heap and the copy frees the old storage
	template<class T> void CompactSwap(ArrayDynamicHeap<T>& array, int heap)
	{
		ArrayDynamicHeap<T> copy(array.begin, array.end, AllocatorCoreAligned<16>(heap));
		copy.Swap(array);
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
