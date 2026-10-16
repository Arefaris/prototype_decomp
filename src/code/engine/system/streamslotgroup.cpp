// engine::StreamSlotGroup (RTTI name; the cluster 0x1083E6A0 - 0x1083EC50): a group of the slots the stream manager
// puts packages in. No assert path names the unit, so the file name is a guess.
#include <new>

#include "code/container/string.h"
#include "code/core/heap.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/engine/system/enginememory.h"
#include "code/engine/system/streampackage.h"

namespace engine
{
	// FUNCTION: ENGINE 0x1083EC50
	void StreamSlotGroup::Create(int unused, bool immediate)
	{
		{
			core::HeapScope scope(0xC);
			slots = new StreamSlot[slotCount];
		}
		container::StringC<64> text;
		SlotHeapFactory makeHeap = GetSlotHeapFactory();
		core::HeapScope scope(core::GetCurrentHeap());
		if (slotCount > 1 && !shared)
		{
			text.Format("%s StreamSlot", name.GetText());
			if (!immediate)
			{
				heap = AllocateSlotHandle();
				int config[3];
				int unit = GetSlotHeapConfig(config)[0];
				allocator = dynamic_cast<core::IMemoryLinearAllocator*>(CreateTwoWayHeap(heap,
					slotCount * unit + 0x10000, 0, text.buffer, core::GetCurrentHeap(), 2, false,
					-1));
			}
			core::SetCurrentHeap(heap);
		}
		for (unsigned int i = 0; i < slotCount; i++)
		{
			slots[i].index = i;
			slots[i].unknownC = shared;
			text.Format("%s StreamSlot[%d]", name.GetText(), i);
			slots[i].unknownE = immediate;
			if (i > 0)
			{
				if (shared || immediate)
				{
					slots[i].heap = slots[0].heap;
					continue;
				}
			}
			else if (immediate)
			{
				slots[0].heap = heap;
				continue;
			}
			int handle = AllocateSlotHandle();
			makeHeap(handle, this, text.buffer);
			slots[i].heap = handle;
		}
		RegisterSlotGroup(this);
	}
}
