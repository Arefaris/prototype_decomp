// The game state of a front end dialog (unit 0x108E3E00 - 0x108E44F0; no assert path, file name guessed).
#include "code/engine/frontend/privatedialogstate.h"
#include "code/engine/system/engineflags.h"
#include "code/core/strings.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108E42D0
	// EQUIVALENT: scheduling (the engine pushes the destination of the first string copy after the last two stores; 73 %)
	PrivateDialogState::PrivateDialogState(DialogState* newOwner, int newId, int newPriority, const char* newName,
		const char* newOverlay) : GameState(0, 0x10000)
	{
		owner = newOwner;
		stateId = newId;
		priority = newPriority;
		icon = 0;
		iconVisible = false;
		requested = false;
		active = false;
		inputPushed = false;
		mouseVisible = false;
		controller = -1;
		overlay = 0;
		core::StrNCpy(name, newName, 0x20);
		core::StrNCpy(overlayName, newOverlay, 0x20);
	}

	// FUNCTION: ENGINE 0x108E3E10
	PrivateDialogState::~PrivateDialogState()
	{
		if (GetGameState(stateId) != 0)
		{
			FreeGameState(stateId);
		}
	}

	// FUNCTION: ENGINE 0x108E3E50
	bool PrivateDialogState::Request(int newController, int flag)
	{
		if (requested)
		{
			return false;
		}
		icon = 0;
		requested = true;
		controller = newController;
		if (GetGameState(stateId) != 0)
		{
			FreeGameState(stateId);
		}
		if (HasEngineFlags(0x10) && flag == 0)
		{
			covered = false;
			AddGameState(this, stateId, priority, 2, 0, 0);
			RequestGameState(stateId, 2, this);
			return true;
		}
		covered = true;
		if (flag == 1)
		{
			AddGameState(this, stateId, priority, 0, 0, 0);
			RequestGameState(stateId, 0, this);
			return true;
		}
		AddGameState(this, stateId, priority, 0, 0, 0);
		RequestGameState(stateId, 1, this);
		return true;
	}

	// FUNCTION: ENGINE 0x108E3F60
	bool PrivateDialogState::IsActive()
	{
		return active;
	}

	// FUNCTION: ENGINE 0x108E3F70
	bool PrivateDialogState::IsDone()
	{
		return requested || GetGameStateStatus(stateId) != 1;
	}

	// FUNCTION: ENGINE 0x108E3FA0
	void PrivateDialogState::SetIcon(int newIcon, bool visible)
	{
		icon = newIcon;
		iconVisible = visible;
	}
}
