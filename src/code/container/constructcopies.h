// container::ConstructCopiesN: copy-constructs count elements from first into raw storage at dest and answers the end
// of the copies (the engine keeps instances of it, e.g. 0x10766000 for pure3d::PassEntry and 0x10835780 for
// math::Plane)
#ifndef CONTAINER_CONSTRUCTCOPIES_H
#define CONTAINER_CONSTRUCTCOPIES_H

#include <new>

namespace container
{
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
}

#endif
