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
#include "code/proto/architecture/frontendpackages.h"
#include "code/proto/freeroamevents/freventmanager.h"
#include "code/proto/smarthint/smarthintmanager.h"
#include "code/pure3d/shadows/shadowrendermanager.h"
#include "code/engine/database/gamedatabase.h"

namespace engine
{
	// 0x10836BC0: forgets the game state with that number (name guess)
	void RemoveGameState(int number);
	// 0x108366F0: lets the other fibers run
	void YieldFiber();
	// 0x10837B40: names the screen a game state (the number) goes to (name guess)
	void SetGameStateScreen(int number, int kind, const char* name);
	// 0x108391A0: asks for the game state with that index in that mode (name guess)
	void RequestGameStateByIndex(int index, int mode);
}

namespace engine
{
	// The front end as the game state sees it (the same class as femovie.cpp's)
	class FrontEnd
	{
	public:
		// 0x10872920: remembers the name of the screen and tells the movie to forward to it
		void Unknown10872920(const char* newName);
	};
	// 0x10864330
	FrontEnd* Unknown10864330();
	// 0x10872840: calls a function of the front end's movie with one text argument (name unknown)
	void Unknown10872840(FrontEnd* frontEnd, const char* function, const char* argument);
	// 0x1088A9D0 / 0x1088A690 / 0x108644B0 / 0x1085FC10 / 0x10864440 (names unknown)
	void Unknown1088A9D0(int value);
	void Unknown1088A690();
	void Unknown108644B0(int a, int b);
	void Unknown1085FC10(int value);
	void UpdateScreenCentre();
	// 0x108388A0 / 0x10837A50
	void AddRealTimeTask(IRealTimeTask* task, unsigned int mask, int priority, unsigned int data);
	void RemoveRealTimeTask(IRealTimeTask* task);
	// 0x10882950: whether the game disc or the storage was taken out
	bool IsMediaRemoved();
}

namespace scaleformp3d
{
	// 0x1095C4D0
	bool RemoveFlashFile(const char* name, int heap);
}

namespace proto
{
	// The head-up display's elements the pause state shows and hides (names unknown)
	class HudScreen
	{
	public:
		// 0x104AB600 / 0x104ABC60
		void Unknown104AB600();
		void Unknown104ABC60();

		int mode;  // +0
		int unknown4;
		bool ready;  // +8
	};

	class HudLayer
	{
	public:
		// 0x104AC0F0 / 0x104AC120
		void Unknown104AC0F0();
		void Unknown104AC120();
	};

	class PauseMenuState
	{
	public:
		// 0x1049D610, 0x1049B4F0, 0x1049B450, 0x1049B580, 0x1049B490, 0x1049C780 (names unknown)
		void Unknown1049D610();
		void Unknown1049B4F0();
		void Unknown1049B450();
		void Unknown1049B580();
		void Unknown1049B490();
		void Unknown1049C780();
	};
	// 0x1049B3D0
	PauseMenuState* GetPauseMenuState();

	class FrontEndHud
	{
	public:
		// 0x104B0D00 / 0x104B0CF0
		HudScreen* Unknown104B0D00();
		HudLayer* Unknown104B0CF0();
		// 0x104B1D80 / 0x104B1DD0
		void Unknown104B1D80(int value);
		void Unknown104B1DD0(int value);
	};
	FrontEndHud* GetFrontEndHud();

	class SaveManager
	{
	public:
		// 0x10486BF0
		void Unknown10486BF0(float dt, int unused);
	};
	SaveManager* GetSaveManager();

	// 0x1126E4F0 (profilekeys.cpp)
	extern core::Name<core::CaseSensitiveKey> gProtoTutorialNum;
	// 0x104DEFD0 (name unknown)
	void Unknown104DEFD0();
	// 0x110A1374 / 0x110A137C: the movies the front end loads (names guessed)
	extern const char* gFrontEndFlashFiles[];
	extern unsigned int gFrontEndFlashFileCount;

	#define PAUSESTATE_FILE "..\\..\\..\\code\\proto\\architecture\\pausestate.cpp"

	// The name a slot group is registered under
	static inline core::Name<core::CaseSensitiveKey> MakeName(const char* text)
	{
		return core::Name<core::CaseSensitiveKey>(text, 1);
	}

	// FUNCTION: ENGINE 0x104E6940
	void GamePauseState::Enter()
	{
		unknown8A = false;
		if (unknown8D)
		{
			GetPauseMenuState()->Unknown1049D610();
			unknown8E = 0;
		}
		else if (!unknown8B)
		{
			GetFrontEndHud()->Unknown104B0D00()->Unknown104AB600();
			if (!GetFrontEndHud()->Unknown104B0D00()->ready)
			{
				do
				{
					engine::YieldFiber();
				}
				while (!GetFrontEndHud()->Unknown104B0D00()->ready);
			}
			engine::Unknown1085FC10(1);
			if (unknown8C)
			{
				GetPauseMenuState()->Unknown1049B4F0();
			}
			else
			{
				GetFrontEndHud()->Unknown104B0CF0()->Unknown104AC0F0();
				GetPauseMenuState()->Unknown1049D610();
			}
		}
		else
		{
			GetPauseMenuState()->Unknown1049B450();
		}
		engine::Unknown10864330()->Unknown10872920("NONE");
		engine::YieldFiber();
		for (unsigned int i = 0; i < gFrontEndFlashFileCount; i++)
		{
			scaleformp3d::RemoveFlashFile(gFrontEndFlashFiles[i], 0x72);
		}
		if (unknown88)
		{
			LoadFrontEndPackages("art/hud/fe_woi.p3d", "FETransient");
			engine::Unknown10872840(engine::Unknown10864330(), "AS_InstallPauseMenuFESounds", "");
			engine::Unknown10864330()->Unknown10872920("WEBOFINTRIGUE");
		}
		else if (unknown8C)
		{
			LoadFrontEndPackages("art/hud/fe_endcredits.p3d", "FETransient");
			engine::Unknown1088A9D0(2);
			engine::Unknown10864330()->Unknown10872920("ENDCREDITS");
		}
		else if (unknown8B)
		{
			engine::Unknown1088A9D0(engine::gGameDatabase->GetInt(gProtoTutorialNum, 0, 0));
			engine::Unknown10872840(engine::Unknown10864330(), "AS_InstallInGameFESounds", "");
			engine::Unknown10864330()->Unknown10872920("TUTORIAL");
		}
		else if (!unknown8D)
		{
			LoadFrontEndPackages("art/hud/fe_pause.p3d", "FETransient");
			engine::Unknown1088A9D0(0x10);
			engine::Unknown10872840(engine::Unknown10864330(), "AS_InstallPauseMenuFESounds", "");
			engine::Unknown10864330()->Unknown10872920(unknown89 ? "POWERPURCHASE" : "MAP");
			GetFrontEndHud()->Unknown104B1D80(0xF);
			unknown90 = true;
			gSmartHintManager->ReadSetting();
			gFREventManager->Unknown10588520();
		}
		engine::UpdateScreenCentre();
		engine::Unknown108644B0(1, 0);
		engine::AddRealTimeTask(this, 1, 1, (unsigned int)"Paused Task");
		engine::PauseState::Enter();
	}

	// FUNCTION: ENGINE 0x104E6C70
	void GamePauseState::Leave()
	{
		if (!unknown8D && !unknown8B && unknown8A)
		{
			int mode = GetFrontEndHud()->Unknown104B0D00()->mode;
			if (mode != 0 && mode != 1)
			{
				GetFrontEndHud()->Unknown104B0D00()->Unknown104ABC60();
				if (!GetFrontEndHud()->Unknown104B0D00()->ready)
				{
					do
					{
						engine::YieldFiber();
					}
					while (!GetFrontEndHud()->Unknown104B0D00()->ready);
				}
			}
		}
		engine::PauseState::Leave();
		if (unknown90)
		{
			GetFrontEndHud()->Unknown104B1DD0(0xF);
			unknown90 = false;
		}
		engine::Unknown10864330()->Unknown10872920("NONE");
		engine::YieldFiber();
		engine::Unknown108644B0(0, 0);
		engine::Unknown1088A690();
		if (unknown8F)
		{
			Unknown104DEFD0();
			UnloadFrontEndPackages("FETransient");
		}
		else
		{
			if (!unknown8D && !unknown8B)
			{
				LoadFrontEndPackages("art/hud/fe_ingame.p3d", "FETransient");
			}
			if (!unknown8A)
			{
				engine::Unknown10864330()->Unknown10872920("IGHUD");
			}
		}
		engine::RemoveRealTimeTask(this);
		if (!unknown8B && !unknown88 && !unknown8D && !unknown8C)
		{
			gSmartHintManager->SendExitPause();
		}
		if (unknown8D)
		{
			GetPauseMenuState()->Unknown1049C780();
		}
		else if (!unknown8B)
		{
			engine::Unknown1085FC10(0);
			if (unknown8C)
			{
				GetPauseMenuState()->Unknown1049B580();
			}
			else
			{
				GetFrontEndHud()->Unknown104B0CF0()->Unknown104AC120();
				GetPauseMenuState()->Unknown1049C780();
			}
		}
		else
		{
			GetPauseMenuState()->Unknown1049B490();
		}
		unknown88 = false;
		unknown89 = false;
		unknown8B = false;
		unknown8C = false;
		unknown8A = false;
		unknown8D = false;
	}

	// FUNCTION: ENGINE 0x104E6EC0
	void GamePauseState::Update(engine::UpdateContext context)
	{
		GetSaveManager()->Unknown10486BF0(context.dt, 0);
		if (unknown81 || unknown80)
		{
			switch (unknown7C)
			{
			case 0:
				{
					int mode = GetFrontEndHud()->Unknown104B0D00()->mode;
					if (mode == 0 || mode == 1)
					{
						if (GetFrontEndHud()->Unknown104B0D00()->ready)
						{
							engine::Unknown10864330()->Unknown10872920("NONE");
							unknown7C = 1;
						}
					}
				}
				break;
			case 1:
				{
					unsigned int count = unknown84;
					unknown84 = count + 1;
					if (count > 2)
					{
						unknown7C = 2;
						unknown84 = 0;
					}
				}
				break;
			case 2:
				engine::Unknown1088A690();
				BeginFrontEndTransientUnload();
				unknown7C = 3;
				break;
			case 3:
				if (FinishFrontEndTransientUnload())
				{
					unknown7C = 4;
				}
				break;
			case 4:
				StartFrontEndTransientLoad(unknown81 ? "art/hud/fe_pause.p3d" : "art/hud/fe_woi.p3d", "FETransient");
				unknown7C = 5;
				break;
			case 5:
				if (IsFrontEndTransientLoaded())
				{
					unknown7C = 6;
				}
				break;
			case 6:
				engine::Unknown10864330()->Unknown10872920(unknown81 ? "MAP" : "WEBOFINTRIGUE");
				if (unknown81)
				{
					engine::Unknown1088A9D0(0x10);
					GetFrontEndHud()->Unknown104B1D80(0xF);
					unknown90 = true;
					unknown7C = 7;
				}
				else
				{
					GetFrontEndHud()->Unknown104B1DD0(0xF);
					unknown90 = false;
					unknown7C = 7;
				}
				break;
			case 7:
				unknown81 = false;
				unknown80 = false;
				break;
			}
		}
		if (unknown8D && !unknown8E && !unknown8A && !engine::IsMediaRemoved())
		{
			Slot3();
			unknown8E = 1;
		}
	}

	// FUNCTION: ENGINE 0x104E7100
	void GamePauseState::Slot3()
	{
		unknown8F = false;
		engine::PauseState::Slot3();
	}

	// FUNCTION: ENGINE 0x104E7110
	void GamePauseState::Slot4()
	{
		unknown8F = true;
		engine::RequestGameStateByIndex(5, 2);
	}

	// FUNCTION: ENGINE 0x104E7130
	void GamePauseState::SetUnknown88()
	{
		unknown88 = true;
	}

	// FUNCTION: ENGINE 0x104E7140
	void GamePauseState::SetUnknown89()
	{
		unknown89 = true;
	}

	// FUNCTION: ENGINE 0x104E7150
	void GamePauseState::SetUnknown8B()
	{
		unknown8B = true;
	}

	// FUNCTION: ENGINE 0x104E7160
	void GamePauseState::SetUnknown8C()
	{
		unknown8C = true;
	}

	// FUNCTION: ENGINE 0x104E7170
	void GamePauseState::SetUnknown8D()
	{
		unknown8D = true;
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
