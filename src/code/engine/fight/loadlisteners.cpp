// The list of the fight contexts the load listeners go through, and the loading locks of a context (part of the unit
// 0x105A2440 - 0x105A5F00; the declarations are in streampackage.h and trackfactory.h).
#include "code/core/criticalsection.h"
#include "code/core/heap.h"
#include "code/engine/fight/fightsystem.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/system/streampackage.h"
#include <new>

namespace fight
{
	// 0x105A4EB0 / 0x105A4ED0: let go of a context / take a reference to one and let go of the old one
	void ReleaseRegistry(TrackRegistry*& slot);
	void AssignRegistry(TrackRegistry*& slot, TrackRegistry* value);

	// FUNCTION: ENGINE 0x105A4EB0
	void ReleaseRegistry(TrackRegistry*& slot)
	{
		if (slot != 0)
		{
			slot->Release();
			slot = 0;
		}
	}

	// FUNCTION: ENGINE 0x105A4ED0
	void AssignRegistry(TrackRegistry*& slot, TrackRegistry* value)
	{
		if (value != 0)
		{
			value->AddRef();
		}
		if (slot != 0)
		{
			slot->Release();
		}
		slot = value;
	}

	// FUNCTION: ENGINE 0x105A5500
	void TrackRegistry::SetNext(TrackRegistry* following)
	{
		AssignRegistry(next, following);
	}

	// FUNCTION: ENGINE 0x105A5330
	void TrackRegistry::AddHolder(BranchHolder* holder)
	{
		holder->nextHolder = holders;
		holders = holder;
	}

	// FUNCTION: ENGINE 0x105A5350
	// EQUIVALENT: the engine leaves the loop for the unlinking as soon as the holder is found, ours tests it again after the loop; 81.2 %
	void TrackRegistry::RemoveHolder(BranchHolder* holder)
	{
		BranchHolder** link = &holders;
		if (holders != 0)
		{
			BranchHolder* node;
			do
			{
				node = *link;
				if (node == holder)
				{
					break;
				}
				link = &node->nextHolder;
			}
			while (node->nextHolder != 0);
		}
		if (*link == holder)
		{
			*link = (*link)->nextHolder;
		}
	}

	// FUNCTION: ENGINE 0x105A5260
	void TrackRegistry::ResolveBranchRefs()
	{
		if (branches != 0)
		{
			branches->Slot7();
		}
		for (BranchHolder* holder = holders; holder != 0; holder = holder->nextHolder)
		{
			holder->Resolve(0);
		}
	}

	// FUNCTION: ENGINE 0x105A5240
	void TrackRegistry::MarkChanged()
	{
		changed = true;
	}

	// FUNCTION: ENGINE 0x105A51E0
	void TrackRegistry::BeginLoading(bool exclusive)
	{
		if (lockCount == 0)
		{
			sharedCount = 0;
			exclusiveCount = 0;
			changed = false;
		}
		lockCount = lockCount + 1;
		if (exclusive)
		{
			sharedCount = sharedCount + 1;
			if (sharedCount == 1)
			{
				core::CriticalSectionEnter(lockA);
			}
		}
		else
		{
			exclusiveCount = exclusiveCount + 1;
		}
	}

	// FUNCTION: ENGINE 0x105A5460
	void TrackRegistry::Unlock(bool exclusive)
	{
		if (exclusive)
		{
			core::CriticalSectionLeave(lockA);
		}
	}

	// FUNCTION: ENGINE 0x105A5520
	void TrackRegistry::EndLoading(bool exclusive)
	{
		lockCount = lockCount - 1;
		if (lockCount == 0)
		{
			if (sharedCount > 0)
			{
				core::CriticalSectionLeave(lockA);
			}
			changed = false;
		}
	}

	// FUNCTION: ENGINE 0x105A52A0
	void TrackRegistry::AddPending(PendingItem* item)
	{
		core::CriticalSectionEnter(lockB);
		PendingItem** link = &pending;
		if (*link != 0)
		{
			do
			{
				link = &(*link)->next;
			}
			while (*link != 0);
		}
		*link = item;
		core::CriticalSectionLeave(lockB);
	}

	// FUNCTION: ENGINE 0x105A52E0
	void TrackRegistry::RemovePending(PendingItem* item, int unused)
	{
		core::CriticalSectionEnter(lockB);
		PendingItem** link = &pending;
		if (*link != 0)
		{
			PendingItem* node;
			do
			{
				node = *link;
				if (node == item)
				{
					break;
				}
				link = &node->next;
			}
			while (node->next != 0);
			if (*link != 0)
			{
				*link = (*link)->next;
			}
		}
		core::CriticalSectionLeave(lockB);
	}
}

namespace engine
{
	// FUNCTION: ENGINE 0x105A4AA0
	LoadListeners::LoadListeners()
		: first(0)
	{
		core::CriticalSectionInit(lock);
	}

	// FUNCTION: ENGINE 0x105A4F00
	LoadListeners::~LoadListeners()
	{
		fight::ReleaseRegistry(first);
		core::CriticalSectionDelete(lock);
	}

	// FUNCTION: ENGINE 0x105A4AC0
	LoadListeners* CreateLoadListeners()
	{
		int heap = core::SetCurrentHeap(fight::GetHeapId(0));
		gLoadListeners = new LoadListeners;
		LoadListeners* listeners = gLoadListeners;
		core::SetCurrentHeap(heap);
		return listeners;
	}

	// FUNCTION: ENGINE 0x105A50B0
	void DestroyLoadListeners()
	{
		delete gLoadListeners;
		gLoadListeners = 0;
	}

	// FUNCTION: ENGINE 0x105A4B00
	int LoadListeners::GetCount()
	{
		int count = 0;
		for (fight::TrackRegistry* context = first; context != 0; context = context->next)
		{
			count = count + 1;
		}
		return count;
	}

	// FUNCTION: ENGINE 0x105A4B20
	fight::TrackRegistry* LoadListeners::GetContextConst(int index) const
	{
		int current = 0;
		fight::TrackRegistry* context = first;
		if (context != 0)
		{
			do
			{
				if (index < current)
				{
					break;
				}
				if (index == current)
				{
					return context;
				}
				context = context->next;
				current = current + 1;
			}
			while (context != 0);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105A4B50
	fight::TrackRegistry* LoadListeners::GetContext(int index)
	{
		int current = 0;
		fight::TrackRegistry* context = first;
		if (context != 0)
		{
			do
			{
				if (index < current)
				{
					break;
				}
				if (index == current)
				{
					return context;
				}
				context = context->next;
				current = current + 1;
			}
			while (context != 0);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105A4B80
	int LoadListeners::IndexOfContext(fight::TrackRegistry* context)
	{
		if (context != 0)
		{
			fight::TrackRegistry* node = first;
			int position = 0;
			if (node != 0)
			{
				do
				{
					if (context == node)
					{
						return position;
					}
					node = node->next;
					position = position + 1;
				}
				while (node != 0);
			}
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x105A4BB0
	void LoadListeners::Begin(bool exclusive)
	{
		fight::TrackRegistry* context = first;
		if (context != 0)
		{
			do
			{
				context->BeginLoading(exclusive);
				context = context->next;
			}
			while (context != 0);
		}
	}

	// FUNCTION: ENGINE 0x105A4BE0
	void LoadListeners::End(bool exclusive)
	{
		fight::TrackRegistry* context = first;
		if (context != 0)
		{
			do
			{
				context->EndLoading(exclusive);
				context = context->next;
			}
			while (context != 0);
		}
	}

	// FUNCTION: ENGINE 0x105A4F40
	void LoadListeners::AddContext(fight::TrackRegistry* context)
	{
		if (context != 0)
		{
			fight::TrackRegistry* last = 0;
			fight::TrackRegistry* node = first;
			while (node != 0)
			{
				last = node;
				node = node->next;
			}
			context->SetNext(node);
			if (last != 0)
			{
				last->SetNext(context);
			}
			else
			{
				fight::AssignRegistry(first, context);
			}
		}
	}

	// FUNCTION: ENGINE 0x105A4F90
	fight::TrackRegistry* LoadListeners::FindContext(const core::Name<core::CaseSensitiveKey>& name)
	{
		for (fight::TrackRegistry* context = first; context != 0; context = context->next)
		{
			if (context->name == name)
			{
				return context;
			}
		}
		return 0;
	}
}

