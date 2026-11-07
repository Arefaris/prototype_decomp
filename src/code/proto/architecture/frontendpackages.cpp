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

namespace engine
{
	// 0x1082C6D0 / 0x108366F0
	void Unknown1082C6D0();
	void YieldFiber();
	// 0x10861170 / 0x10861270 (name unknown)
	void Unknown10861170(core::Time first, core::Time second);
	void Unknown10861270();

	// 0x11283xxx..: the name of the group the packages of the front end are in (0x1126EE48)
	extern core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup6;
}

namespace content
{
	// 0x106075F0
	void UpdateLoads();
}

namespace proto
{
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
	// NONMATCHING: the engine builds the two Time arguments in place (the class has a copy constructor there), 39.5 %
#ifdef NONMATCHING
	void UnloadFrontEndPackages(const char* group)
	{
		if (core::StrCmp(group, "FETransient") == 0)
		{
			if (gFrontEndTransient)
			{
				gFrontEndTransient->Unload(0, false);
				for (;;)
				{
					gFrontEndTransient->ReleaseRequests();
					if (gFrontEndTransient->GetState() == 0 && gFrontEndTransient->instance == 0)
					{
						break;
					}
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
					core::Time first(0, 0);
					core::Time second(0, 0);
					engine::Unknown10861170(first, second);
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
#endif

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

	// FUNCTION: ENGINE 0x104E2860
	// NONMATCHING: the engine builds the name temporaries in one frame slot behind a zeroed word, 60.7 %
#ifdef NONMATCHING
	void StartFrontEndTransientLoad(const char* files, const char* group)
	{
		gFrontEndTransient = new engine::StreamPackage(core::Name<core::CaseSensitiveKey>(group, 1));
		gFrontEndTransient->slotGroup = core::Name<core::CaseSensitiveKey>(group, 1);
		gFrontEndTransient->SetResources(files);
		gFrontEndTransient->tags.FromString("FEResourceTag");
		gFrontEndTransient->sync = false;
		gFrontEndTransient->Load(0, 0xFFFF, engine::gUndefinedSlotGroup6, false);
	}
#endif

	// FUNCTION: ENGINE 0x104E2BC0
	// NONMATCHING: the names are built in one frame slot like StartFrontEndTransientLoad's, 58.7 %
#ifdef NONMATCHING
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
			gFrontEndPermanent = new engine::StreamPackage(core::Name<core::CaseSensitiveKey>(group, 1));
			gFrontEndPermanent->slotGroup = core::Name<core::CaseSensitiveKey>(group, 1);
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
			gFrontEndTextBible = new engine::StreamPackage(core::Name<core::CaseSensitiveKey>(group, 1));
			gFrontEndTextBible->slotGroup = core::Name<core::CaseSensitiveKey>(group, 1);
			gFrontEndTextBible->SetResources(files);
			container::StringC<256> tags;
			tags.Format("%s;__Persistent__", "FEResourceTag");
			gFrontEndTextBible->inventoryInitialSize = 4;
			gFrontEndTextBible->tags.FromString(tags.ConstData());
			gFrontEndTextBible->Load(0, 0xFFFF, engine::gUndefinedSlotGroup6, false);
			while (gFrontEndTextBible->GetState() != 5)
			{
				engine::Unknown1082C6D0();
				content::UpdateLoads();
			}
		}
	}
#endif
}
