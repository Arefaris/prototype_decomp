#include "code/proto/behaviours/motionstatebehaviour.h"

namespace content
{
	static const EnumValue sMotionStateValues[] =
	{
		{ "NotSet", -1 },
		{ "Idling", 0 },
		{ "Walking", 1 },
		{ "Running", 2 },
		{ "Falling", 3 },
		{ "Jumping", 4 },
		{ "Wallrunning", 5 },
		{ "GettingHit", 6 },
		{ "AttackWindup", 7 },
		{ "AttackRelease", 8 },
		{ "Flying", 9 },
		{ "Climbing", 10 },
		{ "BeingGrabbed", 11 },
		{ "Driving", 12 },
		{ "Blocking", 13 },
		{ "Stunned", 14 },
		{ "Gliding", 15 },
		{ "JumpingOutOfWater", 16 },
		{ "Consuming", 17 },
		{ "Devastator", 18 },
		{ "Sliding", 19 },
		{ "Other", 20 }
	};

	// FUNCTION: ENGINE 0x10075510
	template<> void EnumInfo<proto::MotionState::State>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::MotionState::State";
		*code = "";
		*values = sMotionStateValues;
		*count = 0x16;
	}
}

namespace proto
{
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10075710
	MotionStateBehaviour::MotionStateBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		motionState(MotionState::STATE_NOT_SET), unknown1C(false)
	{
		Listen(2, true);
		Listen(0x21, true);
	}

	MotionStateBehaviour::~MotionStateBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10075550
	content::ClassInfo* MotionStateBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::MotionStateBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x100758C0
	content::MemberList* MotionStateBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, MotionStateBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<MotionState::State>(), 0x18, "motionState" },
			{ content::GetNameMetaType<MotionStateBehaviour>(true, true, ""),
				PROTO_NAME_OFFSET(MotionStateBehaviour, name), "name" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x100755A0
// FUNCTION: ENGINE 0x10075630
// FUNCTION: ENGINE 0x100756D0
// FUNCTION: ENGINE 0x100756E0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10075770
// FUNCTION: ENGINE 0x100759C0
