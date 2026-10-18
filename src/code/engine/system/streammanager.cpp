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
	// EQUIVALENT: operand order of the x sum: the engine loads min.x and adds max.x, this compiler loads max.x and adds
	// min.x (98.9 %)
	// Helpers, references, Set and every operand and statement order give the same canonical order.
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
				centre.x = trigger->boundingBox.max.x + trigger->boundingBox.min.x;
				centre.y = trigger->boundingBox.max.y + trigger->boundingBox.min.y;
				centre.z = trigger->boundingBox.max.z + trigger->boundingBox.min.z;
				centre.Scale(0.5f);
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
		typename A::Element* next = position + 1;
		typename A::Element* end = list->end;
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
	// EQUIVALENT: register allocation (45.5 %, 95 % of the instruction lines): the engine keeps the group's zero and
	// the unload loop's counter in one register, the first package of the known array in edx / eax and the end of
	// the list it searches in a copy; this compiler stores the zero as a constant and reloads the end
	// The two arrays are made with Create(16) after their declaration; the sizes are compared with > 0 and <= 0
	// (the engine's tests keep the shift's flags), and the unload loop's erase goes through Find and Erase.
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
			group = StreamManager::FindSlotGroup((**current)[0]->slotGroup);
		}
		else if ((*target)->Size() > 0)
		{
			group = StreamManager::FindSlotGroup((**target)[0]->slotGroup);
		}
		unsigned int droppedCount = dropped.Size();
		for (unsigned int i = 0; i < droppedCount; i++)
		{
			StreamPackage* package = dropped[i];
			if (package->IsUnloaded() || package->IsUnloading())
			{
				EraseElement(*current, FindElement(*current, package));
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
