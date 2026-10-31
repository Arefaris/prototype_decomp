#include "code/proto/behaviours/tunnelingbehaviour.h"

namespace choreo
{
	extern const float gMinusOne;
}

namespace engine
{
	extern content::ObjectName gPuppetAttributeName;
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10079130
	// EQUIVALENT: the stores of the constants and of the last words are scheduled differently (83.0 %)
	TunnelingBehaviour::TunnelingBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), unknownC(1),
		unknown10(math::kZeroVector), unknown1C(math::kZeroVector), unknown28(math::kZeroVector),
		depthUnderground(20.0f), offsetOverground(0.0f), unknown3C(-1), unknown40(-1), unknown44(-1), puppetAttribute(0),
		unknown4C(false), unknown50(choreo::gMinusOne)
	{
		Listen(0x1a, true);
		Listen(0x2f, true);
		Listen(2, true);
		Listen(0x39, true);
	}

	// FUNCTION: ENGINE 0x10078AC0
	void TunnelingBehaviour::OnActiveChanged(bool active)
	{
		engine::Behaviour::OnActiveChanged(active);
	}

	// FUNCTION: ENGINE 0x10079270
	void TunnelingBehaviour::Slot1()
	{
		Listen2(0x10, true);
		unknownC = 1;
		puppetAttribute = owner->FindAttribute(engine::gPuppetAttributeName);
	}

	TunnelingBehaviour::~TunnelingBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10078A70
	content::ClassInfo* TunnelingBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TunnelingBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10079020
	content::MemberList* TunnelingBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, TunnelingBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<TunnelingBehaviour, float, 0>("p"),
				PROTO_OFFSET(TunnelingBehaviour, depthUnderground), "depthUnderground" },
			{ content::GetMemberPrimitiveMetaType<TunnelingBehaviour, float, 1>("p"),
				PROTO_OFFSET(TunnelingBehaviour, offsetOverground), "offsetOverground" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10078D90
// FUNCTION: ENGINE 0x10078DA0
// FUNCTION: ENGINE 0x10078EE0
// FUNCTION: ENGINE 0x10078F20

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10078AB0
// FUNCTION: ENGINE 0x10078DD0
