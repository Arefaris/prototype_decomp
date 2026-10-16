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

	// A list of up to 16 packages, in a block of the aligned heap (empty when there is none); the transition builds two
	// of them. They are plain data and the helpers are forced inline: the engine's copy of the transition has the
	// container's code inline in every place.
	struct PackageSet
	{
		StreamPackage** begin;
		StreamPackage** end;
		StreamPackage** capacity;
	};

	__forceinline void Create(PackageSet* set)
	{
		StreamPackage** block = (StreamPackage**)core::HeapAllocAligned(12, 0x40, 16);
		set->begin = block;
		if (block != 0)
		{
			set->end = block;
			set->capacity = block + 16;
		}
		else
		{
			set->end = 0;
			set->capacity = 0;
		}
	}

	__forceinline void Append(StreamPackageArray* list, StreamPackage* value)
	{
		if (list->end < list->capacity)
		{
			StreamPackage** position = list->end;
			list->end = position + 1;
			if (position != 0)
			{
				*position = value;
			}
		}
	}

	__forceinline void Append(PackageSet* set, StreamPackage* value)
	{
		if (set->end < set->capacity)
		{
			StreamPackage** position = set->end;
			set->end = position + 1;
			if (position != 0)
			{
				*position = value;
			}
		}
	}

	// Takes the first of value out of a list (nothing when it is not there)
	__forceinline void RemovePackage(StreamPackageArray* list, StreamPackage* value)
	{
		StreamPackage** position = list->begin;
		while (position != list->end && *position != value)
		{
			position++;
		}
		StreamPackage** next = position + 1;
		StreamPackage** end = list->end;
		if (next != end)
		{
			StreamPackage** to = position;
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
	// EQUIVALENT: register allocation (21.2 %): the engine keeps the target's count in ebp and the current's in esi,
	// this compiler the other way round; every comparison, call and store is the same
	void UpdateStreamTransition(StreamPackageArray** target, StreamPackageArray** current, bool* active,
		bool restricted)
	{
		PackageSet added;
		PackageSet dropped;
		Create(&added);
		Create(&dropped);
		unsigned int targetCount = (*target)->end - (*target)->begin;
		unsigned int currentCount = (*current)->end - (*current)->begin;
		for (unsigned int i = 0; i < currentCount; i++)
		{
			StreamPackage* package = (*current)->begin[i];
			StreamPackage** found = (*target)->begin;
			while (found != (*target)->end && *found != package)
			{
				found++;
			}
			if (found == (*target)->end)
			{
				Append(&dropped, package);
			}
		}
		for (unsigned int i = 0; i < targetCount; i++)
		{
			StreamPackage* package = (*target)->begin[i];
			StreamPackage** found = (*current)->begin;
			while (found != (*current)->end && *found != package)
			{
				found++;
			}
			if (found == (*current)->end)
			{
				Append(&added, package);
			}
		}
		StreamSlotGroup* group = 0;
		StreamPackageArray* known = *current;
		if (known->end != known->begin || (known = *target)->end != known->begin)
		{
			group = StreamManager::FindSlotGroup(known->begin[0]->slotGroup);
		}
		unsigned int droppedCount = dropped.end - dropped.begin;
		for (unsigned int i = 0; i < droppedCount; i++)
		{
			StreamPackage* package = dropped.begin[i];
			if (package->IsUnloaded() || package->IsUnloading())
			{
				RemovePackage(*current, package);
			}
		}
		if (group != 0)
		{
			unsigned int addedCount = added.end - added.begin;
			if (restricted)
			{
				if (addedCount == 0 || *active)
				{
					if (added.begin == added.end && *active)
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
			if (addedCount == 0 || loading == 0)
			{
				if (droppedCount != 0 && loading == 0 && !group->Unknown1083E990() && !group->Unknown1083E9E0())
				{
					StreamPackage* package = dropped.begin[droppedCount - 1];
					package->Unload(0, false);
					RemovePackage(*current, package);
				}
			}
			else
			{
				StreamPackage* package = added.begin[0];
				package->Load(0, 0xFFFF, gNoSlotGroup, false);
				Append(*current, package);
			}
		}
		if (dropped.begin != 0)
		{
			core::HeapFreeAligned(12, dropped.begin);
		}
		if (added.begin != 0)
		{
			core::HeapFreeAligned(12, added.begin);
		}
	}
}
