// The AI system the ai fight items talk to: the singleton at 0x11263AB0 (created at 0x10364D70, 0x1060 bytes, constructor
// 0x103649D0) and the parts of it the items read. Class and member names are guesses; only what the items use is declared.
#ifndef PROTO_FIGHTITEMS_AI_AIHELPERS_H
#define PROTO_FIGHTITEMS_AI_AIHELPERS_H

#include "code/core/name.h"
#include "code/engine/fight/sequencer.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/math/vector.h"

namespace proto
{
	// A one byte flag the engine passes by value (stored in the argument slot and pushed as a word)
	struct ByteFlag
	{
		bool value;
	};

	// 0x103C4A00: how many objects of a tag are around (name guess)
	int Unknown103C4A00(const fight::Name* tag, int limit, ByteFlag tryDespawnIfFull, float minDespawnDistance, float objRadius);

	// One combat type's pool of tokens (0x20 bytes)
	class CombatBudget
	{
	public:
		// 0x1038A4C0: asks for a token for an object
		void Unknown1038A4C0(const engine::GameObjectHandle* handle);
		// 0x1038A100: whether the object holds a token
		bool Unknown1038A100(const engine::GameObjectHandle* handle);

		unsigned char unknown0[0x20];
	};

	// The combat budgets (0x84 bytes): the flag that turns them on, then one pool per combat type
	class CombatBudgets
	{
	public:
		void Request(int type, const engine::GameObjectHandle* handle)
		{
			if (enabled)
			{
				entries[type].Unknown1038A4C0(handle);
			}
		}

		bool Has(int type, const engine::GameObjectHandle* handle)
		{
			if (enabled && !entries[type].Unknown1038A100(handle))
			{
				return false;
			}
			return true;
		}

		bool enabled;  // +0x0
		unsigned char unknown1[3];
		CombatBudget entries[4];  // +0x4
	};

	// The soldier budgets (gAISystem +0x10; name guess)
	class SoldierBudgets
	{
	public:
		// 0x103866C0: whether the object is in a loaded cell (name guess)
		bool Unknown103866C0(engine::GameObjectHandle handle);
		// 0x10386810: whether a soldier of a type may still be reserved for the object (name guess)
		bool Unknown10386810(int type, engine::GameObjectHandle handle);
		// 0x10385DA0: renews the object's reservation (name guess)
		bool Unknown10385DA0(engine::GameObjectHandle handle);
	};

	// The strafe run tokens (gAISystem +0x1C; name guess)
	class StrafeRunTokens
	{
	public:
		// 0x10383FF0: gives the object a token for a time (name guess)
		bool Unknown10383FF0(engine::GameObjectHandle handle, float time);
		// 0x10381E10 / 0x10381E20: counts a commander in or out of combat (name guess)
		void Unknown10381E10();
		void Unknown10381E20();
		// 0x10384160: holds a gun butt for the object for a time (name guess)
		void Unknown10384160(engine::GameObjectHandle handle, float time);
		// 0x10384090: whether the object holds a token, asking for one first when the flag is set
		bool Unknown10384090(engine::GameObjectHandle handle, ByteFlag requestIt);
		// 0x103840E0: whether the object may gun butt (name guess)
		bool Unknown103840E0(engine::GameObjectHandle handle);
		// 0x103833C0 / 0x10383520: releases a reserved position (name guesses); the flag tells the targets' kind from the others
		void Unknown103833C0(const math::Vector* position, bool targets);
		void Unknown10383520(const math::Vector* position);
		// 0x10385420: releases the volume the object reserved (name guess)
		void Unknown10385420(engine::GameObjectHandle handle);
		// 0x10384460 / 0x103844F0: reserves a position for a time (name guesses)
		void Unknown10384460(const math::Vector* position, float time, bool targets);
		void Unknown103844F0(const math::Vector* position, float time);
	};

	// The base alert (gAISystem +0x20; name guess)
	class BaseAlert
	{
	public:
		// 0x1037E0F0: whether the object should call the radio headquarters (name guess)
		bool Unknown1037E0F0(engine::GameObject* object);
		// 0x10381390: the alert's report of being back at idle (name guess)
		void Unknown10381390(bool evade);
		// 0x10380440: the alert's report of a character beginning combat (name guess)
		void Unknown10380440();
		// 0x1037C5C0: the alert's report of an object for a time (name guess)
		void Unknown1037C5C0(engine::GameObject* object, float time);
		// 0x1037CA50: turns the police off or on for a time (name guess)
		void Unknown1037CA50(bool disable, float delay);
	};

	class AISystem
	{
	public:
		unsigned char unknown0[0x10];
		SoldierBudgets* soldierBudgets;  // +0x10
		CombatBudgets* budgets;  // +0x14
		unsigned char unknown18[4];
		StrafeRunTokens* strafeRunTokens;  // +0x1C
		BaseAlert* baseAlert;  // +0x20
	};

	// 0x11263AB0
	extern AISystem* gAISystem;

	// 0x103B9940: a debug output the release build leaves empty (name guess)
	void Unknown103B9940(engine::GameObject* object, int channel, const char* text);
	// 0x103BE5F0: the object that holds the given one, null when none does (name guess)
	engine::GameObject* Unknown103BE5F0(engine::GameObject* object);
	// 0x103B92B0: the name of an object (name guess)
	const fight::Name* Unknown103B92B0(engine::GameObject* object);
	// 0x103B8440: whether the object has arrived at its destination (name guess)
	bool Unknown103B8440(engine::GameObject* object);
	// 0x103B82F0: makes the object stop (name guess)
	void Unknown103B82F0(engine::GameObject* object);
	// 0x103BA7F0: whether the target is hostile to the object (name guess)
	bool Unknown103BA7F0(engine::GameObject* object, engine::GameObjectHandle target);
	// 0x103BB590: forces the emotional state of the object (name guess)
	void Unknown103BB590(engine::GameObject* object, core::Name<core::CaseSensitiveKey> state);
	// 0x103B8630: sets how an object moves (the sprint and the maximum speed flags; name guess)
	void Unknown103B8630(engine::GameObject* object, bool sprint, bool useMaxSpeed);
	// 0x10078F70: whether the object is the player's
	bool IsPlayerObject(engine::GameObject* object);
	// 0x103C0360 / 0x103C02D0: whether the object is a tank / a helicopter (name guesses; each asks the object for its vehicle kind)
	bool Unknown103C0360(engine::GameObject* object);
	bool Unknown103C02D0(engine::GameObject* object);
	// 0x103B8DC0: the level of detail state of an object (name guess)
	int Unknown103B8DC0(engine::GameObject* object);
	// 0x103B8B80: the handle of the object's target (name guess)
	engine::GameObjectHandle Unknown103B8B80(engine::GameObject* object);
}

#endif
