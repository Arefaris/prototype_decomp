// engine::IPathBehaviour's own members (see pathbehaviour.h). The engine compiled them apart from the implementations
// (they are far from the rest of the unit, and the implementations call them: an empty Slot1 that the compiler could
// see would not be called at all).
#include "code/engine/gameobject/behaviours/pathbehaviour.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108678C0
	IPathBehaviour::IPathBehaviour(GameObject* newOwner) : Behaviour(newOwner)
	{
	}

	// FUNCTION: ENGINE 0x108678E0
	IPathBehaviour::~IPathBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x108678F0
	void IPathBehaviour::Slot1()
	{
	}
}
