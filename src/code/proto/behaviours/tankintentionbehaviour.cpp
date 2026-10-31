#include "code/proto/behaviours/tankintentionbehaviour.h"

namespace engine
{
	extern content::ObjectName gPhysicsObjectAttributeName;
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x100778C0
	TankIntentionBehaviour::TankIntentionBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		unknownC(false), unknown10(math::kZeroVector), unknown1C(false), unknown20(math::kZeroVector), unknown2C(false),
		unknown34(false)
	{
		Listen2(4, true);
		Listen(0x2f, true);
		Listen(0x33, true);
	}

	// FUNCTION: ENGINE 0x10077A80
	void TankIntentionBehaviour::OnActiveChanged(bool active)
	{
		engine::Behaviour::OnActiveChanged(active);
	}

	// FUNCTION: ENGINE 0x10077B80
	void TankIntentionBehaviour::Slot1()
	{
		physicsObjectAttribute = owner->FindAttribute(engine::gPhysicsObjectAttributeName);
	}

	TankIntentionBehaviour::~TankIntentionBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10077880
	content::ClassInfo* TankIntentionBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TankIntentionBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10077B00
	content::MemberList* TankIntentionBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, TankIntentionBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10077A90
// FUNCTION: ENGINE 0x10077AA0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10077980
// FUNCTION: ENGINE 0x10077AD0
