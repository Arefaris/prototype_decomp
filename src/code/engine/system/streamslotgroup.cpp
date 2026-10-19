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

namespace engine
{
	// FUNCTION: ENGINE 0x1083E670
	int __fastcall GetHeapUsed(int heap)
	{
		int used = 0;
		GetHeapStats(heap, 0, 0, 0, &used, 0);
		return used;
	}

	// FUNCTION: ENGINE 0x1083E6C0
	StreamSlot::~StreamSlot()
	{
		if (heap != -1 && !unknownE && (index == 0 || !unknownC))
		{
			FreeSlotHandle(heap);
			DestroyHeap(heap);
		}
	}

	// FUNCTION: ENGINE 0x1083E6F0
	int StreamSlot::GetState() const
	{
		if (package != 0)
		{
			return package->GetState();
		}
		return 9;
	}

	// FUNCTION: ENGINE 0x1083E710
	bool StreamSlot::IsHeapEmpty() const
	{
		int used = 0;
		GetHeapStats(heap, 0, 0, 0, &used, 0);
		return used == 0;
	}

	// FUNCTION: ENGINE 0x1083E740
	StreamPackage* StreamSlot::GetPackage() const
	{
		return package;
	}

	// FUNCTION: ENGINE 0x1083E750
	StreamPackage* StreamSlot::GetPackage2() const
	{
		return package;
	}

	// FUNCTION: ENGINE 0x1083E760
	bool StreamSlot::Attach(StreamPackage* newPackage)
	{
		if (GetState() == 8)
		{
			package->instance->SetEvicting(false);
		}
		if (package == 0)
		{
			package = newPackage;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1083E7A0
	void StreamSlot::Detach()
	{
		if (package != 0)
		{
			if (!unknownC)
			{
				IsHeapEmpty();
			}
			package = 0;
		}
	}

	// FUNCTION: ENGINE 0x1083E7D0
	bool StreamSlot::GetUnknownD() const
	{
		return unknownD;
	}

	// FUNCTION: ENGINE 0x1083E6A0
	StreamSlot::StreamSlot()
	{
		heap = -1;
		package = 0;
		unknownC = false;
		unknownD = true;
		unknownE = false;
	}
}

namespace engine
{
	// FUNCTION: ENGINE 0x1083E7C0
	void StreamSlotGroup::SetSlotCount(unsigned int count)
	{
		slotCount = count;
	}

	// The default function that destroys the heap of a slot
	// FUNCTION: ENGINE 0x1083E820
	static void DestroySlotHeap(int handle)
	{
		core::IMemoryAllocator* allocator = core::GetHeapAllocator(handle);
		if (handle != 0)
		{
			allocator->Release();
		}
	}

	// FUNCTION: ENGINE 0x1083E840
	SlotHeapDestroyer StreamSlotGroup::GetSlotHeapDestroyer() const
	{
		SlotHeapDestroyer function = destroyer;
		if (function == 0)
		{
			function = gStreamManager->slotHeapDestroyer;
			if (function == 0)
			{
				function = DestroySlotHeap;
			}
		}
		return function;
	}

	// FUNCTION: ENGINE 0x1083E860
	void StreamSlotGroup::SetSlotHeapConfig(const SlotHeapConfig* newConfig)
	{
		unknown1C = newConfig->flag;
		slotWin32Bytes = newConfig->size;
		slotWin32KiloBytes = 0;
		slotWin32MegaBytes = 0;
		unknown54 = newConfig->alignment;
	}

	// FUNCTION: ENGINE 0x1083E880
	// EQUIVALENT: the engine stores the size after loading the alignment, ours before (86 %)
	int* StreamSlotGroup::GetSlotHeapConfig(int* out) const
	{
		*(bool*)(out + 1) = unknown1C;
		*out = (slotWin32MegaBytes * 0x400 + slotWin32KiloBytes) * 0x400 + slotWin32Bytes;
		out[2] = unknown54;
		return out;
	}

	// FUNCTION: ENGINE 0x1083E8B0
	int* StreamSlotGroup::GetGroupHeapConfig(int* out) const
	{
		GetSlotHeapConfig(out);
		unsigned int count = shared ? slotCount : 1;
		*out = *out * count;
		return out;
	}

	// FUNCTION: ENGINE 0x1083E8F0
	StreamSlot* StreamSlotGroup::FindFreeSlot() const
	{
		unsigned int free = 0;
		StreamSlot* waiting = 0;
		for (unsigned int i = 0; i < slotCount; i++)
		{
			int state = slots[i].GetState();
			if (state == 9)
			{
				if (slots[i].unknownD)
				{
					return slots + i;
				}
			}
			else if (state == 8 && slots[i].unknownD)
			{
				waiting = slots + i;
			}
		}
		return waiting;
	}

	// FUNCTION: ENGINE 0x1083E950
	unsigned int StreamSlotGroup::Unknown1083E950() const
	{
		unsigned int count = 0;
		for (unsigned int i = 0; i < slotCount; i++)
		{
			int state = slots[i].GetState();
			if (slots[i].unknownD && state == 9)
			{
				count++;
			}
		}
		return count;
	}

	// FUNCTION: ENGINE 0x1083E990
	// EQUIVALENT: the engine addresses the slot as [offset + slots], ours as [slots + offset]; nothing else differs (97 %)
	bool StreamSlotGroup::Unknown1083E990() const
	{
		for (unsigned int i = 0; i < slotCount; i++)
		{
			if ((i + slots)->unknownD)
			{
				StreamPackage* package = (i + slots)->GetPackage();
				if (package != 0 && package->IsLoading())
				{
					return true;
				}
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1083E9E0
	// EQUIVALENT: the engine addresses the slot as [offset + slots], ours as [slots + offset]; nothing else differs (97 %)
	bool StreamSlotGroup::Unknown1083E9E0() const
	{
		for (unsigned int i = 0; i < slotCount; i++)
		{
			if ((i + slots)->unknownD)
			{
				StreamPackage* package = (i + slots)->GetPackage();
				if (package != 0 && package->IsUnloading())
				{
					return true;
				}
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1083EA40
	// EQUIVALENT: the engine stores the reference count of the base before it computes the name's address, ours after (94 %)
	StreamSlotGroup::StreamSlotGroup(const core::Name<core::CaseSensitiveKey>& newName) : name(newName)
	{
		unknown1C = true;
		unknown67 = true;
		unknown68 = true;
		slots = 0;
		allocator = 0;
		slotCount = 0;
		slotWin32Bytes = 0;
		slotWin32KiloBytes = 0;
		slotWin32MegaBytes = 0;
		slotXenonBytes = 0;
		slotXenonKiloBytes = 0;
		slotXenonMegaBytes = 0;
		slotPS3CPUBytes = 0;
		slotPS3CPUKiloBytes = 0;
		slotPS3CPUMegaBytes = 0;
		slotPS3GPUBytes = 0;
		slotPS3GPUKiloBytes = 0;
		slotPS3GPUMegaBytes = 0;
		unknown54 = 0;
		factory = 0;
		destroyer = 0;
		shared = false;
		heap = -1;
		priority = 0x7FFF;
	}

	// FUNCTION: ENGINE 0x1083EAC0
	void StreamSlotGroup::SetName(const content::ObjectName& newName)
	{
		name = newName;
	}

	// FUNCTION: ENGINE 0x1083EAD0
	// EQUIVALENT: the engine stores the reference count of the base before it computes the name's address; the argument loads are ordered differently (80 %)
	StreamSlotGroup::StreamSlotGroup(const core::Name<core::CaseSensitiveKey>& newName, unsigned int count,
		const SlotHeapConfig* config, bool newShared, bool newUnknown67) : name(newName)
	{
		slotCount = count;
		shared = newShared;
		unknown67 = newUnknown67;
		slots = 0;
		heap = -1;
		allocator = 0;
		unknown1C = true;
		slotWin32Bytes = 0;
		slotWin32KiloBytes = 0;
		slotWin32MegaBytes = 0;
		slotXenonBytes = 0;
		slotXenonKiloBytes = 0;
		slotXenonMegaBytes = 0;
		slotPS3CPUBytes = 0;
		slotPS3CPUKiloBytes = 0;
		slotPS3CPUMegaBytes = 0;
		slotPS3GPUBytes = 0;
		slotPS3GPUKiloBytes = 0;
		slotPS3GPUMegaBytes = 0;
		unknown54 = 0;
		factory = 0;
		destroyer = 0;
		priority = 0x7FFF;
		unknown68 = true;
		SetSlotHeapConfig(config);
	}

	// FUNCTION: ENGINE 0x1083EB70
	StreamSlotGroup::~StreamSlotGroup()
	{
	}

	// The default function that makes the heap of a slot
	// FUNCTION: ENGINE 0x1083EB80
	static core::IMemoryAllocator* MakeSlotHeap(int handle, StreamSlotGroup* group, const char* name)
	{
		int config[3];
		group->GetSlotHeapConfig(config);
		return CreateHeap(handle, config[0], 0, name, 0xC, 2, false, -1, 0);
	}

	// FUNCTION: ENGINE 0x1083EE40
	// EQUIVALENT: the engine keeps the flag in cl for the final tests and the result, ours tests it in memory (41 %)
	bool StreamSlotGroup::IsReady()
	{
		UnregisterSlotGroup(this);
		char ready = 1;
		for (unsigned int i = 0; i < slotCount; i++)
		{
			if (slots != 0 && slots[i].package != 0 && !slots[i].package->IsReady())
			{
				ready = 0;
			}
		}
		if (slots != 0)
		{
			if (!ready)
			{
				return ready;
			}
			delete[] slots;
			slots = 0;
		}
		if (ready && heap != -1)
		{
			DestroyHeap(heap);
			FreeSlotHandle(heap);
			heap = -1;
			return ready;
		}
		return ready;
	}

	// FUNCTION: ENGINE 0x1083F5E0
	// EQUIVALENT: the engine stores the reference count of the base before it computes the name's address, ours after (95 %)
	StreamSlotGroup::StreamSlotGroup()
	{
		unknown1C = true;
		unknown67 = true;
		unknown68 = true;
		slots = 0;
		allocator = 0;
		slotCount = 0;
		slotWin32Bytes = 0;
		slotWin32KiloBytes = 0;
		slotWin32MegaBytes = 0;
		slotXenonBytes = 0;
		slotXenonKiloBytes = 0;
		slotXenonMegaBytes = 0;
		slotPS3CPUBytes = 0;
		slotPS3CPUKiloBytes = 0;
		slotPS3CPUMegaBytes = 0;
		slotPS3GPUBytes = 0;
		slotPS3GPUKiloBytes = 0;
		slotPS3GPUMegaBytes = 0;
		unknown54 = 0;
		factory = 0;
		destroyer = 0;
		shared = false;
		heap = -1;
		priority = 0x7FFF;
	}

	// FUNCTION: ENGINE 0x1083F680
	// EQUIVALENT: the engine reuses the argument slots for the heap scopes and the factory, ours puts the factory in the frame (96 %)
	void StreamSlotGroup::Reconfigure(unsigned int count, const SlotHeapConfig* newConfig)
	{
		for (unsigned int i = 0; i < slotCount; i++)
		{
			if (slots[i].package != 0)
			{
				slots[i].package->IsReady();
			}
		}
		delete[] slots;
		slots = 0;
		allocator->Reset();
		slotCount = count;
		SetSlotHeapConfig(newConfig);
		{
			core::HeapScope scope(0xC);
			slots = new StreamSlot[slotCount];
		}
		container::StringC<64> text;
		SlotHeapFactory makeHeap = GetSlotHeapFactory();
		core::HeapScope scope(heap);
		for (unsigned int i = 0; i < slotCount; i++)
		{
			slots[i].index = i;
			slots[i].unknownC = shared;
			text.Format("%s StreamSlot[%d]", name.GetText(), i);
			if (i == 0 || !shared)
			{
				int handle = AllocateSlotHandle();
				makeHeap(handle, this, text.buffer);
				slots[i].heap = handle;
			}
			else
			{
				slots[i].heap = slots[0].heap;
			}
		}
	}
}

namespace engine
{
	// FUNCTION: ENGINE 0x1083E7E0
	content::ClassInfo* StreamSlotGroup::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::StreamSlotGroup";
		sInfo.code = "pnr";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1083EC30
	SlotHeapFactory StreamSlotGroup::GetSlotHeapFactory() const
	{
		SlotHeapFactory function = factory;
		if (function == 0)
		{
			function = gStreamManager->slotHeapFactory;
			if (function == 0)
			{
				function = MakeSlotHeap;
			}
		}
		return function;
	}

#define ENGINE_SLOT_MEMBER(type, id, member) \
	{ content::GetMemberPrimitiveMetaType<StreamSlotGroup, type, id>("pnr"), \
		content::MemberOffset(&((StreamSlotGroup*)0)->member, (int)&((StreamSlotGroup*)0)->member), #member }

	// FUNCTION: ENGINE 0x1083F310
	content::MemberList* StreamSlotGroup::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			ENGINE_SLOT_MEMBER(unsigned int, 0, slotCount),
			ENGINE_SLOT_MEMBER(unsigned int, 1, slotXenonBytes),
			ENGINE_SLOT_MEMBER(unsigned int, 2, slotXenonKiloBytes),
			ENGINE_SLOT_MEMBER(unsigned int, 3, slotXenonMegaBytes),
			ENGINE_SLOT_MEMBER(unsigned int, 4, slotWin32Bytes),
			ENGINE_SLOT_MEMBER(unsigned int, 5, slotWin32KiloBytes),
			ENGINE_SLOT_MEMBER(unsigned int, 6, slotWin32MegaBytes),
			ENGINE_SLOT_MEMBER(unsigned int, 7, slotPS3CPUBytes),
			ENGINE_SLOT_MEMBER(unsigned int, 8, slotPS3CPUKiloBytes),
			ENGINE_SLOT_MEMBER(unsigned int, 9, slotPS3CPUMegaBytes),
			ENGINE_SLOT_MEMBER(unsigned int, 10, slotPS3GPUBytes),
			ENGINE_SLOT_MEMBER(unsigned int, 11, slotPS3GPUKiloBytes),
			ENGINE_SLOT_MEMBER(unsigned int, 12, slotPS3GPUMegaBytes),
			{ content::GetMemberPrimitiveMetaType<StreamSlotGroup, unsigned short, 13>("pnr"),
				content::MemberOffset(&((StreamSlotGroup*)0)->priority, (int)&((StreamSlotGroup*)0)->priority),
				"loadPriority" },
			ENGINE_SLOT_MEMBER(bool, 14, shared),
			{ content::GetMemberPrimitiveMetaType<StreamSlotGroup, bool, 15>("pnr"),
				content::MemberOffset(&((StreamSlotGroup*)0)->unknown67, (int)&((StreamSlotGroup*)0)->unknown67),
				"published" }
		};
		sList.members = sMembers;
		sList.count = 16;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1083EBC0
// FUNCTION: ENGINE 0x1083EF10
// FUNCTION: ENGINE 0x1083EF50
// FUNCTION: ENGINE 0x1083EF90
// FUNCTION: ENGINE 0x1083EFD0
// FUNCTION: ENGINE 0x1083F010
// FUNCTION: ENGINE 0x1083F050
// FUNCTION: ENGINE 0x1083F090
// FUNCTION: ENGINE 0x1083F0D0
// FUNCTION: ENGINE 0x1083F110
// FUNCTION: ENGINE 0x1083F150
// FUNCTION: ENGINE 0x1083F190
// FUNCTION: ENGINE 0x1083F1D0
// FUNCTION: ENGINE 0x1083F210
// FUNCTION: ENGINE 0x1083F250
// FUNCTION: ENGINE 0x1083F290
// FUNCTION: ENGINE 0x1083F2D0
// FUNCTION: ENGINE 0x1083F660
