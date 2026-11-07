#include "code/proto/behaviours/bloodtoxbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_RAW_OFFSET(type, member) \
	((int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x103C90D0
	content::ClassInfo* BloodtoxBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::BloodtoxBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103C9110
	BloodtoxBehaviour::BloodtoxBehaviour(engine::GameObject* newOwner) : engine::TriggerBehaviour(newOwner),
		scaleTime(0.0f), lifeTime(-1.0f), poisonYDist(10.0f), unknownD4(0.0f), unknownD8(0), unknownE0(false)
	{
		Listen(0x2b, true);
		Listen(0x14, true);
	}

	// FUNCTION: ENGINE 0x103C91B0
	BloodtoxBehaviour::BloodtoxBehaviour(engine::GameObject* newOwner, engine::trigger::Volume* newVolume) :
		engine::TriggerBehaviour(newOwner, newVolume), scaleTime(0.0f), lifeTime(-1.0f), unknownD4(0.0f),
		unknownD8(0), unknownE0(false)
	{
		Listen(0x2b, true);
		Listen(0x14, true);
	}

	// FUNCTION: ENGINE 0x103C9250
	BloodtoxBehaviour::BloodtoxBehaviour(engine::GameObject* newOwner, engine::trigger::Volume* newVolume,
		int newMode) : engine::TriggerBehaviour(newOwner, newVolume, newMode), scaleTime(0.0f),
		lifeTime(-1.0f), unknownD4(0.0f), unknownD8(0), unknownE0(false)
	{
		Listen(0x2b, true);
		Listen(0x14, true);
	}

	// FUNCTION: ENGINE 0x103C92F0
	BloodtoxBehaviour::~BloodtoxBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x103C9300
	void BloodtoxBehaviour::OnActiveChanged(bool active)
	{
		engine::TriggerBehaviour::OnActiveChanged(active);
	}

	// FUNCTION: ENGINE 0x103C9760
	content::MemberList* BloodtoxBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::TriggerBehaviour>();
		static content::BaseClassCasterImpl<engine::TriggerBehaviour, BloodtoxBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<BloodtoxBehaviour, 0>("p"),
				PROTO_RAW_OFFSET(BloodtoxBehaviour, initialVolumeScale), "initialVolumeScale" },
			{ content::GetMemberVectorMetaType<BloodtoxBehaviour, 1>("p"),
				PROTO_RAW_OFFSET(BloodtoxBehaviour, finalVolumeScale), "finalVolumeScale" },
			{ content::GetMemberPrimitiveMetaType<BloodtoxBehaviour, float, 2>("p"),
				PROTO_OFFSET(BloodtoxBehaviour, scaleTime), "scaleTime" },
			{ content::GetMemberPrimitiveMetaType<BloodtoxBehaviour, float, 3>("p"),
				PROTO_OFFSET(BloodtoxBehaviour, lifeTime), "lifeTime" },
			{ content::GetMemberPrimitiveMetaType<BloodtoxBehaviour, float, 4>("p"),
				PROTO_OFFSET(BloodtoxBehaviour, poisonYDist), "poisonYDist" },
			{ content::GetMemberVectorMetaType<BloodtoxBehaviour, 5>("p"),
				PROTO_RAW_OFFSET(BloodtoxBehaviour, scaleDisplacement), "scaleDisplacement" }
		};
		sList.members = sMembers;
		sList.count = 6;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103C9370
// FUNCTION: ENGINE 0x103C93B0
// FUNCTION: ENGINE 0x103C93F0
// FUNCTION: ENGINE 0x103C9430
// FUNCTION: ENGINE 0x103C96A0
// FUNCTION: ENGINE 0x103C96E0
// FUNCTION: ENGINE 0x103C9720
