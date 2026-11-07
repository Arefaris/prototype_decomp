// The soldier budgets (gAISystem +0x10; the name is a guess): the list of ai characters alive in the world, one
// CharacterBudgetEntry per character, and the limits the budget keeps them within. Unit 0x10385A00 - 0x1038A3FF together
// with characterbudgetpolicy.h; class and member names are guesses.
#ifndef PROTO_SOLDIERBUDGETS_H
#define PROTO_SOLDIERBUDGETS_H

#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/proto/characterbudget.h"
#include "code/proto/characterbudgetpolicy.h"

namespace proto
{
	class SoldierBudgets
	{
	public:
		typedef container::ArrayDynamic<CharacterBudgetEntry, container::AllocatorNew> EntryArray;

		// 0x10386540 / 0x10386570: the entry of a character (the end of the list when there is none)
		CharacterBudgetEntry* Find(engine::GameObjectHandle handle);
		const CharacterBudgetEntry* Find(engine::GameObjectHandle handle) const;
		// 0x103865A0: gives the character unlimited distances, or the default ones (false when it has no entry)
		bool SetUnlimitedDistances(engine::GameObjectHandle handle, bool unlimited);
		// 0x10386620: gives the character a policy (false when it has no entry)
		bool SetPolicy(engine::GameObjectHandle handle, const CharacterBudgetPolicy& policy);
		// 0x10386690: the policy of the character (null when it has no entry)
		CharacterBudgetPolicy* GetPolicy(engine::GameObjectHandle handle);
		// 0x103866F0: gives the character the policy of a class name (false without an entry or a policy of the name)
		bool SetPolicyByName(engine::GameObjectHandle handle, core::Name<core::CaseSensitiveKey> className);
		// 0x103867D0: sets the squared despawn distance of the character's policy (false when it has no entry)
		bool SetDespawnDistanceSquared(engine::GameObjectHandle handle, const float* value);
		// 0x103866C0: whether the object is in a loaded cell (name guess)
		bool Unknown103866C0(engine::GameObjectHandle handle) const;
		// 0x10386810: whether a soldier of a type may still be reserved for the object (name guess)
		bool Unknown10386810(int type, engine::GameObjectHandle handle);

		EntryArray entries;  // +0
		unsigned char unknownC[0x10];
		int maxEntries;  // +0x1C
		unsigned char unknown20[4];
		int reserved;  // +0x24
		engine::GameObjectHandle reservedHandle;  // +0x28
		float unknown2C;  // +0x2C
		unsigned char unknown30[0x60];
		int unknown90;  // +0x90
		unsigned char unknown94[4];
		CharacterBudgetPolicyList* policies;  // +0x98
	};
}

#endif
