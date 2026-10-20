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
		// 0x10834340: true when every tag of other is in this set (or either is "all")
		bool Includes(const TagSet& other) const;
		// 0x10834910: true when the tag is in the set (or the set is "all")
		bool Contains(const core::Name<core::CaseSensitiveKey>& name) const;
		// 0x10834760: the place of the tag in the set, null when it is not in it
		const core::Name<core::CaseSensitiveKey>* Find(const core::Name<core::CaseSensitiveKey>& name) const;
		// 0x10834E80: adds the tag; false when it is in the set already
		bool Add(const core::Name<core::CaseSensitiveKey>& name);
		// 0x10834970: takes the tag out; false when it was not in the set
		bool Remove(const core::Name<core::CaseSensitiveKey>& name);
		// 0x10834D70: puts the tag in front of the first one that is not before it by less
		core::Name<core::CaseSensitiveKey>* InsertSorted(const core::Name<core::CaseSensitiveKey>& name,
			bool (*less)(const core::Name<core::CaseSensitiveKey>&, const core::Name<core::CaseSensitiveKey>&));
		// 0x10834960: takes all the tags out
		void Clear();
		// 0x10835000: puts the tags in order
		void Sort();
		// 0x10834690: the tags as a list in a static buffer
		const char* ToString();
		// 0x10835010: replaces the tags with the list in text
		void FromString(const char* text);

		container::ArrayDynamic<core::Name<core::CaseSensitiveKey>, container::AllocatorCoreStatic<12, 16> > tags;
		bool all;
	};
}

#endif
