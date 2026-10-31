#include "code/proto/powers/shieldpower.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/nismessages.h"

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
	namespace camera
	{
		extern const float gThree;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1008AF70
	content::ClassInfo* ShieldPower::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ShieldPower";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1008B320
	// EQUIVALENT: the engine loads the constants it stores more than once into registers before the first store, ours
	// loads each where it stores it (51.1 %)
	ShieldPower::ShieldPower() : state(1), jointIndex(0xffff), unknown1C(0.05f), deployedScale(engine::driving::gOne),
		deploySpeed(engine::camera::gThree), retractSpeed(engine::driving::gOne), health(100.0f), currentHealth(0.0f),
		healingTime(5.0f), unknown38(0.0f), unknown3C(0.0f), undamagedTimeBeforeHealing(engine::driving::gOne),
		unknown44(0.0f), autoHealFromBrokenTime(0.0f), shieldObject(0)
	{
	}

	// FUNCTION: ENGINE 0x1008B400
	ShieldPower::ShieldPower(const ShieldPower& other) : Power(other), state(other.state),
		shieldJoint(other.shieldJoint), jointIndex(other.jointIndex), unknown1C(other.unknown1C),
		deployedScale(other.deployedScale), deploySpeed(other.deploySpeed), retractSpeed(other.retractSpeed),
		health(other.health), currentHealth(other.currentHealth), healingTime(other.healingTime),
		unknown38(other.unknown38), unknown3C(other.unknown3C),
		undamagedTimeBeforeHealing(other.undamagedTimeBeforeHealing), unknown44(other.unknown44),
		autoHealFromBrokenTime(other.autoHealFromBrokenTime), gameObjectTemplate(other.gameObjectTemplate),
		grabSlot(other.grabSlot), shieldObject(0)
	{
	}

	// FUNCTION: ENGINE 0x1008B4D0
	ShieldPower::~ShieldPower()
	{
		shieldHandle.DeferUpdate(false);
		shieldObject = 0;
	}

	// FUNCTION: ENGINE 0x1008B500
	Power* ShieldPower::Clone()
	{
		return new ShieldPower(*this);
	}

	// FUNCTION: ENGINE 0x1008AFB0
	// EQUIVALENT: the engine loads the health into the x87 unit and the constant behind it, ours the constant first (77.7 %)
	void ShieldPower::Slot8()
	{
		currentHealth = health;
		state = 1;
		unknown1C = 0.05f;
		unknown3C = 0.0f;
		if (shieldObject != 0)
		{
			engine::PlayBranchMessage message(0, 0);
			shieldObject->SendMessage(&message);
		}
	}

	// FUNCTION: ENGINE 0x1008B0D0
	float ShieldPower::Slot12()
	{
		return unknown38;
	}

	// FUNCTION: ENGINE 0x1008B040
	void ShieldPower::Slot13()
	{
		if (shieldObject != 0)
		{
			engine::PlayBranchMessage message(0, 0);
			shieldObject->SendMessage(&message);
		}
	}

	// FUNCTION: ENGINE 0x1008B0B0
	bool ShieldPower::GetMessageMask(unsigned int* mask)
	{
		*mask = 0x1e;
		return true;
	}

	// FUNCTION: ENGINE 0x1008BAD0
	content::MemberList* ShieldPower::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Power>();
		static content::BaseClassCasterImpl<Power, ShieldPower> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<ShieldPower>(true, true, "p"), PROTO_NAME_OFFSET(ShieldPower, shieldJoint),
				"shieldJoint" },
			{ content::GetMemberPrimitiveMetaType<ShieldPower, float, 0>("p"),
				PROTO_OFFSET(ShieldPower, deployedScale), "deployedScale" },
			{ content::GetMemberPrimitiveMetaType<ShieldPower, float, 1>("p"),
				PROTO_OFFSET(ShieldPower, deploySpeed), "deploySpeed" },
			{ content::GetMemberPrimitiveMetaType<ShieldPower, float, 2>("p"),
				PROTO_OFFSET(ShieldPower, retractSpeed), "retractSpeed" },
			{ content::GetMemberPrimitiveMetaType<ShieldPower, float, 3>("p"), PROTO_OFFSET(ShieldPower, health),
				"health" },
			{ content::GetMemberPrimitiveMetaType<ShieldPower, float, 4>("p"),
				PROTO_OFFSET(ShieldPower, healingTime), "healingTime" },
			{ content::GetMemberPrimitiveMetaType<ShieldPower, float, 5>("p"),
				PROTO_OFFSET(ShieldPower, undamagedTimeBeforeHealing), "undamagedTimeBeforeHealing" },
			{ content::GetMemberPrimitiveMetaType<ShieldPower, float, 6>("p"),
				PROTO_OFFSET(ShieldPower, autoHealFromBrokenTime), "autoHealFromBrokenTime" },
			{ content::GetNameMetaTypeCopy<ShieldPower>(true, true, "p"),
				PROTO_NAME_OFFSET(ShieldPower, gameObjectTemplate), "gameObjectTemplate" },
			{ content::GetMemberNameMetaType<ShieldPower, 1>(true, true, "p"), PROTO_NAME_OFFSET(ShieldPower, grabSlot),
				"grabSlot" }
		};
		sList.members = sMembers;
		sList.count = 10;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1008AF60
// FUNCTION: ENGINE 0x1008B110
// FUNCTION: ENGINE 0x1008B170
// FUNCTION: ENGINE 0x1008B1B0
// FUNCTION: ENGINE 0x1008B1F0
// FUNCTION: ENGINE 0x1008B2E0
// FUNCTION: ENGINE 0x1008B2F0
// FUNCTION: ENGINE 0x1008B8A0
// FUNCTION: ENGINE 0x1008B8E0
// FUNCTION: ENGINE 0x1008B920
// FUNCTION: ENGINE 0x1008B960
// FUNCTION: ENGINE 0x1008B9A0
// FUNCTION: ENGINE 0x1008B9E0
// FUNCTION: ENGINE 0x1008BA20
// FUNCTION: ENGINE 0x1008BD70
