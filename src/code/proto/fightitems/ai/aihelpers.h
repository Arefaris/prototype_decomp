// The AI system the ai fight items talk to: the singleton at 0x11263AB0 (created at 0x10364D70, 0x1060 bytes, constructor
// 0x103649D0) and the parts of it the items read. Class and member names are guesses; only what the items use is declared.
#ifndef PROTO_FIGHTITEMS_AI_AIHELPERS_H
#define PROTO_FIGHTITEMS_AI_AIHELPERS_H

#include "code/engine/fight/sequencer.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"

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
	};

	// The base alert (gAISystem +0x20; name guess)
	class BaseAlert
	{
	public:
		// 0x1037E0F0: whether the object should call the radio headquarters (name guess)
		bool Unknown1037E0F0(engine::GameObject* object);
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

	// 0x103B92B0: the name of an object (name guess)
	const fight::Name* Unknown103B92B0(engine::GameObject* object);
	// 0x103B8B80: the handle of the object's target (name guess)
	engine::GameObjectHandle Unknown103B8B80(engine::GameObject* object);
}

#endif
