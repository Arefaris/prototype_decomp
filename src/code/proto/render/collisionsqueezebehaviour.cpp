#include "code/proto/render/collisionsqueezebehaviour.h"

namespace engine
{
	extern content::ObjectName gPhysicsObjectAttributeName;
}

namespace proto
{
	// FUNCTION: ENGINE 0x102F1EE0
	CollisionSqueezeBehaviour::CollisionSqueezeBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner)
	{
		physicsObjectAttribute = 0;
		unknown10 = false;
		unknown14 = 0;
		Listen(0x1a, true);
		Listen2(0x40, true);
		physicsObjectAttribute = owner->FindAttribute(engine::gPhysicsObjectAttributeName);
	}

	// FUNCTION: ENGINE 0x102F1D80
	content::ClassInfo* CollisionSqueezeBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::CollisionSqueezeBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F1DC0
	CollisionSqueezeBehaviour::~CollisionSqueezeBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x102F1DD0
	void CollisionSqueezeBehaviour::OnMessage(engine::Message* message)
	{
		if (message->type == 0x1a)
		{
			unknown10 = false;
		}
	}

	// FUNCTION: ENGINE 0x102F1E60
	content::MemberList* CollisionSqueezeBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, CollisionSqueezeBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102F1DF0
// FUNCTION: ENGINE 0x102F1E00
// FUNCTION: ENGINE 0x102F1E30
