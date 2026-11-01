// proto::HealthBehaviour (RTTI and reflection names; base engine::HealthBehaviour): the health of the open world's
// objects. It tells the scenario about the damage it takes (broadcastDamageMessages), remembers who hurt it last and
// scales the damage by the difficulty. The base of the advanced health behaviours. Unit 0x102BD6A0 - 0x102BEAE0 (no
// assert path; the file name is a guess). The reflected names are original, the rest is guessed; only the reflection is
// reconstructed.
#ifndef PROTO_BEHAVIOURS_HEALTHBEHAVIOUR_H
#define PROTO_BEHAVIOURS_HEALTHBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/healthbehaviour.h"

namespace proto
{
	enum DamageType
	{
		DAMAGE_TYPE_NONE = 0,
		DAMAGE_TYPE_FIRE = 1,
		DAMAGE_TYPE_BULLET = 2,
		DAMAGE_TYPE_CRUSH = 3,
		DAMAGE_TYPE_CRACK = 4,
		DAMAGE_TYPE_TREADMARK = 5,
		DAMAGE_TYPE_FOOTPRINT = 6,
		DAMAGE_TYPE_BLOOD = 7,
		DAMAGE_TYPE_SLASH = 8,
		DAMAGE_TYPE_TEAR = 9,
		DAMAGE_TYPE_MORTAR_SHELL = 10,
		DAMAGE_TYPE_MISSILE = 11,
		DAMAGE_TYPE_RAIN = 12,
		DAMAGE_TYPE_DEBRIS = 13,
		DAMAGE_TYPE_PAPER = 14,
		DAMAGE_TYPE_ROCKS = 15,
		DAMAGE_TYPE_ROTOR_WASH = 16,
		DAMAGE_TYPE_TANK_CRUSH = 17,
		DAMAGE_TYPE_SCRIPT = 18,
		DAMAGE_TYPE_MOMENTUM = 19,
		DAMAGE_TYPE_SMALL_ROTOR_WASH = 20,
		DAMAGE_TYPE_N25MM = 21,
		DAMAGE_TYPE_N30MM = 22,
		DAMAGE_TYPE_N40MM = 23,
		DAMAGE_TYPE_N40MM_SPECIALIST = 24,
		DAMAGE_TYPE_N70MM = 25,
		DAMAGE_TYPE_N127MM = 26,
		DAMAGE_TYPE_N50CAL = 27,
		DAMAGE_TYPE_ROTOR_BLADES = 28,
		DAMAGE_TYPE_BLOODTOX_WASH = 29,
		DAMAGE_TYPE_GUN_TURRET_BULLET = 30,
		DAMAGE_TYPE_N500MM = 31,
		DAMAGE_TYPE_THERMOBARIC1 = 32,
		DAMAGE_TYPE_THERMOBARIC2 = 33,
		DAMAGE_TYPE_THROW = 34,
		DAMAGE_TYPE_MOTHER_VOMIT = 35,
		DAMAGE_TYPE_ROCKET_LAUNCHER_SHELL = 36
	};

	enum AttackType
	{
		ATTACK_TYPE_NONE = 0,
		ATTACK_TYPE_BARE = 1,
		ATTACK_TYPE_CLAWS = 2,
		ATTACK_TYPE_BLADES = 3,
		ATTACK_TYPE_HAMMERFIST = 4,
		ATTACK_TYPE_WHIPFIST = 5,
		ATTACK_TYPE_WEAPON = 6,
		ATTACK_TYPE_SHIELD = 7,
		ATTACK_TYPE_THROW = 8,
		ATTACK_TYPE_BULLET = 9,
		ATTACK_TYPE_SNIPER = 10,
		ATTACK_TYPE_MISSILE = 11,
		ATTACK_TYPE_MISSILE_EXPLOSION = 12,
		ATTACK_TYPE_PROP_EXPLOSION = 13,
		ATTACK_TYPE_DEVASTATOR_GROUND_SPIKE = 14,
		ATTACK_TYPE_GROUND_SPIKE = 15,
		ATTACK_TYPE_TANK_CRUSH = 16,
		ATTACK_TYPE_SCRIPT = 17,
		ATTACK_TYPE_MOMENTUM = 18,
		ATTACK_TYPE_BLOODTOX_POISON = 19,
		ATTACK_TYPE_LEADER_HUNTER_POISON = 20,
		ATTACK_TYPE_DEVASTATOR_EXPLOSION = 21,
		ATTACK_TYPE_DEVASTATOR_TENDRIL = 22,
		ATTACK_TYPE_HUNTER = 23,
		ATTACK_TYPE_HELICOPTER_ROTOR = 24,
		ATTACK_TYPE_INFECTED1 = 25,
		ATTACK_TYPE_INFECTED2 = 26,
		ATTACK_TYPE_HYDRA = 27,
		ATTACK_TYPE_THERMOBARIC = 28,
		ATTACK_TYPE_HIVE_KILL = 29,
		ATTACK_TYPE_SOLDIER_PUSH = 30,
		ATTACK_TYPE_AMBIENT_VEHICLE = 31,
		ATTACK_TYPE_SUPREME_HUNTER = 32,
		ATTACK_TYPE_OBSTACLE_BASH = 33
	};

	class HealthBehaviour : public engine::HealthBehaviour
	{
	public:
		// 0x102BDA60
		explicit HealthBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		bool broadcastDamageMessages;  // +0x28
		unsigned char unknown29[0x50 - 0x29];
	};
}

#endif
