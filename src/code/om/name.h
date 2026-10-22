// om::Name<Key>: the 64-bit key of a name (RTTI names om::Name<struct om::CaseSensitive64BitKey>); the objects that
// hold one are laid out for 8-byte alignment.
#ifndef OM_NAME_H
#define OM_NAME_H

namespace om
{
	struct CaseSensitive64BitKey
	{
	};

	template<class Key> class Name
	{
	public:
		Name() :
			key(0)
		{
		}

		unsigned __int64 key;
	};
}

#endif
