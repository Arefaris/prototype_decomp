// engine::PauseState (RTTI name): the base of the pause menu's game state, see gamestate.h. The unit is the part of the
// frontend's code around 0x108822F0; no assert path names the file, so the file name is a guess.
#include "code/core/strings.h"
#include "code/engine/controller/inputsystem.h"
#include "code/engine/function.h"
#include "code/engine/gamestate.h"
#include "code/engine/system/engineflags.h"
#include "code/engine/system/gamestatetable.h"

namespace engine
{
	class Replay;

	// The game state table's functions (gamestate.cpp)
	void AddGameState(void* stateObject, int id, int priority, int flag, int mode, int parent);
	void FreeGameState(int id);
	unsigned int* RemoveStateFlags(unsigned int flags);
	void RequestGameState(int state, int mode, SyncCommands::SyncCallback* callback);
	void RequestGameStateOverlay(int state, int mode, SyncCommands::SyncCallback* callback);

	// 0x113187D0 (the replay's unit): the one replay, none while the game is not in a replay session
	extern Replay* gReplay;

	// GLOBAL: ENGINE 0x11316CA0
	PauseState* gCurrentPauseState = 0;

	// FUNCTION: ENGINE 0x108822D0
	PauseState* PauseState::GetCurrent()
	{
		return gCurrentPauseState;
	}

	// FUNCTION: ENGINE 0x108822E0
	void PauseState::SetCurrent(PauseState* state)
	{
		gCurrentPauseState = state;
	}

	// FUNCTION: ENGINE 0x108822F0
	PauseState::~PauseState()
	{
		GetScriptManager()->Unregister(this);
		if (GetCurrent() == this)
		{
			FreeGameState(1);
		}
	}

	// FUNCTION: ENGINE 0x10882320
	// NONMATCHING: the engine compares the context member in memory and loads it again for the call, ours loads it
	// once, 47 %
#ifdef NONMATCHING
	void PauseState::Enter()
	{
		if (gReplay == 0 && unknown68 != -1)
		{
			controller::InputSystem::Get()->PushContext(unknown68, 2);
		}
		if (!HasEngineFlags(0x10) || unknown58 != 0)
		{
			RemoveStateFlags(4);
			RemoveStateFlags(8);
		}
		controller::InputSystem::Get()->StopVibration();
	}
#endif

	// FUNCTION: ENGINE 0x10882380
	// NONMATCHING: the engine compares the context member in memory and loads it again for the call, ours loads it
	// once (88 % with the input system in a local, which calls it before loading the argument)
#ifdef NONMATCHING
	void PauseState::Leave()
	{
		if (gReplay == 0 && unknown68 != -1)
		{
			controller::InputSystem::Get()->PopContext(unknown68);
			unknown68 = -1;
		}
	}
#endif

	// FUNCTION: ENGINE 0x108823B0
	void PauseState::Slot5(bool enable)
	{
		if (enable && unknown58 == 0)
		{
			FreeGameState(1);
			AddGameState(this, 1, 3, 2, 0, 0);
			unknown64 = 2;
			unknown60 = 2;
			return;
		}
		FreeGameState(1);
		AddGameState(this, 1, 3, 0, 0, 0);
		unknown64 = 0;
		unknown60 = 2;
	}

	// FUNCTION: ENGINE 0x10882420
	void PauseState::Slot2(int player)
	{
		if (gReplay == 0)
		{
			unknown68 = player;
		}
		RequestGameState(1, unknown60, 0);
	}

	// FUNCTION: ENGINE 0x10882450
	void PauseState::Slot3()
	{
		RequestGameStateOverlay(1, unknown64, 0);
	}

	// FUNCTION: ENGINE 0x10882470
	void PauseState::Slot4()
	{
		RequestGameState(unknown54, 2, 0);
	}

	// FUNCTION: ENGINE 0x10882490
	void PauseState::SetCurrentMode(const char* mode)
	{
		if (core::StrCmp(mode, "INGAME") == 0)
		{
			Slot3();
		}
		else if (core::StrCmp(mode, "STARTUP") == 0)
		{
			Slot4();
		}
	}

	// FUNCTION: ENGINE 0x10882620
	PauseState::PauseState(int a, int b) : GameState(0, 0x10000)
	{
		unknown54 = a;
		unknown58 = b;
		unknown68 = -1;
		if (GetCurrent() == 0)
		{
			SetCurrent(this);
		}
		PauseState::Slot5(false);
		LuaScriptManager* script = GetScriptManager();
		script->SetOwner(this);
		script->RegisterMethod("fe_SetCurrentMode", this, &PauseState::SetCurrentMode);
		script->ClearOwner();
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108824E0
// FUNCTION: ENGINE 0x10882530
// FUNCTION: ENGINE 0x10882540
// FUNCTION: ENGINE 0x10882560
// FUNCTION: ENGINE 0x108825B0
// FUNCTION: ENGINE 0x108825D0
