// The reflection of proto::PedBehaviourTunables, the load object with the tuning values of the pedestrian behaviours
// (its constructor, destructor and class info are other files'; the table of reactions is pedalertreaction.cpp). Unit
// 0x10434360 - 0x10440830 (scattered; no assert path, the file name is a guess). The reflected names are original, the
// rest is guessed.
#include "code/proto/reflectedstubs.h"
#include "code/ravenphysics/physicsobjectfactory.h"

namespace proto
{
	// Reflected load object whose layout is not recovered (RTTI struct, base content::MetaLoadObject)
	struct TargetSelectionWeights : public content::MetaLoadObject
	{
	};

	// Tells the references to one type apart: the engine has a meta type of its own for every member
	template<int Id> struct PedTunablesMember
	{
	};

#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1043FB30
	content::MemberList* PedBehaviourTunables::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<PedTunablesMember<0>, content::MetaObjectTemplate>("p"),
				PROTO_OFFSET(PedBehaviourTunables, pedestrianAlertTemplate), "pedestrianAlertTemplate" },
			{ content::GetReferenceMetaType<PedTunablesMember<1>, TargetSelectionWeights>("p"),
				PROTO_OFFSET(PedBehaviourTunables, weights), "weights" },
			{ content::GetMemberPrimitiveMetaType<PedBehaviourTunables, float, 0>("p"),
				PROTO_OFFSET(PedBehaviourTunables, characterFadeTime), "characterFadeTime" },
			{ content::GetClassMetaType<PedAlertReactionTable>(),
				PROTO_OFFSET(PedBehaviourTunables, pedAlertReactionTable), "pedAlertReactionTable" },
			{ content::GetReferenceMetaType<PedTunablesMember<2>, ravenphysics::AbstractPhysicsObjectFactory>("p"),
				PROTO_OFFSET(PedBehaviourTunables, alivePedestrianPhysicsObjectFactory),
				"alivePedestrianPhysicsObjectFactory" },
			{ content::GetReferenceMetaType<PedTunablesMember<3>, ravenphysics::AbstractPhysicsObjectFactory>("p"),
				PROTO_OFFSET(PedBehaviourTunables, deadPedestrianPhysicsObjectFactory),
				"deadPedestrianPhysicsObjectFactory" },
			{ content::GetReferenceMetaType<PedTunablesMember<4>, ravenphysics::AbstractPhysicsObjectFactory>("p"),
				PROTO_OFFSET(PedBehaviourTunables, targetingPhysicsObjectFactory),
				"targetingPhysicsObjectFactory" },
			{ content::GetReferenceMetaType<PedTunablesMember<5>, ravenphysics::PhysicsObjectFactory>("p"),
				PROTO_OFFSET(PedBehaviourTunables, maleRagdollFactory), "maleRagdollFactory" },
			{ content::GetReferenceMetaType<PedTunablesMember<6>, ravenphysics::PhysicsObjectFactory>("p"),
				PROTO_OFFSET(PedBehaviourTunables, femaleRagdollFactory), "femaleRagdollFactory" },
			{ content::GetReferenceMetaType<PedTunablesMember<7>, content::MetaObjectTemplate>("p"),
				PROTO_OFFSET(PedBehaviourTunables, pedestrianTemplate), "pedestrianTemplate" },
			{ content::GetMemberPrimitiveMetaType<PedBehaviourTunables, float, 1>("p"),
				PROTO_OFFSET(PedBehaviourTunables, impulseScale), "impulseScale" }
		};
		sList.members = sMembers;
		sList.count = 11;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10433DE0
// FUNCTION: ENGINE 0x103FF3C0
// FUNCTION: ENGINE 0x10433DF0
// FUNCTION: ENGINE 0x10438550
// FUNCTION: ENGINE 0x10438590
// FUNCTION: ENGINE 0x1043ADD0
// FUNCTION: ENGINE 0x1043AE30
// FUNCTION: ENGINE 0x1043AE90
// FUNCTION: ENGINE 0x1043AEF0
// FUNCTION: ENGINE 0x1043AF50
// FUNCTION: ENGINE 0x1043AFB0
// FUNCTION: ENGINE 0x1043B010
// FUNCTION: ENGINE 0x1043B070
// FUNCTION: ENGINE 0x1043FA90
