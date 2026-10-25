// engine::ScriptOwner (the engine's class is not named; names are guesses): what a script runs for and what the
// scenario conditions are asked about. It is a fight::Params node (the value it was made with is its kind): the kind says which sort of
// object it is (a kind below 0x10000 is a node with its own id and handle, a kind in 0x10000 - 0x2FFFF carries the
// handle of a game object), and the scenario message the node was made from lies inside it (GetPart).
#ifndef ENGINE_SCENARIO_SCRIPTOWNER_H
#define ENGINE_SCENARIO_SCRIPTOWNER_H

#include "code/engine/fight/params.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/scenariomessage.h"

namespace engine
{
	struct ScriptOwner : fight::Params
	{
		// 0x1082EAF0 (another unit): a node made from a scenario message
		ScriptOwner(ScenarioMessage* message, int newKind);
		// The vftable's fourth slot (0x1082EB70, another unit): a copy of the node
		virtual ScriptOwner* Clone();
		// 0x1082EB60 / 0x1082EBB0 / 0x1082EBA0 (another unit)
		ScenarioMessage* GetPart();
		static int GetCurrentId();
		static void SetCurrentId(int id);

		// Whether the owner is a node of its own
		bool IsNode() const
		{
			return (unsigned int)value - 1 <= 0xFFFE;
		}

		int id;  // +0xC
		unsigned char unknown10[0x80];
		GameObjectHandle handle;  // +0x90
	};
}

#endif
