#include "code/engine/scenario/scriptowner.h"

namespace engine
{
	// GLOBAL: ENGINE 0x1130D3A8
	int ScriptOwner::sCurrentId;

	// FUNCTION: ENGINE 0x1082EB60
	ScenarioMessage* ScriptOwner::GetPart()
	{
		return (ScenarioMessage*)unknown10;
	}

	// FUNCTION: ENGINE 0x1082EBB0
	int ScriptOwner::GetCurrentId()
	{
		return sCurrentId;
	}

	// FUNCTION: ENGINE 0x1082EBA0
	void ScriptOwner::SetCurrentId(int id)
	{
		sCurrentId = id;
	}
}
