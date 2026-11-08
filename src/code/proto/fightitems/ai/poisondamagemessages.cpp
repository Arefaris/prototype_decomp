// The reflection of the poison messages proto::EnterPoisonDamageMessage and proto::ExitPoisonDamageMessage (RTTI and
// reflection names; base engine::IntrusiveMessage): both name the type of the poison by an attack type. Unit
// 0x102B58A0 - 0x102B5D60 (no assert path; the file name is a guess).
#include "code/proto/fightitems/ai/aicodemessages.h"
#include "code/content/metatype.h"
#include "code/proto/behaviours/healthbehaviour.h"

namespace proto
{
	// FUNCTION: ENGINE 0x102B58A0
	content::ClassInfo* EnterPoisonDamageMessage::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::EnterPoisonDamageMessage";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102B58E0
	content::ClassInfo* ExitPoisonDamageMessage::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ExitPoisonDamageMessage";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102B5B70
	content::MemberList* EnterPoisonDamageMessage::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::IntrusiveMessage>();
		static content::BaseClassCasterImpl<engine::IntrusiveMessage, EnterPoisonDamageMessage> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<AttackType>(), 0xc, "poisonType" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102B5C30
	content::MemberList* ExitPoisonDamageMessage::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::IntrusiveMessage>();
		static content::BaseClassCasterImpl<engine::IntrusiveMessage, ExitPoisonDamageMessage> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<AttackType>(), 0xc, "poisonType" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102B5A10
// FUNCTION: ENGINE 0x102B5A20
// FUNCTION: ENGINE 0x102B5A50
// FUNCTION: ENGINE 0x102B5A60
