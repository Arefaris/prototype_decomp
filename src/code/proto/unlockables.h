// The unlockables of the game (RTTI and reflection names, namespace proto): the enumerations of the unlockables
// manager's reflection and the classes of the unlock list. Unit 0x10578EA0 - 0x1057F000 (no assert path; the file
// name is a guess). Only the reflection of the enumerations and the class infos are reconstructed.
#ifndef PROTO_UNLOCKABLES_H
#define PROTO_UNLOCKABLES_H

#include "code/content/metatype.h"

namespace proto
{
	// Every unlockable item (484 reflected values, see unlockables.cpp)
	enum Unlockable
	{
		UNLOCKABLE_NONE = 0
	};

	// What kind of thing an unlockable is
	enum UnlockableType
	{
		UNLOCKABLE_TYPE_POWER = 0
	};

	// What an unlockable is bought with or as (21 reflected values)
	enum PurchaseType
	{
		PURCHASE_TYPE_EP = 0
	};

	// How necessary an unlockable is
	enum NecessityType
	{
		NECESSITY_GENERAL = 0,
		NECESSITY_CORE = 1
	};

	// How the multipliers of the unlock table are applied
	enum UnlockableMultiplierConfig
	{
		MULTIPLIER_NONE = 0,
		MULTIPLIER_INTERLACED = 1
	};

	// One unlockable of the list (the members are not recovered)
	struct UnlockableInfo
	{
		// 0x10579010
		static content::ClassInfo* GetClassInfo();
	};

	// The list of the unlockables (RTTI proto::UnlockablesList; the members are not recovered)
	class UnlockablesList
	{
	public:
		// 0x10579050
		static content::ClassInfo* GetClassInfo();
	};
}

#endif
