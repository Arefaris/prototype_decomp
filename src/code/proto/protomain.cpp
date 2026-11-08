// The proto game's start-up: the heap table the game runs on and the stream slot groups the loader fills. No assert
// path names the unit, so the file name and every function name here are guesses (the frontend object it builds is
// called "protomain").
#include "code/core/debugger.h"
#include "code/core/file/mounts.h"
#include "code/core/name.h"
#include "code/core/report.h"
#include "code/core/strings.h"
#include "code/engine/controller/defaultcontrollerhandler.h"
#include "code/engine/frontend/frontend.h"
#include "code/engine/frontend/privatedialogstate.h"
#include "code/engine/fight/fightsystem.h"
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/scenario/scenariolisters.h"
#include "code/engine/system/enginememory.h"
#include "code/engine/system/simulationdriver.h"
#include "code/engine/system/streampackage.h"
#include "code/engine/world/zoneset.h"
#include "code/math/random.h"
#include "code/proto/protomain.h"

namespace engine
{
	namespace render
	{
		// 0x1128186A (drawableimpl.h): passed to the texture uploader
		extern bool gTextureLoadFlag;
	}
}

namespace core
{
	// 0x108E45D0 (the cement file unit): whether a cement table is mounted (name guess)
	bool HasCement();
	// 0x108E5B00: picks the cement table of that name and starts the cement thread (name guess)
	void StartCement(const Name<CaseSensitiveKey>& name, int mode);
	// 0x108E45E0: waits for the thread when it is done and answers how many requests are left (name guess)
	int PollCement();
	// 0x10644220 / 0x10644250: the language the game runs in and its name
	int LanguageGet();
	const char* GetLanguageName(int language);
	// 0x10644610: the report file's name and whether it is written (an empty function in this build; name guess)
	void OpenReportFile(const char* name, bool enable);
}

namespace engine
{
	// 0x10E19AA8 (the unit's table of default zones) and 0x1126EE80 (the entries of "zone2")
	extern const unsigned char gDefaultZones[];
	extern ZoneEntry gZone2Entries[];

	class GameState;

	// 0x10832330: the initialiser of the scenario context (name guess)
	void MakeScenarioContext();
	// 0x10811FC0, 0x10811FB0, 0x10811FA0, 0x10811F90, 0x10811F80: empty functions the game state reset calls after the
	// scenario listers (name guesses)
	void Unknown10811FC0();
	void Unknown10811FB0();
	void Unknown10811FA0();
	void Unknown10811F90();
	void Unknown10811F80();

	// 0x10836AB0: makes the driver the one the main loop runs
	void SetSimulationDriver(SimulationDriver* driver);
	// 0x10836B40: enters a game state in the table of states under its number (name guess)
	void AddGameState(void* state, int number, int a, int b, int c, int d);
	// 0x1088A230: the heap the front end allocates from (set to the first slot of FETransient; name guess)
	int SetFrontEndHeap(int heap);

	// 0x10848EE0: the value of a command line option, 0 when it is not given
	const char* GetCommandLineValue(const char* option);
}

namespace engine
{
	class FrontEnd;
}

namespace proto
{
	// 0x102A2730: resets the systems of the fight classes between two game states (name guess)
	void ResetFightSystems();
	// 0x10092AF0 (fightitems/contexts.cpp): registers the fight contexts
	void RegisterFightContexts();

	// 0x1126EE20: the memory the art heaps may use (IncreaseArtHeaps takes a megabyte off it)
	extern int gArtMemory;
	// 0x110A0F24: the front end's data file was found
	extern bool gUVDataFound;
	// 0x1126EE28
	extern engine::controller::DefaultControllerHandler* gControllerHandler;
	// 0x1126EE1C
	extern engine::FrontEnd* gFrontend;

	// 0x104DF950: whether the level is one of the dev select list's (name guess)
	bool HasDevSelectLevel(const char* name);
	// 0x104DEEC0: starts the level of that name from the list named group (name guess)
	void StartDevSelectLevel(const char* name, int flag, const char* group);
	// 0x104DEFC0 (name guess)
	void FinishDevSelectStart();
	// 0x104E1A30
	engine::controller::DefaultControllerHandler* GetControllerHandler();

	// The head-up display of the front end (0x104B0A00 makes it)
	class FrontEndHud
	{
	public:
		// 0x104B1470 (name guess)
		void Unknown104B1470(int value);
	};
	FrontEndHud* GetFrontEndHud();

	// 0x1125E388: the render manager (RTTI proto::ProtoRenderManager, 0xE8 bytes)
	class ProtoRenderManager
	{
	public:
		// 0x102E4440: starts observing the video settings
		void Initialize();
	};
	extern ProtoRenderManager* gProtoRenderManager;

	// The managers the game keeps; each creator makes the singleton (names are guesses)
	void OpenUVData();                       // 0x104E1440
	void CreateProtoRenderManager();         // 0x102E52A0
	void CreateSaveGameManager();            // 0x10487D10
	void CreateGameFEManager();              // 0x104B55E0
	void CreateMissionObjectivesManager();   // 0x104BDB70
	void CreateUnlockablesManager();         // 0x105814D0
	void CreateWebOfIntrigueManager();       // 0x10561A30
	void CreateOnlineManager();              // 0x104A29E0
	void RegisterOnlineLua();                // 0x104DC4B0
	void SetLanguage(const char* name, int unknown);   // 0x104DDBB0
	// 0x104E2BC0: loads the packages of a front end group
	void LoadFrontEndPackages(const char* files, const char* group);
	// 0x104E1870: makes the heap of a slot of a front end group
	core::IMemoryAllocator* FrontEndHeap(int handle, engine::StreamSlotGroup* group, const char* name);
	// The Lua natives of the game (0x104E79D0, 0x104E7AB0)
	float GetRandomFloat();
	float GetWorldOrientation(float a, float b);

	// 0x1126EE70 .. : the names of the slot groups the engine looks up by number (guesses)
	core::Name<core::CaseSensitiveKey> gGroupName1126EE68("MissionPackageSlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gGroupName1126EE70("WorldCellGroup", 0);
	core::Name<core::CaseSensitiveKey> gGroupName1126EE78("DynamicPackageSlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gGroupName1126EEC8("PermanentMissionPackageSlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gGroupName11316F28("NISStreamGroup", 0);
	core::Name<core::CaseSensitiveKey> gGroupName11316F58("NISAnimStreamGroup", 0);

}

namespace proto
{
	// FUNCTION: ENGINE 0x104E1EB0
	GameEngine::GameEngine()
	{
		inGameState = 0;
		frontEndState = 0;
		pauseState = 0;
		simulationDriver = 0;
	}

	// FUNCTION: ENGINE 0x104E1620
	void GameEngine::Slot0(int unused)
	{
	}

	// FUNCTION: ENGINE 0x104E1ED0
	void GameEngine::Slot1()
	{
		if (!engine::HasCommandLineOption("DesyncHunt"))
		{
			engine::HasCommandLineOption("DesyncHunt2");
		}
		engine::CreateHeap(0x0B, 0x5000000, 0, "Sound", 0x100, 2, false, -1, false);
		engine::CreateHeap(0xB5, 0x28000, 0, "FreeRoamEvents Heap", 0x100, 2, false, -1, false);
		engine::CreateHeap(0x0A, 0x600000, 0, "Effects", 0, 2, false, -1, false);
		engine::CreateHeap(0x7A, 0x500000, 0, "Script", 0x100, 1, false, -1, false);
		if (!engine::HasCommandLineOption("BatchMode"))
		{
			if (!engine::HasCommandLineOption("ExportSchema"))
			{
				if (!engine::HasCommandLineOption("ExportHelpFile"))
				{
					engine::CreateHeap(1, 0x200000, 0, "Temporary", 0x100, 2, false, -1, false);
					engine::CreateHeap(0x78, 0x80000, 0, "Cement Files", 0x100, 2, false, -1, false);
					engine::CreateHeap(0x80, 0x40000, 0, "GameDB Heap", 0x100, 1, false, -1, false);
					engine::CreateHeap(0x6F, 0xA00000, 0, "Debug", 0, 2, false, -1, false);
					engine::CreateHeap(0x0C, 0x100000, 0, "Stream Information", 0, 2, false, -1, false);
					engine::HeapConfig2 config;
					config.index = 0xAF;
					config.size = 0x600000;
					config.heap = 0x6F;
					config.name = "Name Strings";
					config.alignment = 8;
					engine::CreateHeap(config);
					core::SetStringHeap(0xAF);
					engine::CreateHeap(0x76, 0x1900000, 0x1000, "Render", 0, 2, false, -1, false);
					engine::CreateHeap(0x72, 0x740000, 0x20, "Front End", 0, 2, false, -1, false);
					engine::CreateHeap(0x86, 0x300000, 0x1000, "Advertisements", 0, 2, false, -1, false);
					engine::CreateHeap(0x74, 0x50000, 0, "Static Fight", 0, 2, false, -1, false);
					engine::CreateHeap(0x75, 0x32C000, 0, "Dynamic Fight", 0, 2, false, -1, false);
					engine::CreateHeap(0xB9, 0x120000, 0, "Devastator", 0, 2, false, -1, false);
					engine::CreateHeap(0x77, 0xBB800, 0, "Decals", 0, 2, false, -1, false);
					engine::CreateHeap(0x85, 0x700000, 0, "Physics", 0, 2, false, -1, false);
					engine::CreateHeap(0x9C, 0x28800, 0, "Triggers", 0, 2, false, -1, false);
					engine::CreateHeap(0xA6, 0x90000, 0, "MissionDynamic", 0, 2, false, -1, false);
					engine::CreateHeap(0xA1, 0x100000, 0, "PedInstance", 0, 2, false, -1, false);
					engine::CreateHeap(0xA2, 0xD0000, 0, "PedDrawables", 0, 2, false, -1, false);
					engine::CreateHeap(0xA4, 0x500000, 0, "PropInstance", 0, 2, false, -1, false);
					engine::CreateHeap(0xA9, 0x550000, 0, "VehicleInstance", 0, 2, false, -1, false);
					engine::CreateHeap(0xA8, 0x110000, 0, "AmbientManager", 0, 2, false, -1, false);
					engine::CreateHeap(0x70, 0x60000, 0, "MainCharacter", 0, 2, false, -1, false);
					engine::CreateHeap(0x9E, 0x580800, 0, "Characters", 0, 2, false, -1, false);
					engine::CreateHeap(0xA0, 0x200000, 0, "DeadBody", 0, 2, false, -1, false);
					engine::CreateHeap(0x9F, 0xC0000, 0, "Consume", 0, 2, false, -1, false);
					engine::CreateHeap(0xB2, 0x40000, 0, "BlobShadows", 0x76, 2, false, -1, false);
					engine::CreateHeap(0xB4, 0x144000, 0, "Checkpoints", 0, 2, false, -1, false);
					engine::CreateHeap(0xB7, 0x30000, 0, "CollectibleInstance", 0, 2, false, -1, false);
					engine::CreateHeap(0xB6, 0x90000, 0, "AI", 0, 1, false, -1, false);
					engine::CreateHeap(0xB8, 0xE0000, 0, "Gameobject System", 0, 2, false, -1, false);
				}
			}
		}
		if (engine::HasCommandLineOption("SkipTopLevelMipMap"))
		{
			engine::render::gTextureLoadFlag = true;
		}
	}

	// FUNCTION: ENGINE 0x104E1630
	void GameEngine::Slot2()
	{
		if (!engine::HasCommandLineOption("BatchMode"))
		{
			if (!engine::HasCommandLineOption("ExportSchema"))
			{
				if (!engine::HasCommandLineOption("ExportHelpFile"))
				{
					engine::DestroyHeap(0xB8);
					engine::DestroyHeap(0xB6);
					engine::DestroyHeap(0xB7);
					engine::DestroyHeap(0xB4);
					engine::DestroyHeap(0xB2);
					engine::DestroyHeap(0x9F);
					engine::DestroyHeap(0xA0);
					engine::DestroyHeap(0x9E);
					engine::DestroyHeap(0x70);
					engine::DestroyHeap(0xA8);
					engine::DestroyHeap(0xA9);
					engine::DestroyHeap(0xA4);
					engine::DestroyHeap(0xA2);
					engine::DestroyHeap(0xA1);
					engine::DestroyHeap(0xA6);
					engine::DestroyHeap(0x9C);
					engine::DestroyHeap(0x85);
					engine::DestroyHeap(0x77);
					engine::DestroyHeap(0xB9);
					engine::DestroyHeap(0x75);
					engine::DestroyHeap(0x74);
					engine::DestroyHeap(0x86);
					engine::DestroyHeap(0x72);
					engine::DestroyHeap(0x76);
					engine::DestroyHeap(0xAF);
					engine::DestroyHeap(0x0C);
					engine::DestroyHeap(0x6F);
					engine::DestroyHeap(0x80);
					engine::DestroyHeap(0x78);
					engine::DestroyHeap(1);
				}
			}
		}
		engine::DestroyHeap(0x7A);
		engine::DestroyHeap(0x0A);
		engine::DestroyHeap(0xB5);
		engine::DestroyHeap(0x0B);
	}

	// FUNCTION: ENGINE 0x104E1810
	void GameEngine::Slot3()
	{
		ResetFightSystems();
	}

	// FUNCTION: ENGINE 0x104E19B0
	void GameEngine::Slot4()
	{
		engine::MakePropLogicContext();
		engine::MakePlaybackContext();
		engine::MakeMotionContext();
		engine::MakeNISContext();
		engine::MakeScenarioContext();
		RegisterFightContexts();
	}

	// FUNCTION: ENGINE 0x104E19E0
	void GameEngine::Slot5()
	{
		engine::scenario::ResetListers();
		engine::Unknown10811FC0();
		engine::Unknown10811FB0();
		engine::Unknown10811FA0();
		engine::Unknown10811F90();
		engine::Unknown10811F80();
	}

	// FUNCTION: ENGINE 0x104E1A10
	const char* GameEngine::Slot6()
	{
		return "SOFTWARE\\Activision\\Prototype";
	}

	// FUNCTION: ENGINE 0x104E1A20
	const char* GameEngine::Slot7()
	{
		return "FE_Language";
	}

	// FUNCTION: ENGINE 0x104E1A30
	engine::controller::DefaultControllerHandler* GetControllerHandler()
	{
		return gControllerHandler;
	}

	// FUNCTION: ENGINE 0x104E2540
	void GameEngine::Launch()
	{
		const char* level = engine::GetCommandLineValue("Level");
		if (level)
		{
			if (HasDevSelectLevel(level))
			{
				StartDevSelectLevel(level, 1, "DevSelect");
				FinishDevSelectStart();
			}
			GetControllerHandler()->LockController(0);
			GetFrontEndHud()->Unknown104B1470(1);
			frontEndState->SetStartUpFlowActive(false);
			engine::RequestGameState(2, 0, 0);
			return;
		}
		if (engine::GetCommandLineValue("Replay"))
		{
			GetControllerHandler()->LockController(0);
			GetFrontEndHud()->Unknown104B1470(1);
		}
		engine::RequestGameState(3, 2, 0);
	}

	// The script wrappers the registration of the two natives builds (function.h), and the zero-argument
	// LuaScriptManager::Register that goes with them: the compiler keeps this copy out of line (0x104E2F20) and inlines the
	// two-argument one
	// FUNCTION: ENGINE 0x104E2A10
	// FUNCTION: ENGINE 0x104E2A60
	// FUNCTION: ENGINE 0x104E2A90
	// FUNCTION: ENGINE 0x104E2AC0
	// FUNCTION: ENGINE 0x104E2B30
	// FUNCTION: ENGINE 0x104E2B70
	// FUNCTION: ENGINE 0x104E2F20

	// FUNCTION: ENGINE 0x104E3840
	void GameEngine::Initialize(int unused)
	{
		OpenUVData();
		if (core::HasCement())
		{
			core::Name<core::CaseSensitiveKey> name("default", 1);
			core::StartCement(name, 0);
			while (core::PollCement() != 0)
			{
				core::FileSystemUpdate();
			}
		}
		CreateProtoRenderManager();
		engine::GetZoneSet()->SetDefaults(engine::gDefaultZones);
		engine::GetZoneSet()->AddZone("zone2", "art/massive.p3d", 3, engine::gZone2Entries);
		gProtoRenderManager->Initialize();
		if (gUVDataFound)
		{
			CreateSaveGameManager();
		}
		bool autotest;
		if (engine::HasCommandLineOption("Autotester") && !core::IsDebugLinkClosed())
		{
			autotest = true;
		}
		else
		{
			autotest = false;
		}
		core::OpenReportFile("prototype.rch", autotest);
		core::InitChannels(0x40, 0);
		RegisterOnlineLua();
		CreateUnlockablesManager();
		CreateWebOfIntrigueManager();
		CreateGameFEManager();
		CreateMissionObjectivesManager();
		gControllerHandler = new engine::controller::DefaultControllerHandler(2);
		simulationDriver = new engine::SimulationDriver();
		engine::SetSimulationDriver(simulationDriver);
		inGameState = new InGameState();
		frontEndState = new FrontEndState();
		pauseState = new GamePauseState();
		engine::AddGameState(frontEndState, 3, 0, 0, 1, 0);
		engine::AddGameState(inGameState, 2, 0, 1, 1, 0);
		simulationDriver->SetUnknown70(0);
		math::gRandom->Seed(0);
		engine::LuaScriptManager* script = engine::GetScriptManager();
		script->SetOwner(this);
		script->Register("util_GetRandomFloat", GetRandomFloat);
		script->Register("util_GetWorldOrientation", GetWorldOrientation);
		script->ClearOwner();
		CreateOnlineManager();
		script->RunInitScript();
		Launch();
		if (engine::HasCommandLineOption("IncreaseArtHeaps"))
		{
			gArtMemory -= 0x100000;
		}
		SlotGroupConfig startup;
		SlotGroupConfig effects;
		SlotGroupConfig figs;
		SlotGroupConfig g70;
		SlotGroupConfig location;
		SlotGroupConfig midground;
		SlotGroupConfig prop;
		SlotGroupConfig mission;
		SlotGroupConfig alex;
		SlotGroupConfig gec8;
		SlotGroupConfig g68;
		SlotGroupConfig soldier;
		SlotGroupConfig permchar;
		SlotGroupConfig air;
		SlotGroupConfig armor;
		SlotGroupConfig g78;
		SlotGroupConfig vehshared;
		SlotGroupConfig vehslot;
		SlotGroupConfig pedshared;
		SlotGroupConfig pedslot;
		SlotGroupConfig mainchar;
		SlotGroupConfig mcpowers;
		SlotGroupConfig fetext;
		SlotGroupConfig fepermanent;
		SlotGroupConfig fetransient;
		SlotGroupConfig g11316f28;
		SlotGroupConfig g11316f58;
		SlotGroupConfig fmv;
		startup.size = 0x280000;
		startup.flag = false;
		startup.alignment = 0;
		effects.size = 0x500000;
		effects.flag = false;
		effects.alignment = 0x200;
		figs.size = 0x800000;
		figs.flag = false;
		figs.alignment = 0;
		location.size = 0x720000;
		location.flag = false;
		location.alignment = 0x200;
		prop.size = 0x500000;
		prop.flag = false;
		prop.alignment = 0x800;
		midground.size = 0x200000;
		midground.flag = false;
		midground.alignment = 0x800;
		g70.size = 0x400000;
		g70.flag = false;
		g70.alignment = 0x800;
		mission.size = 0x40000;
		mission.flag = false;
		mission.alignment = 0;
		alex.size = 0x17000;
		alex.flag = false;
		alex.alignment = 0;
		gec8.size = 0x40000;
		gec8.flag = false;
		gec8.alignment = 0;
		g68.size = 0x1C0000;
		g68.flag = false;
		g68.alignment = 0x800;
		soldier.size = 0x8A0000;
		soldier.flag = false;
		soldier.alignment = 0x200;
		permchar.size = 0x400000;
		permchar.flag = false;
		permchar.alignment = 0x200;
		air.size = 0x200000;
		air.flag = false;
		air.alignment = 0x200;
		armor.size = 0x190000;
		armor.flag = false;
		armor.alignment = 0x200;
		g78.size = 0x280000;
		g78.flag = false;
		g78.alignment = 0x200;
		vehshared.size = 0x80000;
		vehshared.flag = false;
		vehshared.alignment = 0x200;
		vehslot.size = 0x80000;
		vehslot.flag = false;
		vehslot.alignment = 0x200;
		pedshared.size = 0x700000;
		pedshared.flag = false;
		pedshared.alignment = 0x80;
		pedslot.size = 0x80000;
		pedslot.flag = false;
		pedslot.alignment = 0x80;
		mainchar.size = 0xE00000;
		mainchar.flag = false;
		mainchar.alignment = 0x200;
		mcpowers.size = 0x500000;
		mcpowers.flag = false;
		mcpowers.alignment = 0x100;
		fepermanent.size = 0x40000;
		fepermanent.flag = false;
		fepermanent.alignment = 0x200;
		fetransient.size = 0x40000;
		fetransient.flag = false;
		fetransient.alignment = 0x800;
		fetext.size = 0x80000;
		fetext.flag = false;
		fetext.alignment = 0;
		{
			core::Name<core::CaseSensitiveKey> name("Startup_Group", 1);
			CreateSlotGroup(name, 1, &startup, false, true, 0, 0);
		}
		{
			core::Name<core::CaseSensitiveKey> name("EffectsSlotGroup", 1);
			CreateSlotGroup(name, 1, &effects, false, true, 0, 0);
		}
		{
			core::Name<core::CaseSensitiveKey> name("FigsSlotGroup", 1);
			CreateSlotGroup(name, 1, &figs, false, true, 0, 0);
		}
		engine::StreamSlotGroup* group = CreateSlotGroup(gGroupName1126EE70, 7, &g70, false, false, 0, 0);
		group->priority = 1;
		{
			core::Name<core::CaseSensitiveKey> name("LocationGroup", 1);
			CreateSlotGroup(name, 1, &location, false, true, 0, 0);
		}
		{
			core::Name<core::CaseSensitiveKey> name("LocationMidgroundGroup", 1);
			CreateSlotGroup(name, 1, &midground, false, true, 0, 0);
		}
		{
			core::Name<core::CaseSensitiveKey> name("LocationPropGroup", 1);
			CreateSlotGroup(name, 1, &prop, false, true, 0, 0);
		}
		{
			core::Name<core::CaseSensitiveKey> name("MissionScriptGroup", 1);
			CreateSlotGroup(name, 3, &mission, true, true, 0, 0);
		}
		{
			core::Name<core::CaseSensitiveKey> name("AlexMissionSlotGroup", 1);
			CreateSlotGroup(name, 1, &alex, false, true, 0, 0);
		}
		CreateSlotGroup(gGroupName1126EEC8, 2, &gec8, true, true, 0, 0);
		CreateSlotGroup(gGroupName1126EE68, 3, &g68, true, true, 0, 0);
		{
			core::Name<core::CaseSensitiveKey> name("SoldierPackageSlotGroup", 1);
			CreateSlotGroup(name, 1, &soldier, false, true, 0, 0);
		}
		{
			core::Name<core::CaseSensitiveKey> name("PermanentCharacterPackageSlotGroup", 1);
			CreateSlotGroup(name, 1, &permchar, false, true, 0, 0);
		}
		{
			core::Name<core::CaseSensitiveKey> name("AirUnitPackageSlotGroup", 1);
			CreateSlotGroup(name, 1, &air, false, true, 0, 0);
		}
		{
			core::Name<core::CaseSensitiveKey> name("ArmorUnitPackageSlotGroup", 1);
			CreateSlotGroup(name, 1, &armor, false, true, 0, 0);
		}
		CreateSlotGroup(gGroupName1126EE78, 3, &g78, false, true, 0, 0);
		{
			core::Name<core::CaseSensitiveKey> name("VehicleSharedGroup", 1);
			CreateSlotGroup(name, 1, &vehshared, false, true, 0, 0);
		}
		{
			core::Name<core::CaseSensitiveKey> name("VehicleSlotGroup", 1);
			CreateSlotGroup(name, 6, &vehslot, false, true, 0, 0);
		}
		{
			core::Name<core::CaseSensitiveKey> name("PedestrianSharedGroup", 1);
			CreateSlotGroup(name, 1, &pedshared, false, true, 0, 0);
		}
		{
			core::Name<core::CaseSensitiveKey> name("PedestrianSlotGroup", 1);
			CreateSlotGroup(name, 0xC, &pedslot, false, true, 0, 0);
		}
		{
			core::Name<core::CaseSensitiveKey> name("MainCharacterSlotGroup", 1);
			CreateSlotGroup(name, 1, &mainchar, false, true, 0, 0);
		}
		{
			core::Name<core::CaseSensitiveKey> name("MainCharacterPowersSlotGroup", 1);
			group = CreateSlotGroup(name, 5, &mcpowers, true, true, 0, 0);
		}
		group->priority = 1;
		{
			core::Name<core::CaseSensitiveKey> name("FETextBible", 1);
			CreateSlotGroup(name, 1, &fetext, false, false, FrontEndHeap, 0);
		}
		{
			core::Name<core::CaseSensitiveKey> name("FEPermanent", 1);
			CreateSlotGroup(name, 1, &fepermanent, false, false, FrontEndHeap, 0);
		}
		{
			core::Name<core::CaseSensitiveKey> name("FETransient", 1);
			group = CreateSlotGroup(name, 1, &fetransient, false, false, 0, 0);
		}
		engine::SetFrontEndHeap(group->GetSlot(0)->heap);
		group->priority = 0;
		group->unknown68 = false;
		g11316f28.size = 0x800000;
		g11316f28.flag = false;
		g11316f28.alignment = 0;
		g11316f58.size = 0x100000;
		g11316f58.flag = false;
		g11316f58.alignment = 0;
		CreateSlotGroup(gGroupName11316F28, 3, &g11316f28, false, true, 0, 0);
		CreateSlotGroup(gGroupName11316F58, 6, &g11316f58, false, true, 0, 0);
		fmv.size = 0x100000;
		fmv.flag = false;
		fmv.alignment = 0;
		{
			core::Name<core::CaseSensitiveKey> name("FMVSubTitleSlotGroup", 1);
			CreateSlotGroup(name, 1, &fmv, false, true, 0, 0);
		}
		LoadFrontEndPackages("art/hud/fe_resourcetable.p3d;art/hud/fe_permanent.p3d", "FEPermanent");
		int language = core::LanguageGet();
		SetLanguage(core::GetLanguageName(language), 0);
		gFrontend = (engine::FrontEnd*)engine::CreateFrontend((int)"protomain", 0);
		engine::SetFrontend(gFrontend);
	}
}

namespace proto
{
	core::Name<core::CaseSensitiveKey> gNISAnimStreamTag("NISAnimStreamTag", 0);
}

namespace proto
{
	core::Name<core::CaseSensitiveKey> gNISStreamTag("NISStreamTag", 0);
	core::Name<core::CaseSensitiveKey> gLocatorForNIS("Locator for NIS ", 0);
	core::Name<core::CaseSensitiveKey> gShotGroup("Shot-Group", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup2("Undefined_SlotGroup", 0);
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D773C0
// FUNCTION: ENGINE 0x10D77440
// FUNCTION: ENGINE 0x10D77460
// FUNCTION: ENGINE 0x10D77480
// FUNCTION: ENGINE 0x10D8A9D0
// FUNCTION: ENGINE 0x10D8AA10
// FUNCTION: ENGINE 0x10D8AA20
// FUNCTION: ENGINE 0x10D8AAB0


// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D60EF0
// FUNCTION: ENGINE 0x10D60F20
// FUNCTION: ENGINE 0x10D60F50
// FUNCTION: ENGINE 0x10D60F80
// FUNCTION: ENGINE 0x10D773E0
// FUNCTION: ENGINE 0x10D77400
// FUNCTION: ENGINE 0x10D77420
// FUNCTION: ENGINE 0x10D858C0
// FUNCTION: ENGINE 0x10D858D0
// FUNCTION: ENGINE 0x10D858E0
// FUNCTION: ENGINE 0x10D858F0
// FUNCTION: ENGINE 0x10D8A9E0
// FUNCTION: ENGINE 0x10D8A9F0
// FUNCTION: ENGINE 0x10D8AA00
