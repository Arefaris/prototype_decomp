// om::FixedArray<T, N> (RTTI om::FixedArray<unsigned int,8>): an array of N values that is reflected as a whole (the
// description writes it as a list of items). The values are copied one by one.
#ifndef OM_FIXEDARRAY_H
#define OM_FIXEDARRAY_H

#include "code/om/allocation.h"

namespace om
{
	template<class T, int N> class FixedArray
	{
	public:
		FixedArray()
		{
		}
		// Every item gets the value
		FixedArray(const T& value)
		{
			for (int i = 0; i < N; ++i)
			{
				items[i] = value;
			}
		}
		FixedArray(const FixedArray& other)
		{
			for (int i = 0; i < N; ++i)
			{
				items[i] = other.items[i];
			}
		}
		FixedArray& operator=(const FixedArray& other)
		{
			for (int i = 0; i < N; ++i)
			{
				items[i] = other.items[i];
			}
			return *this;
		}
		T& operator[](int index)
		{
			return items[index];
		}
		int GetSize() const
		{
			return N;
		}
		OM_ALLOCATION(FixedArray);

		T items[N];
	};

	template<class T, int N> const char* FixedArray<T, N>::AllocationTag()
	{
		return "";
	}
}

#endif
