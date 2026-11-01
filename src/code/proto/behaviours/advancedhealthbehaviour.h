// proto::AdvancedHealthBehaviour (RTTI and reflection names; base proto::HealthBehaviour): a health that regenerates,
// scales the damage by its type and asks for a charge before some attacks hurt it. Its two tables are classes of their
// own: proto::AdvancedHealthBehaviour::DamageScale (the damage a type of attack does) and ::ChargeRequired (the charge a
// type of attack needs). The base of the base, hunter, mother and prototype health behaviours. Unit 0x102B5D60 -
// 0x102B8550 (no assert path; the file name is a guess). The reflected names are original, the rest is guessed; only the
// reflection is reconstructed.
#ifndef PROTO_BEHAVIOURS_ADVANCEDHEALTHBEHAVIOUR_H
#define PROTO_BEHAVIOURS_ADVANCEDHEALTHBEHAVIOUR_H

#include "code/proto/behaviours/healthbehaviour.h"

namespace proto
{
	class AdvancedHealthBehaviour : public HealthBehaviour
	{
	public:
		// The damage scale of each type of attack (RTTI proto::AdvancedHealthBehaviour::DamageScale; 0x88 bytes)
		struct DamageScale
		{
			// 0x102B5E20
			DamageScale();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			float unknown0;  // +0x0
			float susceptibleToBare;  // +0x4
			float susceptibleToClaws;  // +0x8
			float susceptibleToBlades;  // +0xC
			float susceptibleToHammerfist;  // +0x10
			float susceptibleToWhipfist;  // +0x14
			float susceptibleToWeapon;  // +0x18
			float susceptibleToShield;  // +0x1C
			float susceptibleToThrow;  // +0x20
			float susceptibleToBullet;  // +0x24
			float susceptibleToSniper;  // +0x28
			float susceptibleToMissile;  // +0x2C
			float susceptibleToMissileExplosion;  // +0x30
			float susceptibleToPropExplosion;  // +0x34
			float susceptibleToDevastatorGroundSpike;  // +0x38
			float susceptibleToGroundSpike;  // +0x3C
			float susceptibleToTankCrush;  // +0x40
			float susceptibleToScript;  // +0x44
			float susceptibleToMomentum;  // +0x48
			float susceptibleToBloodtoxPoison;  // +0x4C
			float susceptibleToLeaderHunterPoison;  // +0x50
			float susceptibleToDevastatorExplosion;  // +0x54
			float susceptibleToDevastatorTendril;  // +0x58
			float susceptibleToHunter;  // +0x5C
			float susceptibleToHelicopterRotor;  // +0x60
			float susceptibleToInfected1;  // +0x64
			float susceptibleToInfected2;  // +0x68
			float susceptibleToHydra;  // +0x6C
			float susceptibleToThermobaric;  // +0x70
			float unknown74;  // +0x74
			float unknown78;  // +0x78
			float unknown7C;  // +0x7C
			float susceptibleToSupremeHunter;  // +0x80
			float susceptibleToObstacleBash;  // +0x84
		};

		// The charge each type of attack needs (RTTI proto::AdvancedHealthBehaviour::ChargeRequired; 0x88 bytes)
		struct ChargeRequired
		{
			// 0x102B5EB0
			ChargeRequired();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			float unknown0;  // +0x0
			float chargeBare;  // +0x4
			float chargeClaws;  // +0x8
			float chargeBlades;  // +0xC
			float chargeHammerfist;  // +0x10
			float chargeWhipfist;  // +0x14
			float unknown18;  // +0x18
			float chargeShield;  // +0x1C
			float chargeThrow;  // +0x20
			float unknown24;  // +0x24
			float unknown28;  // +0x28
			float unknown2C;  // +0x2C
			float unknown30;  // +0x30
			float unknown34;  // +0x34
			float unknown38;  // +0x38
			float chargeGroundSpike;  // +0x3C
			float unknown40;  // +0x40
			float unknown44;  // +0x44
			float unknown48;  // +0x48
			float unknown4C;  // +0x4C
			float unknown50;  // +0x50
			float unknown54;  // +0x54
			float unknown58;  // +0x58
			float unknown5C;  // +0x5C
			float unknown60;  // +0x60
			float unknown64;  // +0x64
			float unknown68;  // +0x68
			float unknown6C;  // +0x6C
			float unknown70;  // +0x70
			float unknown74;  // +0x74
			float unknown78;  // +0x78
			float unknown7C;  // +0x7C
			float unknown80;  // +0x80
			float unknown84;  // +0x84
		};

		// 0x102B7780
		explicit AdvancedHealthBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		float regenTimeWithNoDamage;  // +0x50
		float regenRate;  // +0x54
		float regenMaxHealthPercentage;  // +0x58
		unsigned char unknown5C[0x64 - 0x5C];
		DamageScale damageScaleByType;  // +0x64
		ChargeRequired chargeRequiredForType;  // +0xEC
		float chargeRequiredForMuscleMassBareAttack;  // +0x174
		unsigned char unknown178[0x188 - 0x178];
		float accumDamageDecayRate;  // +0x188
		float accumDamageExpiryTime;  // +0x18C
		float npcDamageMultiplier;  // +0x190
		float commanderInfluenceDamageMultiplier;  // +0x194
		bool respondOnlyToPlayerDamage;  // +0x198
		bool proportionalDamageScale;  // +0x199
		unsigned int scaleDownDamageType;  // +0x19C
		int unknown1A0;
	};
}

#endif
