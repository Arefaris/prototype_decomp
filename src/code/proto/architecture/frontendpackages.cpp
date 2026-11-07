// The front end's resource packages (FETransient, FEPermanent, FETextBible): loaded and unloaded by name while the game
// starts and when it goes between the front end and the world, and the heaps of the slots the stream manager gives them.
// The unit follows the game engine's in the engine (0x104E1820 - 0x104E2BC0; no assert path names it, so the file name
// and the function names are guesses).
#include "code/container/string.h"
#include <new>
#include "code/core/heap.h"
#include "code/core/strings.h"
#include "code/core/time.h"
#include "code/engine/system/desynchunter.h"
#include "code/engine/system/enginememory.h"
#include "code/engine/system/streampackage.h"
#include "code/engine/controller/defaultcontrollerhandler.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/system/simulationdriver.h"
#include "code/core/file/mounts.h"
#include "code/core/report.h"
#include "code/proto/protomain.h"

namespace engine
{
	// 0x1082C6D0 / 0x108366F0
	void Unknown1082C6D0();
	void YieldFiber();
	// The two times the frame step takes: the engine builds them in place in the argument area (its class declares a
	// copy constructor), which a class of this unit does with a declaration only
	struct StepTime : public core::Time
	{
		StepTime(unsigned int newMilliseconds, unsigned int newMicroseconds) : core::Time(newMilliseconds, newMicroseconds)
		{
		}
		StepTime(const StepTime& other);
	};
	// 0x10861170 / 0x10861270 (name unknown)
	void Unknown10861170(StepTime first, StepTime second);
	void Unknown10861270();

	// 0x11283xxx..: the name of the group the packages of the front end are in (0x1126EE48)
	extern core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup6;
}

namespace engine
{
	// The front end object (the same class as femovie.cpp's); the game engine deletes it when it shuts down
	class FrontEnd
	{
	public:
		// 0x10872920
		void Unknown10872920(const char* newName);
		// 0x108727E0
		~FrontEnd();
	};
	FrontEnd* Unknown10864330();
	// 0x10864310 / 0x10837B10
	void SetFrontend(void* frontend);
	void FreeGameState(int number);
	// The shutdown of the content manager's cement tables (names unknown): 0x10884000 asks whether one is open,
	// 0x10883FF0 closes the one of that name, 0x10884010 answers how many requests are left
	bool Unknown10884000();
	void Unknown10883FF0(const core::Name<core::CaseSensitiveKey>& name, int mode);
	int Unknown10884010();
	// 0x10644620 (core), 0x10126280
	void Unknown10644620();
}

namespace content
{
	// 0x106075F0
	void UpdateLoads();
}

namespace proto
{
	// The name a package or slot group is registered under
	static inline core::Name<core::CaseSensitiveKey> MakeName(const char* text)
	{
		return core::Name<core::CaseSensitiveKey>(text, 1);
	}

	// 0x1126EE18 / 0x1126EE14 / 0x1126EE10: the packages (name guesses)
	engine::StreamPackage* gFrontEndTransient;
	engine::StreamPackage* gFrontEndPermanent;
	engine::StreamPackage* gFrontEndTextBible;

	// FUNCTION: ENGINE 0x104E1820
	core::IMemoryAllocator* FrontEndHeapOneWay(int handle, engine::StreamSlotGroup* group, const char* name)
	{
		int config[3];
		group->GetSlotHeapConfig(config);
		int heap = core::GetCurrentHeap();
		return engine::CreateHeap(handle, config[0], 0, name, heap, 2, false, -1, false);
	}

	// FUNCTION: ENGINE 0x104E1870
	core::IMemoryAllocator* FrontEndHeap(int handle, engine::StreamSlotGroup* group, const char* name)
	{
		int config[3];
		group->GetSlotHeapConfig(config);
		int heap = core::GetCurrentHeap();
		return engine::CreateTwoWayHeap(handle, config[0], 0, name, heap, 2, false, -1);
	}

	// FUNCTION: ENGINE 0x104E1A40
	void UnloadFrontEndPackages(const char* group)
	{
		if (core::StrCmp(group, "FETransient") == 0)
		{
			if (gFrontEndTransient)
			{
				gFrontEndTransient->Unload(0, false);
				gFrontEndTransient->ReleaseRequests();
				while (gFrontEndTransient->GetState() != 0 || gFrontEndTransient->instance != 0)
				{
					engine::YieldFiber();
				}
				delete gFrontEndTransient;
				gFrontEndTransient = 0;
			}
		}
		else if (core::StrCmp(group, "FEPermanent") == 0)
		{
			if (gFrontEndPermanent)
			{
				engine::DesyncHunter::PushMode(0);
				gFrontEndPermanent->Unload(0, false);
				gFrontEndPermanent->ReleaseRequests();
				while (gFrontEndPermanent->GetState() != 0 || gFrontEndPermanent->instance != 0)
				{
					engine::Unknown1082C6D0();
					content::UpdateLoads();
					engine::Unknown10861170(engine::StepTime(0, 0), engine::StepTime(0, 0));
					engine::Unknown10861270();
				}
				delete gFrontEndPermanent;
				gFrontEndPermanent = 0;
				engine::DesyncHunter::PopMode();
			}
		}
		else if (core::StrCmp(group, "FETextBible") == 0)
		{
			if (gFrontEndTextBible)
			{
				engine::DesyncHunter::PushMode(0);
				gFrontEndTextBible->Unload(0, false);
				gFrontEndTextBible->ReleaseRequests();
				while (gFrontEndTextBible->GetState() != 0 || gFrontEndTextBible->instance != 0)
				{
					engine::Unknown1082C6D0();
					content::UpdateLoads();
				}
				delete gFrontEndTextBible;
				gFrontEndTextBible = 0;
				engine::DesyncHunter::PopMode();
			}
		}
	}

	// FUNCTION: ENGINE 0x104E1C50
	void BeginFrontEndTransientUnload()
	{
		if (gFrontEndTransient)
		{
			gFrontEndTransient->Unload(0, false);
			gFrontEndTransient->ReleaseRequests();
		}
	}

	// FUNCTION: ENGINE 0x104E1C80
	bool FinishFrontEndTransientUnload()
	{
		if (gFrontEndTransient)
		{
			if (gFrontEndTransient->GetState() != 0 || gFrontEndTransient->instance != 0)
			{
				return false;
			}
			delete gFrontEndTransient;
			gFrontEndTransient = 0;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x104E1CD0
	bool IsFrontEndTransientLoaded()
	{
		if (!gFrontEndTransient)
		{
			return false;
		}
		return gFrontEndTransient->GetState() == 5;
	}

	// 0x1126EE1C / 0x1126EE28 (protomain.cpp)
	extern engine::FrontEnd* gFrontend;
	extern engine::controller::DefaultControllerHandler* gControllerHandler;
	// The shutdown calls of the game engine (names unknown)
	void ShutdownProtoRenderManager();  // 0x102E4610
	void Unknown104A0A60();
	void Unknown1047F900();
	void Unknown104BD0D0();
	void Unknown104B09D0();
	void Unknown10579280();
	void Unknown10562FF0();
	void Unknown104DBBD0();
	void Unknown10126280();

	// FUNCTION: ENGINE 0x104E2860
	void StartFrontEndTransientLoad(const char* files, const char* group)
	{
		gFrontEndTransient = new engine::StreamPackage(MakeName(group));
		gFrontEndTransient->slotGroup = MakeName(group);
		gFrontEndTransient->SetResources(files);
		gFrontEndTransient->tags.FromString("FEResourceTag");
		gFrontEndTransient->sync = false;
		gFrontEndTransient->Load(0, 0xFFFF, engine::gUndefinedSlotGroup6, false);
	}

	// FUNCTION: ENGINE 0x104E2BC0
	void LoadFrontEndPackages(const char* files, const char* group)
	{
		UnloadFrontEndPackages(group);
		if (core::StrCmp(group, "FETransient") == 0)
		{
			StartFrontEndTransientLoad(files, group);
			if (gFrontEndTransient->GetState() != 5)
			{
				do
				{
					engine::YieldFiber();
				}
				while (gFrontEndTransient->GetState() != 5);
			}
		}
		else if (core::StrCmp(group, "FEPermanent") == 0)
		{
			gFrontEndPermanent = new engine::StreamPackage(MakeName(group));
			gFrontEndPermanent->slotGroup = MakeName(group);
			gFrontEndPermanent->SetResources(files);
			container::StringC<256> tags;
			tags.Format("%s;__Persistent__", "FEResourceTag");
			gFrontEndPermanent->inventoryInitialSize = 0x100;
			gFrontEndPermanent->tags.FromString(tags.ConstData());
			gFrontEndPermanent->sync = false;
			gFrontEndPermanent->Load(0, 0xFFFF, engine::gUndefinedSlotGroup6, false);
			while (gFrontEndPermanent->GetState() != 5)
			{
				engine::Unknown1082C6D0();
				content::UpdateLoads();
			}
		}
		else if (core::StrCmp(group, "FETextBible") == 0)
		{
			gFrontEndTextBible = new engine::StreamPackage(MakeName(group));
			gFrontEndTextBible->slotGroup = MakeName(group);
			gFrontEndTextBible->SetResources(files);
			container::StringC<256> tags;
			tags.Format("%s;__Persistent__", "FEResourceTag");
			gFrontEndTextBible->inventoryInitialSize = 4;
			gFrontEndTextBible->tags.FromString(tags.ConstData());
			gFrontEndTextBible->sync = false;
			gFrontEndTextBible->Load(0, 0xFFFF, engine::gUndefinedSlotGroup6, false);
			while (gFrontEndTextBible->GetState() != 5)
			{
				engine::Unknown1082C6D0();
				content::UpdateLoads();
			}
		}
	}

	// FUNCTION: ENGINE 0x104E2620
	void GameEngine::Slot10()
	{
		engine::Unknown10864330()->Unknown10872920("NONE");
		for (int i = 10; i != 0; i--)
		{
			engine::Unknown10861170(engine::StepTime(0, 0), engine::StepTime(0, 0));
			engine::Unknown10861270();
		}
		engine::SetFrontend(0);
		delete gFrontend;
		for (int i = 10; i != 0; i--)
		{
			engine::Unknown10861170(engine::StepTime(0, 0), engine::StepTime(0, 0));
			engine::Unknown10861270();
		}
		UnloadFrontEndPackages("FEPermanent");
		UnloadFrontEndPackages("FETextBible");
		ShutdownProtoRenderManager();
		if (engine::Unknown10884000())
		{
			engine::Unknown10883FF0(MakeName("default"), 0);
			if (engine::Unknown10884010())
			{
				do
				{
					core::FileSystemUpdate();
				}
				while (engine::Unknown10884010());
			}
		}
		engine::Unknown10644620();
		Unknown104A0A60();
		engine::LuaScriptManager* script = engine::GetScriptManager();
		script->Unregister(this);
		engine::FreeGameState(3);
		engine::FreeGameState(2);
		Unknown1047F900();
		if (inGameState)
		{
			delete inGameState;
		}
		if (frontEndState)
		{
			delete frontEndState;
		}
		if (pauseState)
		{
			delete pauseState;
		}
		delete gControllerHandler;
		if (simulationDriver)
		{
			delete simulationDriver;
		}
		Unknown104BD0D0();
		Unknown104B09D0();
		Unknown10579280();
		Unknown10562FF0();
		Unknown104DBBD0();
		core::ShutdownChannels();
		Unknown10126280();
	}
}
