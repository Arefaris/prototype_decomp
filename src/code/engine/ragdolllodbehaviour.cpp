#include "code/engine/ragdolllodbehaviour.h"
#include "code/engine/reflectedclasses.h"

namespace engine
{
#define ENGINE_OFFSET(type, member) 	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10925050
	content::ClassInfo* RagdollBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "RagdollBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10925090
	content::ClassInfo* RagdollLODBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::RagdollLODBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10926350
	// NONMATCHING: the engine stores the vftable right behind the three zeroed members, before the pushes of the first Listen call; ours stores it behind them (84 %)
#ifdef NONMATCHING
	RagdollLODBehaviour::RagdollLODBehaviour(GameObject* newOwner)
		: Behaviour(newOwner), unknownC(0), unknown10(0), lowLODRagdollFactory(0), unknown18(-1), unknown1C(-1)
	{
		Listen(2, true);
		Listen(3, true);
	}
#endif

	// FUNCTION: ENGINE 0x109274D0
	content::MemberList* RagdollLODBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, RagdollLODBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<RagdollLODBehaviour, ravenphysics::PhysicsObjectFactory>("p"),
				ENGINE_OFFSET(RagdollLODBehaviour, lowLODRagdollFactory), "lowLODRagdollFactory" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10925320
// FUNCTION: ENGINE 0x10925330
// FUNCTION: ENGINE 0x109272E0
