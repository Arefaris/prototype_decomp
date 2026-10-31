#include "code/proto/behaviours/tendrilbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x100784C0
	TendrilBehaviour::TendrilBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), firstAction(0)
	{
		Listen(0x1e, true);
		Listen(0x17, true);
		Listen(2, true);
		Listen2(0x100, true);
	}

	// FUNCTION: ENGINE 0x10078480
	content::ClassInfo* TendrilBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TendrilBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x100788C0
	content::MemberList* TendrilBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, TendrilBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10078640
// FUNCTION: ENGINE 0x10078650

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x100789C0
