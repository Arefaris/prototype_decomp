// What the registration functions of the node classes share (the engine expands these in each of them): the lookup of the
// reflection of a class and the name key of a text the string only borrows.
#ifndef MGRAPH_REGISTRATION_H
#define MGRAPH_REGISTRATION_H

#include "code/mgraph/throw.h"
#include "code/om/metamethod.h"
#include "code/om/metaproperty.h"

namespace mgraph
{
	// The reflection of the class N, found once and kept in the cache the users of the type share
	template<class N> __forceinline om::MetaClassBase* FindNodeClass()
	{
		om::MetaTypeBase*& cache = om::MetaTypeCache<N>::type;
		om::MetaTypeBase* type = cache;
		if (type == 0)
		{
			type = om::FindMetaType(typeid(N));
			cache = type;
		}
		return static_cast<om::MetaClassBase*>(type);
	}

	__forceinline om::ClassName BorrowedKey(const om::String& text)
	{
		return om::ClassName(core::Hash64(text.GetText(), 0));
	}
}

#endif
