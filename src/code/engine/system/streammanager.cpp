// The stream manager's unit: see the header. The file name and the names are guesses.
#include "code/engine/system/streammanager.h"

#include "code/core/heap.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/system/streampackage.h"
#include "code/engine/system/streamtrigger.h"
#include "code/engine/system/tagset.h"
#include "code/math/vector.h"
#include <new>

namespace engine
{
	extern fight::EnumEntry gStartupGroupTable[3];
	extern fight::EnumEntry gStartupPackageTable[3];
	// The text of the tags that keep the startup packages in memory (0x111C41A0)
	extern const char* const gPersistentText;

	// FUNCTION: ENGINE 0x1082BEC0
	bool StreamManager::IsBusy()
	{
		return gStreamManager->unknown114 != 0;
	}

	// FUNCTION: ENGINE 0x1082BE90
	void StreamManager::AdvanceState()
	{
		StreamManager* manager = gStreamManager;
		switch (manager->unknown114)
		{
		case 0:
			manager->unknown114 = 1;
			break;
		case 1:
			manager->unknown114 = 2;
			break;
		}
	}

	// FUNCTION: ENGINE 0x1082BEE0
	bool ComparePackagePriority(StreamPackage* const* first, StreamPackage* const* second)
	{
		StreamPackageInstance* firstInstance = (*first)->instance;
		StreamPackageInstance* secondInstance = (*second)->instance;
		return secondInstance->GetPriority() < firstInstance->GetPriority();
	}

	// FUNCTION: ENGINE 0x1082BF70
	int StreamManager::IsGroupLoaded(int group)
	{
		StreamManager* manager = gStreamManager;
		if (manager->groupPackages[group] != 0 && manager->groupPackages[group]->GetState() == 5)
		{
			return 1;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1082BFA0
	int StreamManager::IsGroupWithoutInstance(int group)
	{
		StreamManager* manager = gStreamManager;
		if (manager->groupPackages[group] != 0 && manager->groupPackages[group]->instance != 0)
		{
			return 0;
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x1082BFD0
	content::LoadInventory* StreamManager::GetGroupInventory(int group)
	{
		StreamManager* manager = gStreamManager;
		if (manager->groupPackages[group] != 0)
		{
			return manager->groupPackages[group]->GetInventory();
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1082BFF0
	StreamPackage* StreamManager::GetGroupPackage(int group)
	{
		return gStreamManager->groupPackages[group];
	}

	// FUNCTION: ENGINE 0x1082C050
	StreamPackage* StreamManager::GetCurrentPackage()
	{
		return gStreamManager->currentPackage;
	}

	// FUNCTION: ENGINE 0x1082C420
	void StreamManager::LoadStartupPackage(int group, const core::Name<core::CaseSensitiveKey>& newName,
		const container::String* resources, const container::String* prerequisites)
	{
		StreamManager* manager = gStreamManager;
		manager->groupPackages[group] = new (0xC) StreamPackage(gStartupPackageTable[group].name);
		manager->groupPackages[group]->slotGroup = gStartupGroupTable[group].name;
		manager->groupPackages[group]->SetResources(resources->ConstData());
		manager->groupPackages[group]->SetPrerequisites(prerequisites->ConstData());
		if (group == 0)
		{
			manager->groupPackages[0]->tags.FromString("__Persistent__;__NoReload__");
		}
		else
		{
			manager->groupPackages[group]->tags.FromString(gPersistentText);
		}
		manager->groupPackages[group]->Slot3(0);
		manager->groupPackages[group]->ResolvePrerequisites();
		manager->groupPackages[group]->Load(0, 0xFFFF, gNoSlotGroup, false);
		manager->startupNames[group] = newName;
	}

	// FUNCTION: ENGINE 0x1082C510
	void StreamManager::UnloadStartupPackage(int group)
	{
		StreamManager* manager = gStreamManager;
		if (manager->groupPackages[group] != 0)
		{
			manager->groupPackages[group]->instance->SetEvicting(false);
			manager->groupPackages[group]->Unload(0);
			manager->startupNames[group].SetText("");
		}
	}

	// 0x10837470 / 0x108374B0 (gamestate.cpp)
	bool IsGameStateOnTop(int id);
	bool HasPendingStateChange();

	// FUNCTION: ENGINE 0x1082C6D0
	void Unknown1082C6D0()
	{
		StreamManager* manager = gStreamManager;
		StreamPackage** slot = manager->groupPackages;
		for (int i = 3; i != 0; i--)
		{
			StreamPackage* package = *slot;
			if (package != 0 && package->instance == 0)
			{
				delete package;
				*slot = 0;
			}
			slot++;
		}
		int count = manager->activePackages.Size();
		while (count != 0)
		{
			StreamPackage* package = manager->activePackages[count - 1];
			count--;
			if (package->instance->IsLoadingActive())
			{
				package->Update();
			}
		}
		count = manager->activePackages.Size();
		while (count != 0)
		{
			StreamPackage* package = manager->activePackages[count - 1];
			count--;
			if ((int)manager->transitionPriority >= (int)package->instance->GetPriority() || !IsGameStateOnTop(2)
				|| HasPendingStateChange())
			{
				package->Update();
			}
		}
	}

	// FUNCTION: ENGINE 0x1082C7B0
	bool Unknown1082C7B0()
	{
		StreamManager* manager = gStreamManager;
		int count = manager->activePackages.Size();
		while (count != 0)
		{
			count--;
			int state = manager->activePackages[count]->GetState();
			if (state != StreamPackageInstance::STATE_LOADED && state != StreamPackageInstance::STATE_EVICTABLE)
			{
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1082C860
	bool Unknown1082C860(int* found, core::Name<core::CaseSensitiveKey>* name)
	{
		StreamManager* manager = gStreamManager;
		int waiting = 0;
		int count = manager->activePackages.Size();
		while (count != 0)
		{
			count--;
			int state = manager->activePackages[count]->GetState();
			if (state == StreamPackageInstance::STATE_LOADED)
			{
				continue;
			}
			if (state != StreamPackageInstance::STATE_WAIT_FOR_PREREQUISITES)
			{
				return false;
			}
			waiting++;
			if (waiting == 1 && name != 0)
			{
				*name = manager->activePackages[count]->name;
			}
		}
		if (found != 0)
		{
			*found = waiting;
		}
		return waiting != 0;
	}

	// FUNCTION: ENGINE 0x1082C010
	void SetStreamDriver(int index, GameObject* object)
	{
		gStreamManager->streamDrivers[index] = GetHandle(object);
	}

	// FUNCTION: ENGINE 0x1082C040
	int GetStreamDriverCount()
	{
		return gStreamManager->streamDriverCount;
	}

	// FUNCTION: ENGINE 0x1082CED0
	void StreamManager::RegisterClient(StreamClient* client)
	{
		StreamManager* manager = gStreamManager;
		if (client->unknown18)
		{
			manager->flaggedClients.PushBack(client);
		}
		else
		{
			manager->clients.PushBack(client);
		}
	}

	// FUNCTION: ENGINE 0x1082D480
	GameObject* GetStreamDriver(int index)
	{
		return gStreamManager->streamDrivers[index].Get();
	}

	// FUNCTION: ENGINE 0x1082D4C0
	void DestroyStreamDrivers()
	{
		StreamManager* manager = gStreamManager;
		if (manager->streamDrivers != 0)
		{
			for (int i = 0; i < manager->streamDriverCount; i++)
			{
				GameObjectHandle* handle = &manager->streamDrivers[i];
				if (handle->IsValid())
				{
					DeferUpdate(*handle, false);
				}
			}
			delete[] manager->streamDrivers;
			manager->streamDrivers = 0;
			manager->streamDriverCount = 0;
		}
	}

	// FUNCTION: ENGINE 0x1082DC00
	// NONMATCHING: 99.1 %, the vector constructor is given the engine's copy of the handle constructor at 0x1005F820
	// (the one this name maps to is 0x102A8410)
#ifdef NONMATCHING
	void SetStreamDriverCount(int count)
	{
		DestroyStreamDrivers();
		gStreamManager->streamDriverCount = count;
		gStreamManager->streamDrivers = new GameObjectHandle[gStreamManager->streamDriverCount];
	}
#endif

	// FUNCTION: ENGINE 0x1082CF10
	void StreamManager::UnregisterClient(StreamClient* client)
	{
		StreamManager* manager = gStreamManager;
		if (client->unknown18)
		{
			StreamClient** item = manager->flaggedClients.Find(client);
			manager->flaggedClients.Erase(item);
		}
		else
		{
			StreamClient** item = manager->clients.Find(client);
			manager->clients.Erase(item);
		}
		StreamPackage** package = manager->activePackages.Begin();
		if (package != manager->activePackages.End())
		{
			do
			{
				if ((*package)->instance != 0)
				{
					(*package)->instance->RemoveClient(client);
				}
				package++;
			}
			while (package != manager->activePackages.End());
		}
	}

	// FUNCTION: ENGINE 0x1082CFC0
	// NONMATCHING: 87.5 %, the engine takes the count down before it loads the tag set for the call, ours after
#ifdef NONMATCHING
	void StreamManager::FindClients(container::ArrayDynamicStatic<StreamClient*, StreamAllocator>* found,
		const TagSet* tags)
	{
		StreamManager* manager = gStreamManager;
		int count = manager->clients.Size();
		while (count != 0)
		{
			StreamClient* client = manager->clients[count - 1];
			count--;
			if (tags->Intersects(client->tags))
			{
				found->PushBack(client);
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x1082DFF0
	void StreamManager::AddActive(StreamPackage* package)
	{
		gStreamManager->activePackages.InsertSorted(package, ComparePackagePriority);
	}

	// FUNCTION: ENGINE 0x1082D020
	void StreamManager::RemoveActive(StreamPackage* package)
	{
		StreamManager* manager = gStreamManager;
		StreamPackage** item = manager->activePackages.Find(package);
		if (item != 0)
		{
			manager->activePackages.Erase(item);
		}
	}

	// FUNCTION: ENGINE 0x1082C060
	void StreamManager::SetCurrentPackage(StreamPackage* package)
	{
		gStreamManager->currentPackage = package;
	}


	// FUNCTION: ENGINE 0x1082C560
	int StreamManager::GetSlotGroupIndex(const content::ObjectName& name)
	{
		for (int i = 0; i < 3; i++)
		{
			if (gStartupGroupTable[i].name == name)
			{
				return i;
			}
		}
		return 3;
	}

	// FUNCTION: ENGINE 0x1082D080
	void StreamManager::Register(StreamPackage* package)
	{
		gStreamManager->knownPackages.PushBack(package);
	}

	// FUNCTION: ENGINE 0x1082DB20
	void AddTriggerPackages(StreamPackageArray* packages, StreamTrigger* trigger, const TagSet& tags, int count,
		int base)
	{
		packages->end = packages->begin;
		if (count == 0)
		{
			StreamPackage* package = trigger->FindPackage(tags);
			if (package != 0)
			{
				math::Vector centre;
				trigger->boundingBox.GetCentre(&centre);
				package->unknown4C.x = centre.x;
				package->unknown4C.y = centre.y;
				package->unknown4C.z = centre.z;
				packages->PushBack(package);
			}
		}
		StreamTriggerArray* neighbours = trigger->neighbourTriggers;
		if (neighbours != 0)
		{
			int budget = base + count;
			StreamCollect collect;
			collect.packages = packages;
			collect.tags = &tags;
			collect.count = count;
			collect.budget = budget;
			if (budget != 0)
			{
				CollectPackages(&collect, neighbours, 1);
			}
		}
	}

	// The first place in list that holds value, or its end
	template<class A> inline typename A::Element* FindElement(A* list, typename A::Element value)
	{
		typename A::Element* position = list->begin;
		while (position != list->end && *position != value)
		{
			position++;
		}
		return position;
	}

	// Takes the element at position out of list (the ones behind it move down)
	template<class A> inline void EraseElement(A* list, typename A::Element* position)
	{
		typename A::Element* end = list->end;
		typename A::Element* next = position + 1;
		if (next != end)
		{
			typename A::Element* to = position;
			while (next != end)
			{
				*to = *next;
				to++;
				next++;
			}
		}
		list->end--;
	}

	// Takes the first place in list that holds value out of it (the end is read once, before the search)
	template<class A> inline void RemoveElement(A* list, typename A::Element value)
	{
		typename A::Element* position = list->begin;
		typename A::Element* end = list->end;
		while (position != end && *position != value)
		{
			position++;
		}
		typename A::Element* next = position + 1;
		if (next != end)
		{
			typename A::Element* to = position;
			while (next != end)
			{
				*to = *next;
				to++;
				next++;
			}
		}
		list->end--;
	}

	// FUNCTION: ENGINE 0x1082E100
	// EQUIVALENT: register allocation (94.5 %): the engine puts the dropped count in esi and the package in edi, this
	// compiler the other way round, which swaps them in the whole unload loop; the engine also copies the end of the
	// list it searched there into another register. Erase(Find) in the unload loop gives the engine's registers and
	// the copy, but then the zero of the group and of the loop counter are no longer shared and the search loop
	// gets aligned (762 bytes). Which of the two comes out follows whether the unload search reads the list's end in
	// its condition or caches it first; no other spelling of the search gives both. A compiler barrier after any
	// statement of either form, an inline wrapper around Find + Erase, the counter declared outside the loop and the
	// orders of the lists' set-up statements change nothing; the group pointer declared ahead of the two loops gives
	// the Find + Erase form a shared zero but one more frame slot (77 %).
	// The two arrays are made with Create(16) after their declaration; the sizes are compared with > 0 and <= 0
	// (the engine's tests keep the shift's flags). The unload loop reads the list's end once, before its search
	// (RemoveElement); the one after the unload goes through Find and Erase, and Erase reads the end before it steps
	// past the position (that gives the engine's copy of the end); the first package of the group search is a local.
	void UpdateStreamTransition(StreamPackageArray** target, StreamPackageArray** current, bool* active,
		bool restricted)
	{
		StreamPackageArray added;
		StreamPackageArray dropped;
		added.Create(16);
		dropped.Create(16);
		unsigned int targetCount = (*target)->Size();
		unsigned int currentCount = (*current)->Size();
		for (unsigned int i = 0; i < currentCount; i++)
		{
			StreamPackage* package = (**current)[i];
			if (FindElement(*target, package) == (*target)->end)
			{
				dropped.PushBack(package);
			}
		}
		for (unsigned int i = 0; i < targetCount; i++)
		{
			StreamPackage* package = (**target)[i];
			if (FindElement(*current, package) == (*current)->end)
			{
				added.PushBack(package);
			}
		}
		StreamSlotGroup* group = 0;
		if ((*current)->Size() > 0)
		{
			StreamPackage* first = (**current)[0];
			group = StreamManager::FindSlotGroup(first->slotGroup);
		}
		else if ((*target)->Size() > 0)
		{
			StreamPackage* first = (**target)[0];
			group = StreamManager::FindSlotGroup(first->slotGroup);
		}
		unsigned int droppedCount = dropped.Size();
		for (unsigned int i = 0; i < droppedCount; i++)
		{
			StreamPackage* package = dropped[i];
			if (package->IsUnloaded() || package->IsUnloading())
			{
				RemoveElement(*current, package);
			}
		}
		if (group != 0)
		{
			if (restricted)
			{
				if (added.Size() <= 0 || *active)
				{
					if (added.IsEmpty() && *active)
					{
						gStreamManager->transitionPriority = 0xFFFF;
						*active = false;
					}
				}
				else
				{
					gStreamManager->transitionPriority = group->priority;
					*active = true;
				}
			}
			unsigned int loading = group->Unknown1083E950();
			if (added.Size() <= 0 || loading <= 0)
			{
				if (droppedCount > 0 && loading == 0 && !group->Unknown1083E990() && !group->Unknown1083E9E0())
				{
					StreamPackage* package = dropped[droppedCount - 1];
					package->Unload(0, false);
					EraseElement(*current, FindElement(*current, package));
				}
			}
			else
			{
				StreamPackage* package = added[0];
				package->Load(0, 0xFFFF, gNoSlotGroup, false);
				(*current)->PushBack(package);
			}
		}
	}
}

namespace container
{
	template class ArrayDynamic<engine::StreamPackage*, AllocatorCoreStatic<12, 16> >;
	template class ArrayDynamic<engine::StreamTrigger*, AllocatorCoreStatic<12, 16> >;
}

namespace engine
{
	core::Name<core::CaseSensitiveKey> gNoSlotGroup("Undefined_SlotGroup", 0);
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D74C80
// FUNCTION: ENGINE 0x10D8A0A0
