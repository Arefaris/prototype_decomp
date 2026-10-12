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

		// 0x1005D5E0 (another unit): the 64-bit hash of text (core::Hash64(text, 0)); the second argument is passed as 0
		// by its users and its meaning is unknown
		Name(const char* text, int unknown);
		// 0x1005E520 (another unit): the empty name
		Name();
		Name(const Name& other);
		// 0x1007EE00 (another unit's copy): the name of a 64-bit hash
		explicit Name(const unsigned __int64& newHash);
		~Name()
		{
		}
		bool operator==(const Name& other) const;
		// 0x10061ED0 / 0x10061EF0 (another unit)
		Name& operator=(const Name& other);
		bool IsEmpty() const;
		// 0x1007EE20 (another unit's copy): the name as its 64-bit hash
		const unsigned __int64& GetHash() const;
	};

	// Out of line (templates defined outside the class are not inlined): copies like 0x1007EE00 / 0x1007EE20 exist
	// in the units that use them
	template<class Key> Name<Key>::Name(const unsigned __int64& newHash)
	{
		hash = ((const unsigned int*)&newHash)[0];
		index = ((const unsigned int*)&newHash)[1];
	}

	template<class Key> const unsigned __int64& Name<Key>::GetHash() const
	{
		return *(const unsigned __int64*)this;
	}
}

#endif
