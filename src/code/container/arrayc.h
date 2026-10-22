// container::ArrayC<T, N> (RTTI: the content::ArrayCHelper instantiations name it): a plain array of N elements inside
// an object, as the meta system's fixed arrays see it. Member names guessed.
#ifndef CONTAINER_ARRAYC_H
#define CONTAINER_ARRAYC_H

namespace container
{
	template<class T, int N> class ArrayC
	{
	public:
		T& operator[](int index)
		{
			return items[index];
		}

		T items[N];
	};
}

#endif
