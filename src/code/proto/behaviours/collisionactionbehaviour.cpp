#include "code/proto/behaviours/collisionactionbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10065B90
	// EQUIVALENT: the vftable store and the first float store are scheduled differently (89.4 %)
	CollisionActionBehaviour::CollisionActionBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		unknownC(0), unknown10(false), unknown14(0.0f), unknown18(0.0f), unknown1C(0.0f), unknown20(0.0f), unknown24(0.0f),
		unknown28(0.0f), unknown2C(0.0f), colliderListCountMax(0x20), noWarningOnTooManyColliders(false)
	{
		Listen(0x1d, true);
		Listen(5, true);
		Listen(2, true);
	}

	CollisionActionBehaviour::~CollisionActionBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10065820
	void CollisionActionBehaviour::Slot1()
	{
		colliders.Allocate(colliderListCountMax);
	}

	// FUNCTION: ENGINE 0x10065B50
	void CollisionActionBehaviour::OnActiveChanged(bool active)
	{
		if (!active)
		{
			colliders.end = colliders.begin;
			unknown10 = false;
		}
		engine::Behaviour::OnActiveChanged(active);
	}

	// FUNCTION: ENGINE 0x100659C0
	void CollisionActionBehaviour::ClearColliders(engine::Message* message)
	{
		colliders.end = colliders.begin;
	}

	// FUNCTION: ENGINE 0x10065A70
	// EQUIVALENT: the stores and the pushes of the call's arguments are scheduled differently (39.1 %)
	void CollisionActionBehaviour::Reset()
	{
		unknownC = 0;
		colliders.end = colliders.begin;
		unknown10 = false;
		Listen2(4, false);
	}

	// FUNCTION: ENGINE 0x10064AE0
	content::ClassInfo* CollisionActionBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::CollisionActionBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10065710
	content::MemberList* CollisionActionBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, CollisionActionBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<CollisionActionBehaviour, int, 0>("p"),
				PROTO_OFFSET(CollisionActionBehaviour, colliderListCountMax), "colliderListCountMax" },
			{ content::GetMemberPrimitiveMetaType<CollisionActionBehaviour, bool, 0>("p"),
				PROTO_OFFSET(CollisionActionBehaviour, noWarningOnTooManyColliders), "noWarningOnTooManyColliders" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10064C70
// FUNCTION: ENGINE 0x10064CF0
// FUNCTION: ENGINE 0x100650F0
// FUNCTION: ENGINE 0x10065100
// FUNCTION: ENGINE 0x10065650
// FUNCTION: ENGINE 0x10065690

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10064C60
// FUNCTION: ENGINE 0x10064CD0
// FUNCTION: ENGINE 0x10065550
// FUNCTION: ENGINE 0x10065B70
// FUNCTION: ENGINE 0x10065C30
// FUNCTION: ENGINE 0x10065D30

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10065560
