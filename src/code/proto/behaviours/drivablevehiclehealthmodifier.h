// The data classes of proto::DrivableVehicleHealthModifierBehaviour (RTTI and reflection names): the damage the player
// takes in each state of a vehicle, the parameters of the modifier and the mapping of a weapon profile. Unit
// 0x102BB200 - 0x102BD480 (no assert path; the file name is a guess). Only DamageToPlayerPerState is reconstructed, the
// other classes have their class info.
#ifndef PROTO_BEHAVIOURS_DRIVABLEVEHICLEHEALTHMODIFIER_H
#define PROTO_BEHAVIOURS_DRIVABLEVEHICLEHEALTHMODIFIER_H

#include "code/content/metatype.h"
#include "code/core/name.h"

namespace proto
{
	// The damage the player takes while the vehicle is in a state (RTTI proto::DamageToPlayerPerState; 0x10 bytes)
	struct DamageToPlayerPerState
	{
		// 0x102BB760
		DamageToPlayerPerState();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		core::Name<core::CaseSensitiveKey> state;  // +0x0
		float damage;  // +0x8
	};

	// RTTI proto::DrivableVehicleHealthModifierParams
	struct DrivableVehicleHealthModifierParams
	{
		static content::ClassInfo* GetClassInfo();
	};

	// RTTI proto::WeaponProfileMapping
	struct WeaponProfileMapping
	{
		static content::ClassInfo* GetClassInfo();
	};
}

#endif
