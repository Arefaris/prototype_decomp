// The stream manager's unit: see the header. The file name and the names are guesses.
#include "code/engine/system/streammanager.h"

#include "code/core/heap.h"
#include "code/engine/system/streampackage.h"
#include "code/engine/system/streamtrigger.h"
#include "code/engine/system/tagset.h"
#include "code/math/vector.h"

namespace engine
{
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
