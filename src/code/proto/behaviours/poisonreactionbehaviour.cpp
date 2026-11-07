#include "code/proto/behaviours/poisonreactionbehaviour.h"
#include "code/math/random.h"
#include "code/proto/behaviours/healthbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x102C0BF0
	// NONMATCHING: the arithmetic and the generator steps are right; the engine keeps the generator's second state in
	// a pointer register of its own (push esi) where ours reuses the scratch registers (about 21 %)
#ifdef NONMATCHING
	float PoisonInformation::GetNextHitTime() const
	{
		float low = timeBetweenHits;
		float spread = extraRandomTime;
		return math::gRandom->NextFloat01() * spread + low;
	}
#endif

	// FUNCTION: ENGINE 0x102C1330
	void PoisonReactionBehaviour::ClearPoisons(engine::Message* message)
	{
		for (unsigned int i = 0; i < poisonInformations.Size(); i++)
		{
			PoisonInformation& info = poisonInformations[i];
			info.active = false;
			info.sources.Reset();
			info.elapsed = 0.0f;
			info.hitTimer = 0.0f;
		}
	}

	// FUNCTION: ENGINE 0x102C2620
	PoisonReactionBehaviour::PoisonReactionBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner)
	{
		Listen2(8, true);
		Listen(0x14, true);
		Listen(2, true);
	}

	// FUNCTION: ENGINE 0x102C2680
	PoisonReactionBehaviour::~PoisonReactionBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x102C1EE0
	PoisonInformation::PoisonInformation() : active(false), damageRate(0.0f), damageSpikes(0.0f), timeBetweenHits(0.0f),
		extraRandomTime(0.0f), poisonExpiry(0.0f), poisonType(ATTACK_TYPE_BLOODTOX_POISON), hitTimer(0.0f), elapsed(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x102C1F30
	PoisonInformation::~PoisonInformation()
	{
	}

	// FUNCTION: ENGINE 0x102C0B50
	content::ClassInfo* PoisonInformation::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::PoisonInformation";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102C0B90
	content::ClassInfo* PoisonReactionBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::PoisonReactionBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102C11A0
	content::MemberList* PoisonInformation::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<PoisonInformation, float, 0>("p"),
				PROTO_OFFSET(PoisonInformation, damageRate), "damageRate" },
			{ content::GetMemberPrimitiveMetaType<PoisonInformation, float, 1>("p"),
				PROTO_OFFSET(PoisonInformation, damageSpikes), "damageSpikes" },
			{ content::GetMemberPrimitiveMetaType<PoisonInformation, float, 2>("p"),
				PROTO_OFFSET(PoisonInformation, timeBetweenHits), "timeBetweenHits" },
			{ content::GetEnumMetaType<AttackType>(), 0x18, "poisonType" },
			{ content::GetMemberPrimitiveMetaType<PoisonInformation, float, 3>("p"),
				PROTO_OFFSET(PoisonInformation, poisonExpiry), "poisonExpiry" },
			{ content::GetMemberPrimitiveMetaType<PoisonInformation, float, 4>("p"),
				PROTO_OFFSET(PoisonInformation, extraRandomTime), "extraRandomTime" }
		};
		sList.members = sMembers;
		sList.count = 6;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102C1E00
	content::MemberList* PoisonReactionBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, PoisonReactionBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<PoisonReactionBehaviour, PoisonArray>(
				content::GetClassMetaType<PoisonInformation>(), "p"),
				PROTO_OFFSET(PoisonReactionBehaviour, poisonInformations), "poisonInformations" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}
