// The entries of the character budget (the list of ai characters alive in the world that the budget weighs against each
// other, sorted by the level of detail they keep): one entry per character. Unit 0x10385A00 - 0x1038A3FF together with
// characterbudgetpolicy.h (no assert path; the file name is a guess); class and member names are guesses.
#ifndef PROTO_CHARACTERBUDGET_H
#define PROTO_CHARACTERBUDGET_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/proto/characterbudgetpolicy.h"

namespace proto
{
	// One ai character of the budget (0x50 bytes, 8-aligned through its policy)
	class CharacterBudgetEntry
	{
	public:
		// 0x10386930 (the engine's constructor takes a second argument and ignores it)
		CharacterBudgetEntry(engine::GameObjectHandle newHandle, int unused);
		// 0x10386EF0
		CharacterBudgetEntry(const CharacterBudgetEntry& other);
		// 0x10386A00
		CharacterBudgetEntry& operator=(const CharacterBudgetEntry& other);
		// 0x10385910: whether the entry goes in front of another one in the sorted list
		bool IsBefore(const CharacterBudgetEntry& other) const;

		engine::GameObjectHandle handle;  // +0
		bool unknown4;  // +4
		bool unknown5;  // +5
		CharacterBudgetPolicy policy;  // +8
		float distance;  // +0x30
		int unknown34;  // +0x34
		unsigned char unknown38;  // +0x38
		int unknown3C;  // +0x3C
		unsigned char levelOfDetail;  // +0x40
		bool unknown41;  // +0x41
		float unknown44;  // +0x44
		float unknown48;  // +0x48
		int unknown4C;  // +0x4C
	};

	// 0x103862F0: the comparison of the sort (-1, 0 or 1; name guess)
	int CompareCharacterBudgetEntries(const void* first, const void* second);
	// 0x10386C70: sorts the entries from begin to end (name guess)
	void SortCharacterBudgetEntries(CharacterBudgetEntry* begin, CharacterBudgetEntry* end);
}

namespace container
{
	template<> struct ArrayEraseInline<proto::CharacterBudgetEntry>
	{
		enum
		{
			value = 0
		};
	};
}

#endif
