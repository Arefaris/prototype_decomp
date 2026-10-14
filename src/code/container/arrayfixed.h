// container::ArrayFixed<T, N> (class and member names guessed; no RTTI for a template without virtual functions): a
// fixed-capacity array filled from the front over raw storage -- the elements are constructed and destroyed by the
// array -- with the end pointer after the storage. Users: the game object master table (0x1800 entries), the message
// router's lists and the render passes' part filters (pure3d::PassEntries, sixteen 8-byte entries) and light lists
// (eight pure3d::Light pointers). The members are defined in the class, so the compiler inlines them where it likes;
// the engine's out-of-line copies are 0x10766000 / 0x10766040 / 0x10766090 / 0x1076BE40.
#ifndef CONTAINER_ARRAYFIXED_H
#define CONTAINER_ARRAYFIXED_H

#include "code/container/arraydynamic.h"

namespace container
{
	template<class T, int N> class ArrayFixed
	{
	public:
		ArrayFixed()
		{
			end = Data();
		}
		// Copies the elements of other (0x10766040 for pure3d::PassEntry)
		ArrayFixed(const ArrayFixed& other);
		~ArrayFixed()
		{
			Clear();
		}
		// The elements of other over this one's (0x10766090 for pure3d::PassEntry)
		ArrayFixed& operator=(const ArrayFixed& other);
		T* Data()
		{
			return (T*)storage;
		}
		const T* Data() const
		{
			return (const T*)storage;
		}
		T* Begin()
		{
			return Data();
		}
		T* End()
		{
			return end;
		}
		bool IsEmpty() const
		{
			return Data() == end;
		}
		int Size() const
		{
			return end - Data();
		}
		T& operator[](int index)
		{
			return Data()[index];
		}
		bool PushBack(const T& value)
		{
			if (Size() != N)
			{
				Construct(end++, value);
				return true;
			}
			return false;
		}
		void Clear()
		{
			Destroy(Data(), end);
			end = Data();
		}
		void Reset()
		{
			end = Data();
		}

		int storage[N * sizeof(T) / sizeof(int)];
		T* end;
	};

	// Copy-constructs count elements from first into raw storage at dest; answers the end of the copies (the
	// engine's kept copy of the pure3d::PassEntry instance is 0x10766000)
	template<class T> T* ConstructCopiesN(const T* first, unsigned int count, T* dest);

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

	template<class T, int N> ArrayFixed<T, N>::ArrayFixed(const ArrayFixed& other)
	{
		const T* from = other.Data();
		T* to = Data();
		unsigned int count = other.Size();
		while (count != 0)
		{
			count--;
			if (to != 0)
			{
				new (to) T(*from);
			}
			from++;
			to++;
		}
		end = to;
	}

	template<class T, int N> ArrayFixed<T, N>& ArrayFixed<T, N>::operator=(const ArrayFixed& other)
	{
		const T* otherEnd = other.end;
		unsigned int count = otherEnd - other.Data();
		unsigned int size = Size();
		if (count <= size)
		{
			T* to = Data();
			for (const T* from = other.Data(); from != otherEnd; from++)
			{
				*to = *from;
				to++;
			}
			end = to;
		}
		else
		{
			const T* last = other.Data() + size;
			T* to = Data();
			for (const T* from = other.Data(); from != last; from++)
			{
				*to = *from;
				to++;
			}
			end = ConstructCopiesN(last, count - size, end);
		}
		return *this;
	}
}

#endif
