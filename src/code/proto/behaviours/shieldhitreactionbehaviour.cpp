#include "code/proto/behaviours/shieldhitreactionbehaviour.h"
#include "code/core/refptr.h"
#include "code/ravenphysics/context.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x102C48D0
	ShieldHitReactionBehaviour::ShieldHitReactionBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		hitsA(0), hitsB(0), reflecting(false), reflectingIntersectionProperties(0)
	{
		Listen(0x14, true);
		Listen(0x1e, true);
	}

	// FUNCTION: ENGINE 0x102C4AB0
	ShieldHitReactionBehaviour::~ShieldHitReactionBehaviour()
	{
		core::SafeRelease(reflectingIntersectionProperties);
	}

	// FUNCTION: ENGINE 0x102C4890
	content::ClassInfo* ShieldHitReactionBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ShieldHitReactionBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102C4D30
	content::MemberList* ShieldHitReactionBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, ShieldHitReactionBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<ShieldHitReactionBehaviour, ravenphysics::IntersectionPropertiesLoader>("p"),
				PROTO_OFFSET(ShieldHitReactionBehaviour, reflectingIntersectionProperties),
				"reflectingIntersectionProperties" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}
