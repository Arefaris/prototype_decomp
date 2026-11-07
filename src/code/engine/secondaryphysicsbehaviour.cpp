// engine::SecondaryPhysicsBehaviour (RTTI name; base engine::Behaviour): unit 0x10927F60 - 0x10929690. Only the
// reflection's class description is reconstructed so far; the class is still described by reflectedclasses.h.
#include "code/engine/reflectedclasses.h"

namespace engine
{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10927F60
	content::ClassInfo* SecondaryPhysicsBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SecondaryPhysicsBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10928F80
	content::MemberList* SecondaryPhysicsBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, SecondaryPhysicsBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<SecondaryPhysicsBehaviour, SecondaryPhysicsProperties>("pnr"),
				ENGINE_OFFSET(SecondaryPhysicsBehaviour, sharedProperties), "sharedProperties" },
			{ content::GetMemberPrimitiveMetaType<SecondaryPhysicsBehaviour, bool, 0>("pn"),
				ENGINE_OFFSET(SecondaryPhysicsBehaviour, sendPoseSyncMessage), "sendPoseSyncMessage" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x109281B0
// FUNCTION: ENGINE 0x10928A30
// FUNCTION: ENGINE 0x10928270
// FUNCTION: ENGINE 0x10928280
// FUNCTION: ENGINE 0x10928AD0
// FUNCTION: ENGINE 0x10928AE0
// FUNCTION: ENGINE 0x10928F00
