// The helpers the registration functions of the reflected classes are made of (names guessed): the name a member is
// registered under and the description of the class it belongs to.
#ifndef OM_REFLECTION_H
#define OM_REFLECTION_H

#include "code/core/hash.h"
#include "code/om/metaclass.h"
#include "code/om/metatype.h"
#include "code/om/name.h"
#include "code/om/string.h"

namespace om
{
	// The name a member is registered under: the 64-bit hash of its text
	inline ClassName MakeClassName(const String& text)
	{
		return ClassName(core::Hash64(text.GetText(), 0));
	}

	// The description of T, found once and kept in the static every user of the type shares
	template<class T> inline MetaClassBase* GetCachedClass()
	{
		MetaTypeBase*& cache = MetaTypeCache<T>::type;
		if (cache == 0)
		{
			cache = FindMetaType(typeid(T));
		}
		return static_cast<MetaClassBase*>(cache);
	}
}

#endif
