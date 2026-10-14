// A growable array of begin / end / capacity pointers over operator new[] / delete[]. The RTTI calls the instantiation
// the supporting limb unit reflects container::ArrayDynamic<T, AllocatorNew>, but its members differ from the
// container::ArrayDynamic the camera director instantiates (two pointers, heap 0x79), so it is kept apart under its
// own name here. Member names are guesses.
#ifndef CONTAINER_ARRAYDYNAMICNEW_H
#define CONTAINER_ARRAYDYNAMICNEW_H

#include "code/container/arraycdynamic.h"
#include "code/content/metatype.h"

namespace container
{
	template<class T> class ArrayDynamicNew
	{
	public:
		typedef T Element;

		ArrayDynamicNew()
		{
			begin = 0;
			end = 0;
			capacity = 0;
		}
		~ArrayDynamicNew()
		{
			end = begin;
			if (begin != 0)
			{
				delete[] begin;
			}
		}
		unsigned int Size() const
		{
			return end - begin;
		}
		void Clear()
		{
			end = begin;
		}
		bool IsFull() const
		{
			return end == capacity;
		}
		// Appends a copy of value when there is room
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
		// Room for one more element at the end (uninitialised), or null when the array is full
		T* Grow()
		{
			if (end < capacity)
			{
				return end++;
			}
			return 0;
		}
		T& operator[](int index)
		{
			return begin[index];
		}
		const T& operator[](int index) const
		{
			return begin[index];
		}
		T* Begin()
		{
			return begin;
		}
		unsigned int Capacity() const
		{
			return capacity - begin;
		}
		// Room for count elements; false (and an empty array) when count is 0 or the allocation fails
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
		void Erase(T* position)
		{
			for (T* next = position + 1; next != end; next++)
			{
				next[-1] = *next;
			}
			end--;
		}
		void Free()
		{
			if (begin != 0)
			{
				delete[] begin;
			}
			capacity = 0;
			end = 0;
			begin = 0;
		}
		void Reserve(int count)
		{
			int size = end - begin;
			if (count != capacity - begin)
			{
				int keep = count < size ? count : size;
				T* storage = new T[count];
				if (storage == 0)
				{
					keep = 0;
					count = 0;
				}
				else
				{
					for (int i = 0; i < keep; i++)
					{
						ConstructAt(storage + i, begin[i]);
					}
				}
				if (begin != 0)
				{
					delete[] begin;
				}
				begin = storage;
				end = storage + keep;
				capacity = storage + count;
			}
		}
		// Inserts count copies of value before position when they fit
		void Insert(T* position, unsigned int count, const T& value)
		{
			T* last = end + count;
			if (last <= capacity)
			{
				T* from = end;
				end = last;
				while (from != position)
				{
					from--;
					last--;
					ConstructAt(last, *from);
				}
				UninitializedFill(position, count, value);
			}
		}
		void Insert(T* position, const T& value)
		{
			T* last = end + 1;
			if (last <= capacity)
			{
				T* from = end;
				end = last;
				while (from != position)
				{
					from--;
					last--;
					ConstructAt(last, *from);
				}
				ConstructAt(position, value);
			}
		}

		T* begin;
		T* end;
		T* capacity;
	};
}

namespace content
{
	template<class T> class ArrayDynamicHelper<container::ArrayDynamicNew<T> > : public ArrayDynamicHelperBase
	{
	public:
		typedef container::ArrayDynamicNew<T> A;

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
