#include "code/engine/knockbehaviour.h"
#include "code/engine/gameobject/gameobject.h"

namespace engine
{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1091EC70
	content::ClassInfo* KnockBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::KnockBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1091ECB0
	KnockBehaviour::KnockBehaviour(GameObject* newOwner) : Behaviour(newOwner)
	{
		strength = 4.0f;
		rangeDistance = 5.0f;
		rangeCosHalfAngle = 0.5f;
		minimumRepeatPeriod = 0.5f;
		repeatTimer = 0.0f;
		damage = 0.0f;
		Listen2(4, true);
	}

	// FUNCTION: ENGINE 0x1091F230
	content::MemberList* KnockBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, KnockBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<KnockBehaviour, float, 0>("p"),
				ENGINE_OFFSET(KnockBehaviour, strength), "strength" },
			{ content::GetMemberPrimitiveMetaType<KnockBehaviour, float, 1>("p"),
				ENGINE_OFFSET(KnockBehaviour, rangeDistance), "rangeDistance" },
			{ content::GetMemberPrimitiveMetaType<KnockBehaviour, float, 2>("p"),
				ENGINE_OFFSET(KnockBehaviour, rangeCosHalfAngle), "rangeCosHalfAngle" },
			{ content::GetMemberPrimitiveMetaType<KnockBehaviour, float, 3>("p"),
				ENGINE_OFFSET(KnockBehaviour, minimumRepeatPeriod), "minimumRepeatPeriod" },
			{ content::GetMemberPrimitiveMetaType<KnockBehaviour, float, 4>("p"),
				ENGINE_OFFSET(KnockBehaviour, damage), "damage" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1091ED10
// FUNCTION: ENGINE 0x1091ED40
// FUNCTION: ENGINE 0x1091ED50
// FUNCTION: ENGINE 0x1091F0F0
// FUNCTION: ENGINE 0x1091F130
// FUNCTION: ENGINE 0x1091F170
// FUNCTION: ENGINE 0x1091F1B0
// FUNCTION: ENGINE 0x1091F1F0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1091ED20
