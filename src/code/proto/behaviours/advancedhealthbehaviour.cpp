#include "code/proto/behaviours/advancedhealthbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x102B5D60
	content::ClassInfo* AdvancedHealthBehaviour::DamageScale::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AdvancedHealthBehaviour::DamageScale";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102B5DA0
	content::ClassInfo* AdvancedHealthBehaviour::ChargeRequired::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AdvancedHealthBehaviour::ChargeRequired";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102B5DE0
	content::ClassInfo* AdvancedHealthBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AdvancedHealthBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102B5E20
	// EQUIVALENT: instruction selection; the engine loads the constant into a register once and stores it 34 times, ours stores it as an immediate each time (2.2 %)
	AdvancedHealthBehaviour::DamageScale::DamageScale()
	{
		unknown0 = 1.0f;
		susceptibleToBare = 1.0f;
		susceptibleToClaws = 1.0f;
		susceptibleToBlades = 1.0f;
		susceptibleToHammerfist = 1.0f;
		susceptibleToWhipfist = 1.0f;
		susceptibleToWeapon = 1.0f;
		susceptibleToShield = 1.0f;
		susceptibleToThrow = 1.0f;
		susceptibleToBullet = 1.0f;
		susceptibleToSniper = 1.0f;
		susceptibleToMissile = 1.0f;
		susceptibleToMissileExplosion = 1.0f;
		susceptibleToPropExplosion = 1.0f;
		susceptibleToDevastatorGroundSpike = 1.0f;
		susceptibleToGroundSpike = 1.0f;
		susceptibleToTankCrush = 1.0f;
		susceptibleToScript = 1.0f;
		susceptibleToMomentum = 1.0f;
		susceptibleToBloodtoxPoison = 1.0f;
		susceptibleToLeaderHunterPoison = 1.0f;
		susceptibleToDevastatorExplosion = 1.0f;
		susceptibleToDevastatorTendril = 1.0f;
		susceptibleToHunter = 1.0f;
		susceptibleToHelicopterRotor = 1.0f;
		susceptibleToInfected1 = 1.0f;
		susceptibleToInfected2 = 1.0f;
		susceptibleToHydra = 1.0f;
		susceptibleToThermobaric = 1.0f;
		unknown74 = 1.0f;
		unknown78 = 1.0f;
		unknown7C = 1.0f;
		susceptibleToSupremeHunter = 1.0f;
		susceptibleToObstacleBash = 1.0f;
	}

	// FUNCTION: ENGINE 0x102B5EB0
	// EQUIVALENT: instruction selection; the engine zeroes a register once and stores it 34 times, ours stores a zero from an SSE register each time (2.2 %)
	AdvancedHealthBehaviour::ChargeRequired::ChargeRequired()
	{
		unknown0 = 0.0f;
		chargeBare = 0.0f;
		chargeClaws = 0.0f;
		chargeBlades = 0.0f;
		chargeHammerfist = 0.0f;
		chargeWhipfist = 0.0f;
		unknown18 = 0.0f;
		chargeShield = 0.0f;
		chargeThrow = 0.0f;
		unknown24 = 0.0f;
		unknown28 = 0.0f;
		unknown2C = 0.0f;
		unknown30 = 0.0f;
		unknown34 = 0.0f;
		unknown38 = 0.0f;
		chargeGroundSpike = 0.0f;
		unknown40 = 0.0f;
		unknown44 = 0.0f;
		unknown48 = 0.0f;
		unknown4C = 0.0f;
		unknown50 = 0.0f;
		unknown54 = 0.0f;
		unknown58 = 0.0f;
		unknown5C = 0.0f;
		unknown60 = 0.0f;
		unknown64 = 0.0f;
		unknown68 = 0.0f;
		unknown6C = 0.0f;
		unknown70 = 0.0f;
		unknown74 = 0.0f;
		unknown78 = 0.0f;
		unknown7C = 0.0f;
		unknown80 = 0.0f;
		unknown84 = 0.0f;
	}

	// FUNCTION: ENGINE 0x102B6F30
	content::MemberList* AdvancedHealthBehaviour::DamageScale::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 0>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToBare), "susceptibleToBare" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 1>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToClaws), "susceptibleToClaws" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 2>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToBlades), "susceptibleToBlades" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 3>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToHammerfist), "susceptibleToHammerfist" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 4>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToWhipfist), "susceptibleToWhipfist" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 5>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToWeapon), "susceptibleToWeapon" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 6>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToShield), "susceptibleToShield" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 7>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToThrow), "susceptibleToThrow" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 8>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToBullet), "susceptibleToBullet" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 9>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToSniper), "susceptibleToSniper" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 10>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToMissile), "susceptibleToMissile" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 11>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToMissileExplosion), "susceptibleToMissileExplosion" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 12>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToPropExplosion), "susceptibleToPropExplosion" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 13>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToGroundSpike), "susceptibleToGroundSpike" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 14>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToTankCrush), "susceptibleToTankCrush" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 15>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToScript), "susceptibleToScript" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 16>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToMomentum), "susceptibleToMomentum" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 17>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToBloodtoxPoison), "susceptibleToBloodtoxPoison" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 18>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToLeaderHunterPoison), "susceptibleToLeaderHunterPoison" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 19>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToDevastatorExplosion), "susceptibleToDevastatorExplosion" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 20>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToDevastatorTendril), "susceptibleToDevastatorTendril" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 21>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToHunter), "susceptibleToHunter" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 22>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToHelicopterRotor), "susceptibleToHelicopterRotor" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 23>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToInfected1), "susceptibleToInfected1" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 24>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToInfected2), "susceptibleToInfected2" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 25>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToHydra), "susceptibleToHydra" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 26>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToThermobaric), "susceptibleToThermobaric" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 27>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToSupremeHunter), "susceptibleToSupremeHunter" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 28>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToObstacleBash), "susceptibleToObstacleBash" },
			{ content::GetMemberPrimitiveMetaType<DamageScale, float, 29>("p"),
				PROTO_OFFSET(DamageScale, susceptibleToDevastatorGroundSpike), "susceptibleToDevastatorGroundSpike" }
		};
		sList.members = sMembers;
		sList.count = 30;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102B7580
	content::MemberList* AdvancedHealthBehaviour::ChargeRequired::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<ChargeRequired, float, 0>("p"),
				PROTO_OFFSET(ChargeRequired, chargeBare), "chargeBare" },
			{ content::GetMemberPrimitiveMetaType<ChargeRequired, float, 1>("p"),
				PROTO_OFFSET(ChargeRequired, chargeClaws), "chargeClaws" },
			{ content::GetMemberPrimitiveMetaType<ChargeRequired, float, 2>("p"),
				PROTO_OFFSET(ChargeRequired, chargeBlades), "chargeBlades" },
			{ content::GetMemberPrimitiveMetaType<ChargeRequired, float, 3>("p"),
				PROTO_OFFSET(ChargeRequired, chargeHammerfist), "chargeHammerfist" },
			{ content::GetMemberPrimitiveMetaType<ChargeRequired, float, 4>("p"),
				PROTO_OFFSET(ChargeRequired, chargeWhipfist), "chargeWhipfist" },
			{ content::GetMemberPrimitiveMetaType<ChargeRequired, float, 5>("p"),
				PROTO_OFFSET(ChargeRequired, chargeShield), "chargeShield" },
			{ content::GetMemberPrimitiveMetaType<ChargeRequired, float, 6>("p"),
				PROTO_OFFSET(ChargeRequired, chargeThrow), "chargeThrow" },
			{ content::GetMemberPrimitiveMetaType<ChargeRequired, float, 7>("p"),
				PROTO_OFFSET(ChargeRequired, chargeGroundSpike), "chargeGroundSpike" }
		};
		sList.members = sMembers;
		sList.count = 8;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102B81F0
	content::MemberList* AdvancedHealthBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<HealthBehaviour>();
		static content::BaseClassCasterImpl<HealthBehaviour, AdvancedHealthBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<AdvancedHealthBehaviour, float, 0>("p"),
				PROTO_OFFSET(AdvancedHealthBehaviour, regenTimeWithNoDamage), "regenTimeWithNoDamage" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHealthBehaviour, float, 1>("p"),
				PROTO_OFFSET(AdvancedHealthBehaviour, regenRate), "regenRate" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHealthBehaviour, float, 2>("p"),
				PROTO_OFFSET(AdvancedHealthBehaviour, regenMaxHealthPercentage), "regenMaxHealthPercentage" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHealthBehaviour, float, 3>("p"),
				PROTO_OFFSET(AdvancedHealthBehaviour, accumDamageDecayRate), "accumDamageDecayRate" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHealthBehaviour, float, 4>("p"),
				PROTO_OFFSET(AdvancedHealthBehaviour, accumDamageExpiryTime), "accumDamageExpiryTime" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHealthBehaviour, float, 5>("p"),
				PROTO_OFFSET(AdvancedHealthBehaviour, npcDamageMultiplier), "npcDamageMultiplier" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHealthBehaviour, float, 6>("p"),
				PROTO_OFFSET(AdvancedHealthBehaviour, commanderInfluenceDamageMultiplier),
				"commanderInfluenceDamageMultiplier" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHealthBehaviour, bool, 0>("p"),
				PROTO_OFFSET(AdvancedHealthBehaviour, respondOnlyToPlayerDamage), "respondOnlyToPlayerDamage" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHealthBehaviour, bool, 1>("p"),
				PROTO_OFFSET(AdvancedHealthBehaviour, proportionalDamageScale), "proportionalDamageScale" },
			{ content::GetEnumMetaType<DamageType>(), 0x19C, "scaleDownDamageType" },
			{ content::GetClassMetaType<DamageScale>(), PROTO_OFFSET(AdvancedHealthBehaviour, damageScaleByType),
				"damageScaleByType" },
			{ content::GetClassMetaType<ChargeRequired>(),
				PROTO_OFFSET(AdvancedHealthBehaviour, chargeRequiredForType), "chargeRequiredForType" },
			{ content::GetMemberPrimitiveMetaType<AdvancedHealthBehaviour, float, 7>("p"),
				PROTO_OFFSET(AdvancedHealthBehaviour, chargeRequiredForMuscleMassBareAttack),
				"chargeRequiredForMuscleMassBareAttack" }
		};
		sList.members = sMembers;
		sList.count = 13;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102B60E0
// FUNCTION: ENGINE 0x102B6170
// FUNCTION: ENGINE 0x102B6180
// FUNCTION: ENGINE 0x102B61C0
// FUNCTION: ENGINE 0x102B61D0
// FUNCTION: ENGINE 0x102B6330
// FUNCTION: ENGINE 0x102B6370
// FUNCTION: ENGINE 0x102B63B0
// FUNCTION: ENGINE 0x102B63F0
// FUNCTION: ENGINE 0x102B6430
// FUNCTION: ENGINE 0x102B6470
// FUNCTION: ENGINE 0x102B64B0
// FUNCTION: ENGINE 0x102B64F0
// FUNCTION: ENGINE 0x102B6530
// FUNCTION: ENGINE 0x102B6570
// FUNCTION: ENGINE 0x102B65B0
// FUNCTION: ENGINE 0x102B65F0
// FUNCTION: ENGINE 0x102B6630
// FUNCTION: ENGINE 0x102B6670
// FUNCTION: ENGINE 0x102B66B0
// FUNCTION: ENGINE 0x102B66F0
// FUNCTION: ENGINE 0x102B6730
// FUNCTION: ENGINE 0x102B6770
// FUNCTION: ENGINE 0x102B67B0
// FUNCTION: ENGINE 0x102B67F0
// FUNCTION: ENGINE 0x102B6830
// FUNCTION: ENGINE 0x102B6870
// FUNCTION: ENGINE 0x102B68B0
// FUNCTION: ENGINE 0x102B68F0
// FUNCTION: ENGINE 0x102B6930
// FUNCTION: ENGINE 0x102B6970
// FUNCTION: ENGINE 0x102B69B0
// FUNCTION: ENGINE 0x102B69F0
// FUNCTION: ENGINE 0x102B6A30
// FUNCTION: ENGINE 0x102B6A70
// FUNCTION: ENGINE 0x102B6AB0
// FUNCTION: ENGINE 0x102B6AF0
// FUNCTION: ENGINE 0x102B6B30
// FUNCTION: ENGINE 0x102B6B70
// FUNCTION: ENGINE 0x102B6BB0
// FUNCTION: ENGINE 0x102B6BF0
// FUNCTION: ENGINE 0x102B6C30
// FUNCTION: ENGINE 0x102B6C70
// FUNCTION: ENGINE 0x102B6CB0
// FUNCTION: ENGINE 0x102B6CF0
// FUNCTION: ENGINE 0x102B6D30
// FUNCTION: ENGINE 0x102B6D70
// FUNCTION: ENGINE 0x102B6DB0
// FUNCTION: ENGINE 0x102B6DF0
// FUNCTION: ENGINE 0x102B6E30
// FUNCTION: ENGINE 0x102B6E70
// FUNCTION: ENGINE 0x102B6EB0
// FUNCTION: ENGINE 0x102B6EF0
// FUNCTION: ENGINE 0x102B8130
// FUNCTION: ENGINE 0x102B8190
