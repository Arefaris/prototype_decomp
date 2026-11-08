// The scenario's start-up (unit 0x1082FEE0 - 0x10830EE0, no assert path; the file name and the function names are
// guesses): the game object that owns the scenario tree, made once the scenario context is loaded, and the message that
// hands the script state's global table to the scenario's scripts.
#ifndef ENGINE_SCENARIO_SCENARIOMANAGER_H
#define ENGINE_SCENARIO_SCENARIOMANAGER_H

#include "code/engine/gameobject/gameobject.h"
#include "code/engine/scenariomessage.h"

namespace fight
{
	class TrackRegistry;
}

namespace engine
{
	// RTTI engine::SetLuaEnvironmentMessage: a scenario message of id 10 that carries the reference to the global table
	struct SetLuaEnvironmentMessage : ScenarioMessage
	{
		SetLuaEnvironmentMessage() : ScenarioMessage(10), reference(0)
		{
		}
		virtual ~SetLuaEnvironmentMessage()
		{
		}
		// 0x10830200: answers no copy
		virtual ScenarioMessage* Clone(void* memory, int unused);

		int reference;  // +0x1C
	};

	// The game object that runs the scenario (0x1130D438; made by StartScenario)
	extern GameObject* gScenarioObject;

	// The name of the context the scenario tree lives in (0x111C17D4)
	extern const char* const gScenarioContextName;

	// 0x10830270: makes the scenario object, gives it the tree of the registry and sends the script environment
	void StartScenario(fight::TrackRegistry* registry);
	// 0x10830E90: the same for the scenario context, made in the given heap
	void StartScenarioContext(int heap);
}

#endif
