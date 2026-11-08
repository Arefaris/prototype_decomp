// proto::SaveGameManager: the manager of saved games and checkpoints (unit 0x1047FEE0 - 0x10488BD0).
#include "code/proto/savegamemanager.h"
#include "code/engine/luascriptmanager.h"

namespace proto
{
	// FUNCTION: ENGINE 0x10480000
	void SaveGameManager::Slot3(bool result)
	{
		state = 0;
		lastResult = result;
	}

	// FUNCTION: ENGINE 0x10480020
	void SaveGameManager::Slot4(bool result)
	{
		succeeded = result;
		state = 0;
		lastResult = result;
	}

	// FUNCTION: ENGINE 0x10480040
	bool SaveGameManager::IsActive()
	{
		return state != 0;
	}

	// FUNCTION: ENGINE 0x10480050
	bool SaveGameManager::GetLastResult()
	{
		return lastResult;
	}

	// FUNCTION: ENGINE 0x10480060
	void SaveGameManager::UnregisterScript()
	{
		engine::LuaScriptManager* script = engine::GetScriptManager();
		script->Unregister(this);
	}
}
