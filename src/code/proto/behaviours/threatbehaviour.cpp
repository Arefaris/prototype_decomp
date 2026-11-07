#include "code/proto/behaviours/threatbehaviour.h"
#include "code/engine/gameobject/gameobject.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10407480
	content::ClassInfo* ExpiryTimeBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ExpiryTimeBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104074C0
	content::ClassInfo* ThreatBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ThreatBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104075D0
	ExpiryTimeBehaviour::ExpiryTimeBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), expiryTime(0.0f),
		timeLeft(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x10407600
	ExpiryTimeBehaviour::~ExpiryTimeBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10407610
	void ExpiryTimeBehaviour::Slot1()
	{
		timeLeft = expiryTime;
		Listen2(4, true);
	}

	// FUNCTION: ENGINE 0x10407630
	void ExpiryTimeBehaviour::OnActiveChanged(bool active)
	{
		if (active)
		{
			timeLeft = expiryTime;
		}
		engine::Behaviour::OnActiveChanged(active);
	}

	// FUNCTION: ENGINE 0x10407650
	void ExpiryTimeBehaviour::Update(float dt, unsigned short mask)
	{
		if (timeLeft < 0.0f)
		{
			owner->SetActive(false);
		}
		timeLeft -= dt;
	}

	// FUNCTION: ENGINE 0x10407890
	ThreatBehaviour::ThreatBehaviour(engine::GameObject* newOwner) : ExpiryTimeBehaviour(newOwner), branch(0)
	{
		unknown34 = -1;
		Listen(0x28, true);
	}

	// FUNCTION: ENGINE 0x10407900
	ThreatBehaviour::~ThreatBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x104079F0
	content::MemberList* ExpiryTimeBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, ExpiryTimeBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<ExpiryTimeBehaviour, float, 0>("p"),
				PROTO_OFFSET(ExpiryTimeBehaviour, expiryTime), "expiryTime" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10407D00
	content::MemberList* ThreatBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<ExpiryTimeBehaviour>();
		static content::BaseClassCasterImpl<ExpiryTimeBehaviour, ThreatBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104076D0
// FUNCTION: ENGINE 0x104076E0
// FUNCTION: ENGINE 0x10407710
// FUNCTION: ENGINE 0x10407720
// FUNCTION: ENGINE 0x10407860
// FUNCTION: ENGINE 0x10407930
// FUNCTION: ENGINE 0x10407C30
