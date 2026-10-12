// A set of tags (core::Name), kept sorted, or "all" (class name guessed; its unit is 0x108340A0 - 0x108351A0, not
// reconstructed yet). Stream triggers and packages carry one each and are matched by intersecting them.
#ifndef ENGINE_SYSTEM_TAGSET_H
#define ENGINE_SYSTEM_TAGSET_H

#include "code/container/arraydynamicstatic.h"
#include "code/core/name.h"

namespace engine
{
	class TagSet
	{
	public:
		// 0x10834D60
		TagSet();

		// 0x108342A0: true when the sets share a tag (or either is "all")
		bool Intersects(const TagSet& other) const;
		// 0x10834690: the tags as a list in a static buffer
		const char* ToString();
		// 0x10835010: replaces the tags with the list in text
		void FromString(const char* text);

		container::ArrayDynamic<core::Name<core::CaseSensitiveKey>, container::AllocatorCoreStatic<12, 16> > tags;
		bool all;
	};
}

#endif
