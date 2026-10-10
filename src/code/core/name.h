// core::Name<Key>: an 8-byte name handle, two 32-bit words (the RTTI names core::Name<struct core::CaseSensitiveKey>;
// core::Hash64 is the engine's string hash, so this is probably its 64-bit result, but the users lay it out with
// 4-byte alignment). Only what the engine's users need so far: it is passed by value through a user-defined copy
// constructor (0x1005E500) and compared with operator== (0x10061F10), both in another unit; the destructor is
// user-declared but empty (its users keep the compiler's "constructed" flag for temporaries without calling anything).
#ifndef CORE_NAME_H
#define CORE_NAME_H

namespace core
{
	struct CaseSensitiveKey
	{
	};

	template<class Key> class Name
	{
	public:
		unsigned int hash;
		unsigned int index;

		Name(const Name& other);
		~Name()
		{
		}
		bool operator==(const Name& other) const;
	};
}

#endif
