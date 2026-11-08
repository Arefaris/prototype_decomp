#include "code/proto/behaviours/drivablevehiclehealthmodifier.h"
#include "code/proto/reflectedstubs.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x102BB200
	content::ClassInfo* DamageToPlayerPerState::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::DamageToPlayerPerState";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102BB240
	content::ClassInfo* DrivableVehicleHealthModifierParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::DrivableVehicleHealthModifierParams";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102BB280
	content::ClassInfo* WeaponProfileMapping::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WeaponProfileMapping";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102BB2C0
	content::ClassInfo* DrivableVehicleHealthModifierBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::DrivableVehicleHealthModifierBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102BB760
	DamageToPlayerPerState::DamageToPlayerPerState()
	{
		damage = 0.0f;
	}

	// FUNCTION: ENGINE 0x102BBD90
	content::MemberList* DamageToPlayerPerState::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<DamageToPlayerPerState>(true, true, "p"), PROTO_OFFSET(DamageToPlayerPerState, state),
				"state" },
			{ content::GetMemberPrimitiveMetaType<DamageToPlayerPerState, float, 0>("p"),
				PROTO_OFFSET(DamageToPlayerPerState, damage), "damage" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}
}
// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102BB5A0
// FUNCTION: ENGINE 0x102BB7F0
