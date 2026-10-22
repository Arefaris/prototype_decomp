// The reference counted base classes of the om library (RTTI: om::RefCount<Policy>, with the policies
// om::SingleThreadedRefCount and om::ThreadSafeRefCount). The objects that count their users make one vftable
// of their own; the policy only decides how the counter is changed.
#ifndef OM_REFCOUNT_H
#define OM_REFCOUNT_H

namespace om
{
	struct SingleThreadedRefCount
	{
	};

	struct ThreadSafeRefCount
	{
		// 0x105B4C50 / 0x105B4C70 (names guessed): the interlocked change of a counter, and what it came to
		static void AddRef(int* count);
		static int Release(int* count);
	};

	// A reference counted object: the vftable only holds the destructor (the engine's deleting destructor of the
	// single threaded one is 0x10030EA9, of the thread safe one 0x105B5260)
	template<class Policy> class RefCount
	{
	public:
		RefCount() :
			count(0)
		{
		}
		virtual ~RefCount()
		{
		}

		int count;
	};
}

#endif
