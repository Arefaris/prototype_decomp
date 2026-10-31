// The states of a stream package's load state machine (RTTI names engine::streampackagestates::*; unit 0x108A6010 -
// 0x108A6D90, no assert path; file name guessed). The machine itself is StreamPackageInstance in streampackage.cpp.
#include "code/engine/system/streampackage.h"

namespace engine
{
	// 0x11318098: the state that is loading now (name guess)
	streampackagestates::Loading* gLoadingState;
	// 0x11318118: the slot group the prerequisites are asked to load in (name guess)
	extern content::ObjectName gPrerequisiteSlotGroup;
	// 0x1130EFDC: the counter the eviction delay is measured in (name guess)
	extern unsigned int gStreamCounter;

	namespace streampackagestates
	{
		// FUNCTION: ENGINE 0x108A6D00
		Unloaded::Unloaded(StreamPackageInstance* newInstance) : StreamPackageState("Unloaded", newInstance)
		{
		}

		// FUNCTION: ENGINE 0x108A6D40
		void Unloaded::Enter()
		{
			StreamPackage::PackageList* prerequisites = instance->package->prerequisites;
			if (prerequisites != 0)
			{
				StreamPackage** it = prerequisites->begin;
				StreamPackage** end = prerequisites->end;
				for (; it != end; it++)
				{
					(*it)->Unload(instance->package, false);
				}
			}
			instance->DetachSlot();
			instance->ReleaseLoaders();
		}

		// FUNCTION: ENGINE 0x108A6D20
		bool Unloaded::Exit(int next)
		{
			return true;
		}

		// FUNCTION: ENGINE 0x108A6D30
		int Unloaded::Update()
		{
			return StreamPackageInstance::STATE_NONE;
		}

		// FUNCTION: ENGINE 0x108A6C20
		WaitForPrerequisites::WaitForPrerequisites(StreamPackageInstance* newInstance) : StreamPackageState("WaitForPrerequisites", newInstance)
		{
		}

		// FUNCTION: ENGINE 0x108A6C50
		void WaitForPrerequisites::Enter()
		{
			StreamPackage::PackageList* prerequisites = instance->package->prerequisites;
			if (prerequisites != 0)
			{
				StreamPackage** end = prerequisites->end;
				for (StreamPackage** it = prerequisites->begin; it != end; it++)
				{
					StreamPackage* prerequisite = *it;
					StreamPackage* requester = instance->package;
					prerequisite->Load(requester, instance->GetPriority(), gPrerequisiteSlotGroup, false);
				}
			}
		}

		// FUNCTION: ENGINE 0x108A6CA0
		int WaitForPrerequisites::Update()
		{
			StreamPackage::PackageList* prerequisites = instance->package->prerequisites;
			if (prerequisites != 0)
			{
				StreamPackage** it = prerequisites->begin;
				StreamPackage** end = prerequisites->end;
				for (; it != end; it++)
				{
					if ((*it)->GetState() != 5)
					{
						return StreamPackageInstance::STATE_NONE;
					}
				}
			}
			StreamSlot* slot = instance->group->FindFreeSlot();
			if (slot != 0 && instance->AttachSlot(slot))
			{
				return StreamPackageInstance::STATE_LOADING;
			}
			return StreamPackageInstance::STATE_NONE;
		}

		// FUNCTION: ENGINE 0x108A6C40
		bool WaitForPrerequisites::Exit(int next)
		{
			return true;
		}

		// FUNCTION: ENGINE 0x108A6B20
		CancelLoading::CancelLoading(StreamPackageInstance* newInstance) : StreamPackageState("CancelLoading", newInstance), unknownC(false)
		{
		}

		// FUNCTION: ENGINE 0x108A6B40
		bool CancelLoading::Exit(int next)
		{
			return unknownC;
		}

		// FUNCTION: ENGINE 0x108A6AA0
		ClientLoading::ClientLoading(StreamPackageInstance* newInstance) : StreamPackageState("ClientLoading", newInstance), unknownC(0)
		{
		}

		// FUNCTION: ENGINE 0x108A6AC0
		void ClientLoading::Enter()
		{
			unknownC = 0;
		}

		// FUNCTION: ENGINE 0x108A6AD0
		bool ClientLoading::Exit(int next)
		{
			if (unknownC)
			{
				return true;
			}
			return false;
		}

		// FUNCTION: ENGINE 0x108A6AE0
		int ClientLoading::Update()
		{
			if (instance->UpdateClientLoading())
			{
				unknownC = 1;
				return StreamPackageInstance::STATE_LOADED;
			}
			return StreamPackageInstance::STATE_NONE;
		}

		// FUNCTION: ENGINE 0x108A65E0
		Loaded::Loaded(StreamPackageInstance* newInstance) : StreamPackageState("Loaded", newInstance)
		{
		}

		// FUNCTION: ENGINE 0x108A6600
		int Loaded::Update()
		{
			return StreamPackageInstance::STATE_NONE;
		}

		// FUNCTION: ENGINE 0x108A6580
		WaitForUnloads::WaitForUnloads(StreamPackageInstance* newInstance) : StreamPackageState("WaitForUnloads", newInstance)
		{
		}

		// FUNCTION: ENGINE 0x108A65A0
		void WaitForUnloads::Enter()
		{
		}

		// FUNCTION: ENGINE 0x108A65B0
		bool WaitForUnloads::Exit(int next)
		{
			return true;
		}

		// FUNCTION: ENGINE 0x108A65C0
		int WaitForUnloads::Update()
		{
			return StreamPackageInstance::STATE_CLIENT_UNLOADING;
		}

		// FUNCTION: ENGINE 0x108A6510
		ClientUnloading::ClientUnloading(StreamPackageInstance* newInstance) : StreamPackageState("ClientsUnloading", newInstance), unknownC(false)
		{
		}

		// FUNCTION: ENGINE 0x108A6530
		void ClientUnloading::Enter()
		{
			unknownC = false;
		}

		// FUNCTION: ENGINE 0x108A6540
		bool ClientUnloading::Exit(int next)
		{
			return unknownC;
		}

		// FUNCTION: ENGINE 0x108A6550
		int ClientUnloading::Update()
		{
			if (instance->UpdateClientUnloading())
			{
				unknownC = true;
				return StreamPackageInstance::STATE_EVICTABLE;
			}
			return StreamPackageInstance::STATE_NONE;
		}

		// FUNCTION: ENGINE 0x108A6440
		Evictable::Evictable(StreamPackageInstance* newInstance) : StreamPackageState("Evictable", newInstance), deadline(0), unknown10(true)
		{
		}

		// FUNCTION: ENGINE 0x108A6470
		void Evictable::Enter()
		{
			unknown10 = false;
			deadline = gStreamCounter + 0x32;
		}

		// FUNCTION: ENGINE 0x108A6480
		bool Evictable::Exit(int next)
		{
			return unknown10;
		}

		// FUNCTION: ENGINE 0x108A6070
		Loading::Loading(StreamPackageInstance* newInstance) : StreamPackageState("Loading", newInstance), total(0), unknown10(0)
		{
		}

		// FUNCTION: ENGINE 0x108A60A0
		bool Loading::IsActive() const
		{
			if (gLoadingState == this)
			{
				return true;
			}
			return false;
		}

		// FUNCTION: ENGINE 0x108A60F0
		void Loading::Enter()
		{
			StreamPackage::ResourceList* resources = instance->package->resources;
			int count = resources->end - resources->begin;
			total = count;
			unknown14 = count;
			unknown10 = 0;
			unknown1C = false;
		}

		// FUNCTION: ENGINE 0x108A6110
		bool Loading::Exit(int next)
		{
			if (next == StreamPackageInstance::STATE_CLIENT_LOADING && !unknown1C)
			{
				return false;
			}
			if (gLoadingState == this)
			{
				gLoadingState = 0;
			}
			return true;
		}
	}
}

namespace engine
{
	core::Name<core::CaseSensitiveKey> gPrerequisiteSlotGroup("Undefined_SlotGroup", 0);
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D77A30
// FUNCTION: ENGINE 0x10D8ACC0
