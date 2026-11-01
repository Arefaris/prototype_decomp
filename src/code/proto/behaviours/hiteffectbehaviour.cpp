#include "code/proto/behaviours/hiteffectbehaviour.h"
#include "code/engine/fight/fightcommon.h"

namespace ravenphysics
{
	// 0x10D977E4: 1000.0f in the pooled constants (name guess)
	extern const float gDefaultMaxForce;
}

namespace engine
{
	namespace driving
	{
		// 0x10D95578: 2.0f in the pooled constants (name guess)
		extern const float gTwo;
	}
}

namespace proto
{
	// 0x10D977EC: 10.0f in the pooled constants (name guess)
	extern const float gTen;

#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	AnalyseCollisionParams* gAnalyseCollisionParams;  // 0x1126F6A0
	MomentumDamageParams* gMomentumDamageParams;  // 0x1126F6A4

	// FUNCTION: ENGINE 0x105112E0
	content::ClassInfo* AnalyseCollisionParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AnalyseCollisionParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10511320
	content::ClassInfo* MomentumEntry::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::MomentumEntry";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10511360
	content::ClassInfo* MomentumDamageParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::MomentumDamageParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x105113A0
	content::ClassInfo* HitEffectBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HitEffectBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x105113E0
	AnalyseCollisionParams::~AnalyseCollisionParams()
	{
		gAnalyseCollisionParams = 0;
	}

	// FUNCTION: ENGINE 0x10511400
	HitEffectBehaviour::HitEffectBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), unknownC(0)
	{
		Listen(5, true);
	}

	// FUNCTION: ENGINE 0x10511440
	HitEffectBehaviour::~HitEffectBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10511450
	void HitEffectBehaviour::Slot1()
	{
	}

	// FUNCTION: ENGINE 0x105115D0
	// EQUIVALENT: scheduling; the engine loads the two repeated constants before it stores the base class's words and writes the class's vftable in the middle of the member stores, ours loads them after the base stores and writes both vftables first (51 %)
	AnalyseCollisionParams::AnalyseCollisionParams()
	{
		float force = ravenphysics::gDefaultMaxForce;
		float one = engine::driving::gOne;
		impactThreshold = force;
		slideThreshold = force;
		slideMaxNormalVelocity = engine::driving::gTwo;
		impactMinNormalVelocity = one;
		impactMinIntervalMilliseconds = 0;
		impactEffectScale = one;
		slideMinTangentialVelocity = gTen;
		slideEffectScaleX = one;
		slideEffectScaleY = one;
		gAnalyseCollisionParams = this;
	}

	// FUNCTION: ENGINE 0x10511680
	MomentumEntry::MomentumEntry() : damage(0.0f), momentum(0.0f), effectTemplate(0, 1)
	{
	}

	// FUNCTION: ENGINE 0x105116B0
	MomentumEntry::~MomentumEntry()
	{
	}

	// FUNCTION: ENGINE 0x105116C0
	// NONMATCHING: the engine reads the table's start again where it needs it and walks the entries with one register, ours keeps the start in a second register (8.6 %)
#ifdef NONMATCHING
	MomentumEntry* MomentumDamageParams::Lookup(float value, float* damage)
	{
		int count = momentum.Size();
		int index = 0;
		if (0 < count)
		{
			float* cursor = &momentum.begin->damage;
			float previousMomentum = 0.0f;
			float previousDamage = 0.0f;
			do
			{
				float entryMomentum = cursor[1];
				float entryDamage = cursor[0];
				if (value < entryMomentum)
				{
					float fraction = (value - previousMomentum) / (entryMomentum - previousMomentum);
					*damage = (engine::driving::gOne - fraction) * previousDamage + fraction * entryDamage;
					return momentum.begin + index;
				}
				index++;
				cursor += 6;
				previousMomentum = entryMomentum;
				previousDamage = entryDamage;
			}
			while (index < count);
		}
		MomentumEntry* last = momentum.begin + (count - 1);
		*damage = last->damage;
		return last;
	}
#endif

	// FUNCTION: ENGINE 0x10511DF0
	content::MemberList* AnalyseCollisionParams::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<AnalyseCollisionParams, float, 0>("p"),
				PROTO_OFFSET(AnalyseCollisionParams, impactThreshold), "impactThreshold" },
			{ content::GetMemberPrimitiveMetaType<AnalyseCollisionParams, float, 1>("p"),
				PROTO_OFFSET(AnalyseCollisionParams, impactMinNormalVelocity), "impactMinNormalVelocity" },
			{ content::GetMemberPrimitiveMetaType<AnalyseCollisionParams, unsigned int, 0>("p"),
				PROTO_OFFSET(AnalyseCollisionParams, impactMinIntervalMilliseconds), "impactMinIntervalMilliseconds" },
			{ content::GetMemberPrimitiveMetaType<AnalyseCollisionParams, float, 2>("p"),
				PROTO_OFFSET(AnalyseCollisionParams, impactEffectScale), "impactEffectScale" },
			{ content::GetMemberPrimitiveMetaType<AnalyseCollisionParams, float, 3>("p"),
				PROTO_OFFSET(AnalyseCollisionParams, slideThreshold), "slideThreshold" },
			{ content::GetMemberPrimitiveMetaType<AnalyseCollisionParams, float, 4>("p"),
				PROTO_OFFSET(AnalyseCollisionParams, slideMaxNormalVelocity), "slideMaxNormalVelocity" },
			{ content::GetMemberPrimitiveMetaType<AnalyseCollisionParams, float, 5>("p"),
				PROTO_OFFSET(AnalyseCollisionParams, slideMinTangentialVelocity), "slideMinTangentialVelocity" },
			{ content::GetMemberPrimitiveMetaType<AnalyseCollisionParams, float, 6>("p"),
				PROTO_OFFSET(AnalyseCollisionParams, slideEffectScaleX), "slideEffectScaleX" },
			{ content::GetMemberPrimitiveMetaType<AnalyseCollisionParams, float, 7>("p"),
				PROTO_OFFSET(AnalyseCollisionParams, slideEffectScaleY), "slideEffectScaleY" }
		};
		sList.members = sMembers;
		sList.count = 9;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10512020
	content::MemberList* MomentumEntry::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<MomentumEntry, float, 0>("p"),
				PROTO_OFFSET(MomentumEntry, damage), "damage" },
			{ content::GetMemberPrimitiveMetaType<MomentumEntry, float, 1>("p"),
				PROTO_OFFSET(MomentumEntry, momentum), "momentum" },
			{ content::GetNameMetaType<MomentumEntry>(true, true, "p"),
				PROTO_NAME_OFFSET(MomentumEntry, effectTemplate), "template" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10512130
	content::MemberList* HitEffectBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, HitEffectBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10512500
	content::MemberList* MomentumDamageParams::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<MomentumDamageParams, MomentumArray>(content::GetClassMetaType<MomentumEntry>(), "p"),
				PROTO_OFFSET(MomentumDamageParams, momentum), "momentum" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10513240
	MomentumDamageParams::MomentumDamageParams()
	{
		gMomentumDamageParams = this;
	}

	// FUNCTION: ENGINE 0x10513270
	// NONMATCHING: the engine empties the table with the array's out-of-line Clear and frees its block; the array's destructor here destroys the elements inline (21.8 %)
#ifdef NONMATCHING
	MomentumDamageParams::~MomentumDamageParams()
	{
		gMomentumDamageParams = 0;
	}
#endif

	// FUNCTION: ENGINE 0x105132C0
	void HitEffectBehaviour::OnMessage(engine::Message* message)
	{
		if (message->type == 5)
		{
			OnHit(message);
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10511460
// FUNCTION: ENGINE 0x10511530
// FUNCTION: ENGINE 0x10511570
// FUNCTION: ENGINE 0x10511580
// FUNCTION: ENGINE 0x10511590
// FUNCTION: ENGINE 0x105117C0
// FUNCTION: ENGINE 0x105117D0
// FUNCTION: ENGINE 0x10511810
// FUNCTION: ENGINE 0x10511850
// FUNCTION: ENGINE 0x10511890
// FUNCTION: ENGINE 0x105118D0
// FUNCTION: ENGINE 0x10511910
// FUNCTION: ENGINE 0x10511950
// FUNCTION: ENGINE 0x10511990
// FUNCTION: ENGINE 0x105119D0
// FUNCTION: ENGINE 0x10511A10
// FUNCTION: ENGINE 0x10511A50
// FUNCTION: ENGINE 0x10511A90
// FUNCTION: ENGINE 0x10511AC0
// FUNCTION: ENGINE 0x10511B20
// FUNCTION: ENGINE 0x10511B80
// FUNCTION: ENGINE 0x10511BD0
// FUNCTION: ENGINE 0x10511C10
// FUNCTION: ENGINE 0x10511CF0
// FUNCTION: ENGINE 0x10511D30
// FUNCTION: ENGINE 0x10511D90
// FUNCTION: ENGINE 0x105121E0
// FUNCTION: ENGINE 0x10512280
// FUNCTION: ENGINE 0x10512410
// FUNCTION: ENGINE 0x105131F0
// FUNCTION: ENGINE 0x105115A0
// FUNCTION: ENGINE 0x10511650
// FUNCTION: ENGINE 0x10511790
// FUNCTION: ENGINE 0x10511AD0
// FUNCTION: ENGINE 0x10511B00
// FUNCTION: ENGINE 0x10511C40
// FUNCTION: ENGINE 0x10511C60
// FUNCTION: ENGINE 0x105121B0
// FUNCTION: ENGINE 0x10513130
// FUNCTION: ENGINE 0x10513180
// FUNCTION: ENGINE 0x10513320
// FUNCTION: ENGINE 0x10513350
