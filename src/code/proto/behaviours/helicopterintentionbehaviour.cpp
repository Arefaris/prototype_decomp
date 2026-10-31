#include "code/proto/behaviours/helicopterintentionbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1006FAD0
	HelicopterIntentionBehaviour::HelicopterIntentionBehaviour(engine::GameObject* newOwner) :
		engine::Behaviour(newOwner), unknownC(math::kZeroVector), unknown18(false)
	{
		Listen2(4, true);
		Listen(0x2f, true);
		Listen(0x33, true);
	}

	// FUNCTION: ENGINE 0x1006FB50
	HelicopterIntentionBehaviour::~HelicopterIntentionBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x1006FB60
	void HelicopterIntentionBehaviour::Slot1()
	{
	}

	// FUNCTION: ENGINE 0x1006FA90
	content::ClassInfo* HelicopterIntentionBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HelicopterIntentionBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1006FD60
	content::MemberList* HelicopterIntentionBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, HelicopterIntentionBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1006FCF0
// FUNCTION: ENGINE 0x1006FD00

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1006FD30
