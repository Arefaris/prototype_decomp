#include "code/proto/behaviours/healthbehaviour.h"

namespace content
{
	static const EnumValue sDamageTypeValues[] =
	{
		{ "None", 0 },
		{ "Fire", 1 },
		{ "Bullet", 2 },
		{ "Crush", 3 },
		{ "Crack", 4 },
		{ "Treadmark", 5 },
		{ "Footprint", 6 },
		{ "Blood", 7 },
		{ "Slash", 8 },
		{ "Tear", 9 },
		{ "MortarShell", 10 },
		{ "Missile", 11 },
		{ "Rain", 12 },
		{ "Debris", 13 },
		{ "Paper", 14 },
		{ "Rocks", 15 },
		{ "RotorWash", 16 },
		{ "TankCrush", 17 },
		{ "Script", 18 },
		{ "Momentum", 19 },
		{ "SmallRotorWash", 20 },
		{ "25mm", 21 },
		{ "30mm", 22 },
		{ "40mm", 23 },
		{ "40mm_Specialist", 24 },
		{ "70mm", 25 },
		{ "127mm", 26 },
		{ "50cal", 27 },
		{ "RotorBlades", 28 },
		{ "BloodtoxWash", 29 },
		{ "gunTurretBullet", 30 },
		{ "500mm", 31 },
		{ "Thermobaric1", 32 },
		{ "Thermobaric2", 33 },
		{ "Throw", 34 },
		{ "MotherVomit", 35 },
		{ "RocketLauncherShell", 36 }
	};

	static const EnumValue sAttackTypeValues[] =
	{
		{ "None", 0 },
		{ "Bare", 1 },
		{ "Claws", 2 },
		{ "Blades", 3 },
		{ "Hammerfist", 4 },
		{ "Whipfist", 5 },
		{ "Weapon", 6 },
		{ "Shield", 7 },
		{ "Throw", 8 },
		{ "Bullet", 9 },
		{ "Sniper", 10 },
		{ "Missile", 11 },
		{ "MissileExplosion", 12 },
		{ "PropExplosion", 13 },
		{ "DevastatorGroundSpike", 14 },
		{ "GroundSpike", 15 },
		{ "TankCrush", 16 },
		{ "Script", 17 },
		{ "Momentum", 18 },
		{ "BloodtoxPoison", 19 },
		{ "LeaderHunterPoison", 20 },
		{ "DevastatorExplosion", 21 },
		{ "DevastatorTendril", 22 },
		{ "Hunter", 23 },
		{ "HelicopterRotor", 24 },
		{ "Infected1", 25 },
		{ "Infected2", 26 },
		{ "Hydra", 27 },
		{ "Thermobaric", 28 },
		{ "HiveKill", 29 },
		{ "SoldierPush", 30 },
		{ "AmbientVehicle", 31 },
		{ "SupremeHunter", 32 },
		{ "ObstacleBash", 33 }
	};

	// FUNCTION: ENGINE 0x102B5820
	template<> void EnumInfo<proto::DamageType>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::DamageType";
		*code = "p";
		*values = sDamageTypeValues;
		*count = 0x25;
	}

	// FUNCTION: ENGINE 0x102B5860
	template<> void EnumInfo<proto::AttackType>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::AttackType";
		*code = "p";
		*values = sAttackTypeValues;
		*count = 0x22;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x102BD6A0
	content::ClassInfo* HealthBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HealthBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102BDEE0
	content::MemberList* HealthBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::HealthBehaviour>();
		static content::BaseClassCasterImpl<engine::HealthBehaviour, HealthBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<HealthBehaviour, bool, 0>("p"),
				PROTO_OFFSET(HealthBehaviour, broadcastDamageMessages), "broadcastDamageMessages" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102BD920
// FUNCTION: ENGINE 0x102BDA20
// FUNCTION: ENGINE 0x102BDA30
// FUNCTION: ENGINE 0x102BDE90
