#include "code/proto/behaviours/bombbehaviour.h"

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

namespace choreo
{
	extern const float gMinusOne;
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10464760
	content::ClassInfo* BombBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::BombBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104647A0
	BombBehaviour::~BombBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x104647C0
	void BombBehaviour::Reset()
	{
		Stop();
		unknownA4.x = 0.0f;
		unknownA4.y = 0.0f;
		unknownA4.z = 0.0f;
	}

	// FUNCTION: ENGINE 0x104647F0
	// EQUIVALENT: block layout; the engine lays the reset out in front of the tail call and branches around it, ours branches to it (62 %)
	void BombBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 2:
			Reset();
			break;
		default:
			MissileBehaviour::OnMessage(message);
			break;
		}
	}

	// FUNCTION: ENGINE 0x10464820
	// EQUIVALENT: scheduling; the engine loads the -1.0 after the zero register is made, ours between its stores (88 %)
	void BombBehaviour::Slot8(int a, int b, float c)
	{
		MissileBehaviour::Slot8(a, b, c);
		unknownA4.x = 0.0f;
		unknownA4.y = choreo::gMinusOne;
		unknownA4.z = 0.0f;
	}

	// FUNCTION: ENGINE 0x10464880
	// EQUIVALENT: scheduling; the engine stores the vftable after the first member stores, ours before them (79 %)
	BombBehaviour::BombBehaviour(engine::GameObject* newOwner)  : MissileBehaviour(newOwner)
	{
		timeToSlowDown = 0.0f;
		float one = engine::driving::gOne;
		slowDownScale = one;
		unknown110 = one;
		unknown114 = one;
		Reset();
	}

	// FUNCTION: ENGINE 0x10464B20
	content::MemberList* BombBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<MissileBehaviour>();
		static content::BaseClassCasterImpl<MissileBehaviour, BombBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<BombBehaviour, float, 0>("p"),
				PROTO_OFFSET(BombBehaviour, timeToSlowDown), "timeToSlowDown" },
			{ content::GetMemberPrimitiveMetaType<BombBehaviour, float, 1>("p"),
				PROTO_OFFSET(BombBehaviour, slowDownScale), "slowDownScale" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104648E0
// FUNCTION: ENGINE 0x104648F0
// FUNCTION: ENGINE 0x10464920
// FUNCTION: ENGINE 0x10464AA0
// FUNCTION: ENGINE 0x10464AE0
