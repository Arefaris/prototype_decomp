// proto::GamePauseState (code/proto/architecture/pausestate.cpp, path from the unit's own assert strings; see the
// header). Reconstructed from the shadow map memory borrowing to the destructor.
#include "code/proto/architecture/pausestate.h"

#include "code/core/heap.h"
#include "code/core/report.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/controller/inputsystem.h"
#include "code/engine/frontend/frontend.h"
#include "code/engine/function.h"
#include "code/engine/message.h"
#include "code/pure3d/shadows/shadowrendermanager.h"

namespace engine
{
	// 0x10836BC0: forgets the game state with that number (name guess)
	void RemoveGameState(int number);
	// 0x108366F0: lets the other fibers run
	void YieldFiber();
	// 0x10837B40: names the screen a game state (the number) goes to (name guess)
	void SetGameStateScreen(int number, int kind, const char* name);
}

namespace proto
{
	#define PAUSESTATE_FILE "..\\..\\..\\code\\proto\\architecture\\pausestate.cpp"

	// The name a slot group is registered under
	static inline core::Name<core::CaseSensitiveKey> MakeName(const char* text)
	{
		return core::Name<core::CaseSensitiveKey>(text, 1);
	}

	// FUNCTION: ENGINE 0x104E7180
	void GamePauseState::PauseMenuToWOI()
	{
		unknown80 = true;
		unknown81 = false;
		unknown7C = 0;
	}

	// FUNCTION: ENGINE 0x104E71A0
	void GamePauseState::WOIToPauseMenu()
	{
		unknown81 = true;
		unknown80 = false;
		unknown7C = 0;
	}

	// FUNCTION: ENGINE 0x104E71C0
	void GamePauseState::UnpauseGame()
	{
		Slot3();
	}

	// FUNCTION: ENGINE 0x104E71D0
	void GamePauseState::ReturnShadowMapHeap()
	{
		static bool sReport = true;
		if (sReport)
		{
			if (core::Report(1, " oldassert ", PAUSESTATE_FILE, 654, "false", 0) == 3)
			{
				sReport = false;
			}
		}
		if (borrowedHeap != 0)
		{
			borrowedHeap->heap = -1;
			while (!borrowedHeap->IsReady())
			{
				engine::YieldFiber();
			}
			if (borrowedHeap != 0)
			{
				delete borrowedHeap;
			}
			borrowedHeap = 0;
			pure3d::ShadowRenderManager::Get()->ReclaimShadowMapHeap();
		}
	}

	// FUNCTION: ENGINE 0x104E7280
	void GamePauseState::OnMessage(engine::OLSMessage* message)
	{
		if (message->type == 0)
		{
			unsigned short id = message->id;
			if (id != 8)
			{
				if (id == 0)
				{
					if (message->user == engine::OLS::Get()->currentUser->id)
					{
						unknown8A = true;
					}
				}
				else if (id == 1)
				{
					if (message->user == engine::OLS::Get()->currentUser->id)
					{
						unknown8A = true;
					}
				}
			}
		}
	}

	// The copies the compiler keeps out of line of the members the constructor and the destructor use
	// (container::SListLite<OLS::Callback>::PushBack and Remove, engine::OLS::AddCallback and RemoveCallback), and of
	// the script wrappers the registration of the four natives builds (Method0 / Closure0 of this class and
	// LuaScriptManager::RegisterMethod)
	// FUNCTION: ENGINE 0x104E72E0
	// FUNCTION: ENGINE 0x104E7310
	// FUNCTION: ENGINE 0x104E7340
	// FUNCTION: ENGINE 0x104E7390
	// FUNCTION: ENGINE 0x104E73B0
	// FUNCTION: ENGINE 0x104E73F0
	// FUNCTION: ENGINE 0x104E75D0
	// FUNCTION: ENGINE 0x104E7630
	// FUNCTION: ENGINE 0x104E7650
	// FUNCTION: ENGINE 0x104E76F0

	// FUNCTION: ENGINE 0x104E7710
	GamePauseState::GamePauseState() : engine::PauseState(3, 0)
	{
		borrowedHeap = 0;
		unknown7C = 7;
		unknown80 = false;
		unknown81 = false;
		unknown84 = 0;
		unknown88 = false;
		unknown89 = false;
		unknown8A = false;
		unknown8B = false;
		unknown8C = false;
		unknown8D = false;
		unknown8F = false;
		unknown90 = false;
		engine::SetGameStateScreen(5, 3, engine::HasCommandLineOption("Demo") ? "START" : "FEMAINMENU");
		engine::LuaScriptManager* script = engine::GetScriptManager();
		script->SetOwner(this);
		script->RegisterMethod("fe_PauseGame", this, &GamePauseState::PauseGame);
		script->RegisterMethod("fe_UnpauseGame", this, &GamePauseState::UnpauseGame);
		script->RegisterMethod("fe_PauseMenuToWOI", this, &GamePauseState::PauseMenuToWOI);
		script->RegisterMethod("fe_WOIToPauseMenu", this, &GamePauseState::WOIToPauseMenu);
		script->ClearOwner();
		engine::OLS::Get()->AddCallback(this);
	}

	// FUNCTION: ENGINE 0x104E7430
	GamePauseState::~GamePauseState()
	{
		engine::GetScriptManager()->Unregister(this);
		engine::RemoveGameState(5);
		engine::OLS::Get()->RemoveCallback(this);
	}

	// FUNCTION: ENGINE 0x104E74A0
	void GamePauseState::PauseGame()
	{
		unsigned int player = ((engine::controller::PlayerInfo*)engine::controller::InputSystem::Get()->active.head)->id;
		Slot2(player);
	}

	// FUNCTION: ENGINE 0x104E74C0
	void GamePauseState::BorrowShadowMapHeap()
	{
		static bool sReport = true;
		if (sReport)
		{
			if (core::Report(1, " oldassert ", PAUSESTATE_FILE, 623, "false", 0) == 3)
			{
				sReport = false;
			}
		}
		if (borrowedHeap == 0)
		{
			int parent = pure3d::ShadowRenderManager::Get()->LendShadowMapHeap();
			engine::SlotHeapConfig config;
			config.size = 0x400000;
			config.flag = false;
			config.alignment = 0x1000;
			core::HeapScope scope(parent);
			borrowedHeap = new engine::StreamSlotGroup(MakeName("PauseBorrowed"), 1, &config, false, true);
			borrowedHeap->heap = parent;
			borrowedHeap->Create(0, true);
		}
	}
}
