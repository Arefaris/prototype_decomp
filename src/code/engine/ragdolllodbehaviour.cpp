#include "code/engine/ragdolllodbehaviour.h"
#include "code/engine/physics/ragdollmessages.h"
#include "code/engine/reflectedclasses.h"

namespace engine
{
#define ENGINE_OFFSET(type, member) 	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10924FA0
	CharacterSolverRagdollActivatedMessage::CharacterSolverRagdollActivatedMessage(bool newActivated)
		: IntrusiveMessage(0x11, 0xb)
	{
		activated = newActivated;
	}

	// FUNCTION: ENGINE 0x10925010
	RagdollPhysicsObjectAddedRemovedMessage::RagdollPhysicsObjectAddedRemovedMessage(bool newAdded, int newPhysicsObject)
		: IntrusiveMessage(6, 1)
	{
		added = newAdded;
		physicsObject = newPhysicsObject;
	}

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

	// FUNCTION: ENGINE 0x10927330
	content::MemberList* RagdollBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, RagdollBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberReferenceMetaType<RagdollBehaviour, ravenphysics::PhysicsObjectFactory, 0>("p"),
				ENGINE_OFFSET(RagdollBehaviour, ragdollFactory), "ragdollFactory" },
			{ content::GetMemberReferenceMetaType<RagdollBehaviour, ravenphysics::PhysicsObjectFactory, 1>("p"),
				ENGINE_OFFSET(RagdollBehaviour, ragdoll), "ragdoll" },
			{ content::GetMemberReferenceMetaType<RagdollBehaviour, ravenphysics::PhysicsObjectFactory, 2>("p"),
				ENGINE_OFFSET(RagdollBehaviour, lowLODRagdollFactory), "lowLODRagdollFactory" },
			{ content::GetMemberReferenceMetaType<RagdollBehaviour, ravenphysics::IntersectionPropertiesLoader, 0>("p"),
				ENGINE_OFFSET(RagdollBehaviour, intersectionProperties), "intersectionProperties" },
			{ content::GetMemberReferenceMetaType<RagdollBehaviour, ravenphysics::MaterialLoader, 0>("p"),
				ENGINE_OFFSET(RagdollBehaviour, overrideMaterial), "overrideMaterial" },
			{ content::GetMemberPrimitiveMetaType<RagdollBehaviour, bool, 0>("p"),
				ENGINE_OFFSET(RagdollBehaviour, createRagdollPhysicsObject), "createRagdollPhysicsObject" },
			{ content::GetMemberPrimitiveMetaType<RagdollBehaviour, bool, 1>("p"),
				ENGINE_OFFSET(RagdollBehaviour, isKeyframeUpdated), "isKeyframeUpdated" }
		};
		sList.members = sMembers;
		sList.count = 7;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10925320
// FUNCTION: ENGINE 0x10925330
// FUNCTION: ENGINE 0x109272E0
// FUNCTION: ENGINE 0x10927150
// FUNCTION: ENGINE 0x109271A0
// FUNCTION: ENGINE 0x109271F0
// FUNCTION: ENGINE 0x10927240
// FUNCTION: ENGINE 0x10927290
// FUNCTION: ENGINE 0x109264D0
// FUNCTION: ENGINE 0x10926510
// FUNCTION: ENGINE 0x109252E0
// FUNCTION: ENGINE 0x109252F0
// FUNCTION: ENGINE 0x10924FD0
// FUNCTION: ENGINE 0x10925040
// FUNCTION: ENGINE 0x109252A0
// FUNCTION: ENGINE 0x109252C0
