#include "code/proto/behaviours/advancedhitreactionbehaviour.h"

namespace choreo
{
	// 0x10D94FF8: -1.0f in the pooled constants (name from its symbol)
	extern const float gMinusOne;
}

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x102B8550
	content::ClassInfo* AdvancedHitReactionBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AdvancedHitReactionBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102BA930
	// EQUIVALENT: scheduling; the engine stores the vftable after the load of the second constant, ours right after the base class's constructor (80.6 %)
	AdvancedHitReactionBehaviour::AdvancedHitReactionBehaviour(engine::GameObject* newOwner)
		: HitReactionBehaviour(newOwner)
	{
		hydraImpulsePointScaleOverride = choreo::gMinusOne;
		float one = engine::driving::gOne;
		unknownA0 = 0;
		for (int i = 0; i < ATTACK_TYPE_COUNT; i++)
		{
			impulseScale[i] = one;
			interruptible[i] = false;
		}
		Listen(0x14, true);
	}

	// FUNCTION: ENGINE 0x102B99F0
	content::MemberList* AdvancedHitReactionBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<HitReactionBehaviour>();
		static content::BaseClassCasterImpl<HitReactionBehaviour, AdvancedHitReactionBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 0>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[0]), "impulseScale_None" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 1>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[1]), "impulseScale_Bare" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 2>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[2]), "impulseScale_Claws" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 3>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[3]), "impulseScale_Blades" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 4>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[4]), "impulseScale_Hammerfist" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 5>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[5]), "impulseScale_Whipfist" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 6>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[6]), "impulseScale_Weapon" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 7>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[7]), "impulseScale_Shield" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 8>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[8]), "impulseScale_Throw" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 9>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[9]), "impulseScale_Bullet" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 10>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[10]), "impulseScale_Sniper" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 11>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[11]), "impulseScale_Missile" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 12>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[12]), "impulseScale_MissileExplosion" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 13>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[13]), "impulseScale_PropExplosion" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 14>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[14]), "impulseScale_DevastatorGroundSpike" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 15>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[15]), "impulseScale_GroundSpike" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 16>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[16]), "impulseScale_TankCrush" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 17>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[17]), "impulseScale_Script" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 18>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[18]), "impulseScale_Momentum" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 19>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[19]), "impulseScale_BloodtoxPoison" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 20>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[20]), "impulseScale_LeaderHunterPoison" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 21>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[21]), "impulseScale_DevastatorExplosion" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 22>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[22]), "impulseScale_DevastatorTendril" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 23>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[23]), "impulseScale_Hunter" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 24>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[24]), "impulseScale_HelicopterRotor" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 25>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[25]), "impulseScale_Infected1" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 26>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[26]), "impulseScale_Infected2" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 27>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[27]), "impulseScale_Hydra" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 28>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[28]), "impulseScale_Thermobaric" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 29>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[29]), "impulseScale_HiveKill" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 30>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[30]), "impulseScale_SoldierPush" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 31>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[31]), "impulseScale_AmbientVehicle" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 32>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[32]), "impulseScale_SupremeHunter" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 33>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, impulseScale[33]), "impulseScale_ObstacleBash" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 0>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[0]), "interruptible_None" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 1>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[1]), "interruptible_Bare" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 2>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[2]), "interruptible_Claws" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 3>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[3]), "interruptible_Blades" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 4>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[4]), "interruptible_Hammerfist" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 5>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[5]), "interruptible_Whipfist" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 6>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[6]), "interruptible_Weapon" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 7>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[7]), "interruptible_Shield" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 8>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[8]), "interruptible_Throw" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 9>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[9]), "interruptible_Bullet" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 10>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[10]), "interruptible_Sniper" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 11>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[11]), "interruptible_Missile" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 12>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[12]), "interruptible_MissileExplosion" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 13>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[13]), "interruptible_PropExplosion" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 14>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[14]), "interruptible_DevastatorGroundSpike" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 15>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[15]), "interruptible_GroundSpike" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 16>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[16]), "interruptible_TankCrush" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 17>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[17]), "interruptible_Script" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 18>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[18]), "interruptible_Momentum" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 19>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[19]), "interruptible_BloodtoxPoison" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 20>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[20]), "interruptible_LeaderHunterPoison" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 21>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[21]), "interruptible_DevastatorExplosion" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 22>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[22]), "interruptible_DevastatorTendril" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 23>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[23]), "interruptible_Hunter" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 24>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[24]), "interruptible_HelicopterRotor" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 25>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[25]), "interruptible_Infected1" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 26>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[26]), "interruptible_Infected2" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 27>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[27]), "interruptible_Hydra" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 28>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[28]), "interruptible_Thermobaric" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 29>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[29]), "interruptible_HiveKill" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 30>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[30]), "interruptible_SoldierPush" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 31>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[31]), "interruptible_AmbientVehicle" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 32>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[32]), "interruptible_SupremeHunter" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, bool, 33>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, interruptible[33]), "interruptible_ObstacleBash" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHitReactionBehaviour, float, 34>("p"),
				PROTO_OFFSET(AdvancedHitReactionBehaviour, hydraImpulsePointScaleOverride), "hydraImpulsePointScaleOverride" }
		};
		sList.members = sMembers;
		sList.count = 69;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102B8590
// FUNCTION: ENGINE 0x102B8630
// FUNCTION: ENGINE 0x102B8640
// FUNCTION: ENGINE 0x102B8670
// FUNCTION: ENGINE 0x102B88F0
// FUNCTION: ENGINE 0x102B8930
// FUNCTION: ENGINE 0x102B8970
// FUNCTION: ENGINE 0x102B89B0
// FUNCTION: ENGINE 0x102B89F0
// FUNCTION: ENGINE 0x102B8A30
// FUNCTION: ENGINE 0x102B8A70
// FUNCTION: ENGINE 0x102B8AB0
// FUNCTION: ENGINE 0x102B8AF0
// FUNCTION: ENGINE 0x102B8B30
// FUNCTION: ENGINE 0x102B8B70
// FUNCTION: ENGINE 0x102B8BB0
// FUNCTION: ENGINE 0x102B8BF0
// FUNCTION: ENGINE 0x102B8C30
// FUNCTION: ENGINE 0x102B8C70
// FUNCTION: ENGINE 0x102B8CB0
// FUNCTION: ENGINE 0x102B8CF0
// FUNCTION: ENGINE 0x102B8D30
// FUNCTION: ENGINE 0x102B8D70
// FUNCTION: ENGINE 0x102B8DB0
// FUNCTION: ENGINE 0x102B8DF0
// FUNCTION: ENGINE 0x102B8E30
// FUNCTION: ENGINE 0x102B8E70
// FUNCTION: ENGINE 0x102B8EB0
// FUNCTION: ENGINE 0x102B8EF0
// FUNCTION: ENGINE 0x102B8F30
// FUNCTION: ENGINE 0x102B8F70
// FUNCTION: ENGINE 0x102B8FB0
// FUNCTION: ENGINE 0x102B8FF0
// FUNCTION: ENGINE 0x102B9030
// FUNCTION: ENGINE 0x102B9070
// FUNCTION: ENGINE 0x102B90B0
// FUNCTION: ENGINE 0x102B90F0
// FUNCTION: ENGINE 0x102B9130
// FUNCTION: ENGINE 0x102B9170
// FUNCTION: ENGINE 0x102B91B0
// FUNCTION: ENGINE 0x102B91F0
// FUNCTION: ENGINE 0x102B9230
// FUNCTION: ENGINE 0x102B9270
// FUNCTION: ENGINE 0x102B92B0
// FUNCTION: ENGINE 0x102B92F0
// FUNCTION: ENGINE 0x102B9330
// FUNCTION: ENGINE 0x102B9370
// FUNCTION: ENGINE 0x102B93B0
// FUNCTION: ENGINE 0x102B93F0
// FUNCTION: ENGINE 0x102B9430
// FUNCTION: ENGINE 0x102B9470
// FUNCTION: ENGINE 0x102B94B0
// FUNCTION: ENGINE 0x102B94F0
// FUNCTION: ENGINE 0x102B9530
// FUNCTION: ENGINE 0x102B9570
// FUNCTION: ENGINE 0x102B95B0
// FUNCTION: ENGINE 0x102B95F0
// FUNCTION: ENGINE 0x102B9630
// FUNCTION: ENGINE 0x102B9670
// FUNCTION: ENGINE 0x102B96B0
// FUNCTION: ENGINE 0x102B96F0
// FUNCTION: ENGINE 0x102B9730
// FUNCTION: ENGINE 0x102B9770
// FUNCTION: ENGINE 0x102B97B0
// FUNCTION: ENGINE 0x102B97F0
// FUNCTION: ENGINE 0x102B9830
// FUNCTION: ENGINE 0x102B9870
// FUNCTION: ENGINE 0x102B98B0
// FUNCTION: ENGINE 0x102B98F0
// FUNCTION: ENGINE 0x102B9930
// FUNCTION: ENGINE 0x102B9970
// FUNCTION: ENGINE 0x102B99B0
// FUNCTION: ENGINE 0x102BA9B0
// FUNCTION: ENGINE 0x102BA9C0
