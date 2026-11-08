// core::Name members that other units call (kept copies of the engine's inlines; this is not an original translation
// unit).
#include "code/core/hash.h"
#include "code/core/name.h"
#include "code/pure3d/context.h"

namespace core
{
	// FUNCTION: ENGINE 0x1007EE60
	Name<CaseInsensitiveKey32>::Name()
	{
		hash = 0;
	}

	// FUNCTION: ENGINE 0x10061ED0
	template<> Name<CaseSensitiveKey>& Name<CaseSensitiveKey>::operator=(const Name<CaseSensitiveKey>& other)
	{
		hash = other.hash;
		index = other.index;
		return *this;
	}

	// FUNCTION: ENGINE 0x10061EF0
	// NONMATCHING: the engine ors the two words and branches to a constant per outcome; ours folds it to a single set
	// instruction (11.1 %)
#ifdef NONMATCHING
	template<> bool Name<CaseSensitiveKey>::IsEmpty() const
	{
		return (hash | index) == 0;
	}
#endif

	// FUNCTION: ENGINE 0x10061F10
	template<> bool Name<CaseSensitiveKey>::operator==(const Name<CaseSensitiveKey>& other) const
	{
		return hash == other.hash && index == other.index;
	}

	// FUNCTION: ENGINE 0x10061F40
	// NONMATCHING: the engine tests the low words, then returns on a branch for the high words with the constant 1
	// first; ours lays the two outcomes out the other way round (64.5 %)
#ifdef NONMATCHING
	template<> bool Name<CaseSensitiveKey>::operator!=(const Name<CaseSensitiveKey>& other) const
	{
		return hash != other.hash || index != other.index;
	}
#endif

	// FUNCTION: ENGINE 0x1006A170
	template<> void Name<CaseSensitiveKey>::SetHash(unsigned __int64 newHash)
	{
		hash = (unsigned int)newHash;
		index = (unsigned int)(newHash >> 32);
	}

	// FUNCTION: ENGINE 0x1007EE30
	template<> void Name<CaseSensitiveKey>::SetText(const char* text)
	{
		unsigned __int64 newHash = Hash64(text, 0);
		hash = (unsigned int)newHash;
		index = (unsigned int)(newHash >> 32);
	}
}

namespace pure3d
{
	// FUNCTION: ENGINE 0x1007EE00
	ContextName::ContextName(const unsigned __int64& newHash)
	{
		hash = newHash;
	}

	// FUNCTION: ENGINE 0x1007EE20
	const unsigned __int64& ContextName::GetHash() const
	{
		return hash;
	}
}
