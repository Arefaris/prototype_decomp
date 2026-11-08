#include "code/proto/behaviours/drivablevehiclehealthmodifier.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectmessages.h"
#include "code/proto/behaviours/weaponbehaviour.h"

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

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

	// FUNCTION: ENGINE 0x102BB300
	void DrivableVehicleHealthModifierBehaviour::UpdateDamageScale()
	{
		float scale = engine::driving::gOne;
		if (playerDriving)
		{
			int count = gUnlockTable->CountUnlocked(params.playerDamageScaleUnlockableFirst,
				params.playerDamageScaleUnlockableLast);
			int span = params.playerDamageScaleUnlockableLast - params.playerDamageScaleUnlockableFirst + 1;
			scale = (params.playerDamageScaleMax - params.playerDamageScaleMin) / (float)span * (float)count
				+ params.playerDamageScaleMin;
			unlockedCount = count;
		}
		engine::SetDamageScaleMessage message(scale);
		owner->SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x102BB3B0
	void DrivableVehicleHealthModifierBehaviour::Update(float dt, unsigned short mask)
	{
		if (playerDriving)
		{
			if (unknown10 > 0.0f)
			{
				unknown10 = unknown10 - dt;
				if (unknown10 <= 0.0f)
				{
					engine::SetUndamageableMessage message(false);
					owner->SendMessage(&message);
				}
			}
			if (gUnlockTable->CountUnlocked(params.playerDamageScaleUnlockableFirst,
				params.playerDamageScaleUnlockableLast) != unlockedCount)
			{
				UpdateDamageScale();
			}
		}
	}

	// FUNCTION: ENGINE 0x102BB760
	DamageToPlayerPerState::DamageToPlayerPerState()
	{
		damage = 0.0f;
	}

	// FUNCTION: ENGINE 0x102BB7C0
	WeaponProfileMapping::WeaponProfileMapping() : userProfile(0), ammoProfile(0)
	{
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

	// FUNCTION: ENGINE 0x102BC650
	content::MemberList* DrivableVehicleHealthModifierParams::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<DrivableVehicleHealthModifierParams, bool, 0>("p"),
				PROTO_OFFSET(DrivableVehicleHealthModifierParams, immuneWhilePlayerAttached),
				"immuneWhilePlayerAttached" },
			{ content::GetMemberPrimitiveMetaType<DrivableVehicleHealthModifierParams, float, 0>("p"),
				PROTO_OFFSET(DrivableVehicleHealthModifierParams, timeImmuneWithPlayerDriver),
				"timeImmuneWithPlayerDriver" },
			{ content::GetMemberPrimitiveMetaType<DrivableVehicleHealthModifierParams, float, 1>("p"),
				PROTO_OFFSET(DrivableVehicleHealthModifierParams, minHealthWithPlayerDriver),
				"minHealthWithPlayerDriver" },
			{ content::GetMemberPrimitiveMetaType<DrivableVehicleHealthModifierParams, bool, 1>("p"),
				PROTO_OFFSET(DrivableVehicleHealthModifierParams, giveMinHealthEachEntrance),
				"giveMinHealthEachEntrance" },
			{ content::GetMemberNameMetaType<DrivableVehicleHealthModifierParams, 0>(true, true, "p"),
				PROTO_OFFSET(DrivableVehicleHealthModifierParams, driverGrabslotName), "driverGrabslotName" },
			{ content::GetEnumMetaType<Unlockable>(), 0x18, "playerDamageScaleUnlockableFirst" },
			{ content::GetEnumMetaType<Unlockable>(), 0x1c, "playerDamageScaleUnlockableLast" },
			{ content::GetMemberPrimitiveMetaType<DrivableVehicleHealthModifierParams, float, 2>("p"),
				PROTO_OFFSET(DrivableVehicleHealthModifierParams, playerDamageScaleMin), "playerDamageScaleMin" },
			{ content::GetMemberPrimitiveMetaType<DrivableVehicleHealthModifierParams, float, 3>("p"),
				PROTO_OFFSET(DrivableVehicleHealthModifierParams, playerDamageScaleMax), "playerDamageScaleMax" },
			{ content::GetArrayDynamicMetaType<DrivableVehicleHealthModifierParams,
				DrivableVehicleHealthModifierParams::StateArray>(content::GetClassMetaType<DamageToPlayerPerState>(), "p"),
				PROTO_OFFSET(DrivableVehicleHealthModifierParams, damageToPlayerPerState), "damageToPlayerPerState" }
		};
		sList.members = sMembers;
		sList.count = 10;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102BC8B0
	content::MemberList* WeaponProfileMapping::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberNameMetaType<WeaponProfileMapping, 0>(true, true, "p"),
				PROTO_OFFSET(WeaponProfileMapping, weapon), "weapon" },
			{ content::GetReferenceMetaType<WeaponProfileMapping, WeaponUserProfile>("p"),
				PROTO_OFFSET(WeaponProfileMapping, userProfile), "userProfile" },
			{ content::GetReferenceMetaType<WeaponProfileMapping, AmmoProfileBase>("p"),
				PROTO_OFFSET(WeaponProfileMapping, ammoProfile), "ammoProfile" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102BCD00
	content::MemberList* DrivableVehicleHealthModifierBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, DrivableVehicleHealthModifierBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetClassMetaType<DrivableVehicleHealthModifierParams>(),
				PROTO_OFFSET(DrivableVehicleHealthModifierBehaviour, params), "params" },
			{ content::GetArrayCDynamicMetaType<DrivableVehicleHealthModifierBehaviour,
				container::ArrayCDynamic<WeaponProfileMapping, 6> >(6, content::GetClassMetaType<WeaponProfileMapping>(), "p"),
				PROTO_OFFSET(DrivableVehicleHealthModifierBehaviour, playerWeaponProfiles), "playerWeaponProfiles" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102BD220
	// NONMATCHING: the engine loads the constant for the two scales once (60.0 %)
#ifdef NONMATCHING
	DrivableVehicleHealthModifierParams::DrivableVehicleHealthModifierParams() : immuneWhilePlayerAttached(true),
		timeImmuneWithPlayerDriver(0.0f), minHealthWithPlayerDriver(0.0f), giveMinHealthEachEntrance(true),
		playerDamageScaleMin(engine::driving::gOne), playerDamageScaleMax(engine::driving::gOne)
	{
	}
#endif

	// FUNCTION: ENGINE 0x102BD290
	DrivableVehicleHealthModifierBehaviour::~DrivableVehicleHealthModifierBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x102BD2D0
	void DrivableVehicleHealthModifierBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 0xb:
			if ((unsigned short)message->id == 3)
			{
				OnFightEvent(message);
			}
			break;
		case 0x1f:
			if ((unsigned short)message->id == 0xe)
			{
				OnGrabbedSlot(message);
			}
			break;
		}
	}

	// FUNCTION: ENGINE 0x102BD480
	DrivableVehicleHealthModifierBehaviour::DrivableVehicleHealthModifierBehaviour(engine::GameObject* newOwner)
		: engine::Behaviour(newOwner), unknownC(false), unknown10(0.0f), unknown14(true), playerDriving(false),
		unlockedCount(-1)
	{
		Listen(0xb, true);
		Listen(0x1f, true);
		Listen2(4, true);
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102BB5A0
// FUNCTION: ENGINE 0x102BB7F0
// FUNCTION: ENGINE 0x102BB450
// FUNCTION: ENGINE 0x102BB470
// FUNCTION: ENGINE 0x102BB480
// FUNCTION: ENGINE 0x102BB5E0
// FUNCTION: ENGINE 0x102BB640
// FUNCTION: ENGINE 0x102BB6C0
// FUNCTION: ENGINE 0x102BB780
// FUNCTION: ENGINE 0x102BB790
// FUNCTION: ENGINE 0x102BB830
// FUNCTION: ENGINE 0x102BB870
// FUNCTION: ENGINE 0x102BB8B0
// FUNCTION: ENGINE 0x102BB8F0
// FUNCTION: ENGINE 0x102BB930
// FUNCTION: ENGINE 0x102BB970
// FUNCTION: ENGINE 0x102BB9B0
// FUNCTION: ENGINE 0x102BB9C0
// FUNCTION: ENGINE 0x102BB9E0
// FUNCTION: ENGINE 0x102BBA00
// FUNCTION: ENGINE 0x102BBA60
// FUNCTION: ENGINE 0x102BBA90
// FUNCTION: ENGINE 0x102BBAC0
// FUNCTION: ENGINE 0x102BBAF0
// FUNCTION: ENGINE 0x102BBB00
// FUNCTION: ENGINE 0x102BBB20
// FUNCTION: ENGINE 0x102BBB60
// FUNCTION: ENGINE 0x102BBBC0
// FUNCTION: ENGINE 0x102BBBE0
// FUNCTION: ENGINE 0x102BBC00
// FUNCTION: ENGINE 0x102BBC40
// FUNCTION: ENGINE 0x102BBC70
// FUNCTION: ENGINE 0x102BC220
// FUNCTION: ENGINE 0x102BC280
// FUNCTION: ENGINE 0x102BC2E0
// FUNCTION: ENGINE 0x102BC340
// FUNCTION: ENGINE 0x102BC3A0
// FUNCTION: ENGINE 0x102BC500
// FUNCTION: ENGINE 0x102BCA20
// FUNCTION: ENGINE 0x102BCA80
// FUNCTION: ENGINE 0x102BCAE0
// FUNCTION: ENGINE 0x102BCB60
// FUNCTION: ENGINE 0x102BD100
// FUNCTION: ENGINE 0x102BD130
// FUNCTION: ENGINE 0x102BD180
// FUNCTION: ENGINE 0x102BD270
// FUNCTION: ENGINE 0x102BD320
