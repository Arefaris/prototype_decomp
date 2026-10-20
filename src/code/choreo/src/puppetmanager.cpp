// The registry of the puppets (the unit 0x10955580 - 0x10955C00, and the tasks of the update from 0x10958D80; file
// name and all names guessed). Handles lead to puppets through a table of slots; the puppets that are updated every
// frame sit in a list, in batches the tasks work on.
#include "code/choreo/puppetmanager.h"

namespace choreo
{
	void* gPuppetWaiter;
	int gPuppetGeneration;
	bool gPuppetsUpdating;
	SlotArray<PuppetSlot> gPuppetSlots;
	SlotStack gPuppetFreeSlots;
	PuppetList gPuppetList;
	unsigned char gPuppetResultLock[0x18];
	unsigned char gPuppetBufferLock[0x18];
	unsigned char gPuppetEvent[8];
	int gPuppetTaskFunction;
	core::AsyncTaskGroup gPuppetTaskGroup;
	core::AsyncTaskNode gPuppetTaskNodes[MAX_PUPPET_JOBS];
	PoseBlendJob gPuppetJobs[MAX_PUPPET_JOBS];
	unsigned int gPuppetBatchSize = 1;
	bool gPuppetsThreaded = true;

	template<class T>
	T* FillCopies(T* dest, unsigned int count, const T& value)
	{
		while (count != 0)
		{
			count--;
			if (dest != 0)
			{
				new (dest) T(value);
			}
			dest++;
		}
		return dest;
	}

	template<class T>
	bool SlotArray<T>::Create(unsigned int count, const T& value)
	{
		if (begin != 0)
		{
			return false;
		}
		if (count > 0)
		{
			begin = (T*)operator new[](count * sizeof(T));
			if (begin != 0)
			{
				end = begin + count;
				FillCopies(begin, count, value);
				return true;
			}
		}
		begin = 0;
		end = 0;
		return false;
	}

	// FUNCTION: ENGINE 0x10955890
	bool PuppetList::Allocate(unsigned int count)
	{
		if (count != 0)
		{
			begin = (Puppet**)core::HeapAllocAligned(core::GetCurrentHeap(), count * sizeof(Puppet*), 16);
			if (begin != 0)
			{
				capacity = begin + count;
				end = begin;
				return true;
			}
		}
		else
		{
			begin = 0;
		}
		end = 0;
		capacity = 0;
		return false;
	}

	// FUNCTION: ENGINE 0x10955AA0
	bool PuppetList::Reserve(unsigned int count)
	{
		return Allocate(count);
	}

	// FUNCTION: ENGINE 0x109555A0
	PuppetHandle::PuppetHandle()
	{
		mIndex = -1;
		mGeneration = 0;
	}

	// FUNCTION: ENGINE 0x10955590
	PuppetManagerSettings::PuppetManagerSettings()
	{
		mCapacity = 0x400;
		mBatchSize = 4;
	}

	// FUNCTION: ENGINE 0x10955790
	bool PuppetHandle::IsValid() const
	{
		return (unsigned int)mIndex < gPuppetSlots.Size() && gPuppetSlots.begin[mIndex].mPuppet != 0 &&
			mGeneration == gPuppetSlots.begin[mIndex].mGeneration;
	}

	// FUNCTION: ENGINE 0x109557D0
	Puppet* PuppetHandle::Get()
	{
		return gPuppetSlots.begin[mIndex].mPuppet;
	}

	// FUNCTION: ENGINE 0x109557E0
	Puppet* PuppetHandle::Get() const
	{
		return gPuppetSlots.begin[mIndex].mPuppet;
	}

	// FUNCTION: ENGINE 0x109555B0
	bool GetPuppetsThreaded()
	{
		return gPuppetsThreaded;
	}

	// FUNCTION: ENGINE 0x109555C0
	void SetPuppetsThreaded(bool threaded)
	{
		gPuppetsThreaded = threaded;
	}

	// FUNCTION: ENGINE 0x109555D0
	void TogglePuppetsThreaded()
	{
		gPuppetsThreaded = !gPuppetsThreaded;
	}

	// FUNCTION: ENGINE 0x109555E0
	void SetPuppetWaiter(void* waiter)
	{
		gPuppetWaiter = waiter;
	}

	// FUNCTION: ENGINE 0x109557F0
	void UpdatePuppetManager(float dt)
	{
		if (gPuppetList.begin != gPuppetList.end)
		{
			gPuppetsUpdating = true;
			RunPuppetJobs(dt, gPuppetList.begin, gPuppetList.end, gPuppetWaiter);
			gPuppetsUpdating = false;
		}
	}

	// FUNCTION: ENGINE 0x10955940
	PuppetHandle CreatePuppetHandle(Puppet* puppet)
	{
		unsigned int* last = gPuppetFreeSlots.end - 1;
		unsigned int index = *last;
		if (gPuppetFreeSlots.begin != gPuppetFreeSlots.end)
		{
			gPuppetFreeSlots.end = last;
		}
		PuppetHandle handle;
		handle.mIndex = index;
		gPuppetSlots.begin[index].mPuppet = puppet;
		int generation = gPuppetGeneration;
		gPuppetSlots.begin[index].mGeneration = generation;
		handle.mGeneration = generation;
		gPuppetGeneration = generation + 1;
		puppet->AddRef();
		gPuppetList.PushBack(puppet);
		return handle;
	}

	// FUNCTION: ENGINE 0x109559C0
	void DestroyPuppetHandle(PuppetHandle handle)
	{
		unsigned int index = handle.mIndex;
		Puppet* puppet = gPuppetSlots.begin[index].mPuppet;
		gPuppetSlots.begin[index].mPuppet = 0;
		gPuppetList.Erase(gPuppetList.Find(puppet));
		puppet->Release();
		gPuppetFreeSlots.PushBack(index);
	}

	// FUNCTION: ENGINE 0x10955B50
	void ShutdownPuppetManager()
	{
		StopPuppetJobs();
		gPuppetSlots.Free();
		gPuppetList.Free();
		gPuppetFreeSlots.Free();
	}

	// FUNCTION: ENGINE 0x10955C00
	void InitializePuppetManager(const PuppetManagerSettings* settings)
	{
		PuppetSlot empty;
		empty.mPuppet = 0;
		empty.mGeneration = 0;
		gPuppetSlots.Create(settings->mCapacity, empty);
		gPuppetList.Allocate(settings->mCapacity);
		gPuppetFreeSlots.Allocate(settings->mCapacity);
		for (unsigned int i = 0; i < settings->mCapacity; i++)
		{
			unsigned int slot = settings->mCapacity - i - 1;
			gPuppetFreeSlots.PushBack(slot);
		}
		StartPuppetJobs(settings);
	}

	// The members of the containers that the engine keeps as functions of their own
	// FUNCTION: ENGINE 0x10955620 ; choreo::SlotArray<structchoreo::PuppetSlot>::Size
	unsigned int (SlotArray<PuppetSlot>::*gKeepSlotArraySize)() const = &SlotArray<PuppetSlot>::Size;

	// FUNCTION: ENGINE 0x10955630 ; choreo::SlotArray<structchoreo::PuppetSlot>::At
	PuppetSlot* (SlotArray<PuppetSlot>::*gKeepSlotArrayAt)(int) = &SlotArray<PuppetSlot>::At;

	// FUNCTION: ENGINE 0x10955640 ; choreo::SlotArray<structchoreo::PuppetSlot>::Begin
	PuppetSlot* (SlotArray<PuppetSlot>::*gKeepSlotArrayBegin)() = &SlotArray<PuppetSlot>::Begin;

	// FUNCTION: ENGINE 0x10955650 ; choreo::SlotArray<structchoreo::PuppetSlot>::End
	PuppetSlot* (SlotArray<PuppetSlot>::*gKeepSlotArrayEnd)() = &SlotArray<PuppetSlot>::End;

	// FUNCTION: ENGINE 0x10955660 ; choreo::SlotArray<structchoreo::PuppetSlot>::IsEmpty
	bool (SlotArray<PuppetSlot>::*gKeepSlotArrayIsEmpty)() const = &SlotArray<PuppetSlot>::IsEmpty;

	// FUNCTION: ENGINE 0x109556B0 ; choreo::SlotArray<structchoreo::PuppetSlot>::Allocate
	bool (SlotArray<PuppetSlot>::*gKeepSlotArrayAllocate)(unsigned int) = &SlotArray<PuppetSlot>::Allocate;

	// FUNCTION: ENGINE 0x10955AE0 ; choreo::SlotArray<structchoreo::PuppetSlot>::Create
	bool (SlotArray<PuppetSlot>::*gKeepSlotArrayCreate)(unsigned int, const PuppetSlot&) = &SlotArray<PuppetSlot>::Create;

	// FUNCTION: ENGINE 0x10955830 ; choreo::SlotStack::PushBack
	bool (SlotStack::*gKeepSlotStackPushBack)(const unsigned int&) = &SlotStack::PushBack;

	// FUNCTION: ENGINE 0x10955860 ; choreo::SlotStack::Erase
	// EQUIVALENT: the same loop; the engine keeps the position, the delta to it and the element in three registers of
	// its own (17.9 %)
	void (SlotStack::*gKeepSlotStackErase)(unsigned int*) = &SlotStack::Erase;

	// FUNCTION: ENGINE 0x10955B40 ; choreo::SlotStack::Clear
	void (SlotStack::*gKeepSlotStackClear)() = &SlotStack::Clear;

	// FUNCTION: ENGINE 0x10955AB0 ; choreo::PuppetList::Free
	void (PuppetList::*gKeepPuppetListFree)() = &PuppetList::Free;

	// FUNCTION: ENGINE 0x10955670 ; choreo::PuppetList::Find
	Puppet** (PuppetList::*gKeepPuppetListFind)(Puppet* const&) = &PuppetList::Find;

	// FUNCTION: ENGINE 0x10955910 ; choreo::FillCopies<structchoreo::PuppetSlot>
	PuppetSlot* (*gKeepFillCopies)(PuppetSlot*, unsigned int, const PuppetSlot&) = &FillCopies<PuppetSlot>;

	// FUNCTION: ENGINE 0x10955770 ; choreo::ConstructAt<structchoreo::PuppetSlot>
	void (*gKeepConstructSlot)(PuppetSlot*, const PuppetSlot&) = &ConstructAt<PuppetSlot>;

	// FUNCTION: ENGINE 0x10955700 ; choreo::ConstructAt<unsignedint>
	void (*gKeepConstructIndex)(unsigned int*, const unsigned int&) = &ConstructAt<unsigned int>;

	// FUNCTION: ENGINE 0x10955720 ; choreo::CopyRange<unsignedint>
	unsigned int* (*gKeepCopyIndices)(unsigned int*, unsigned int*, unsigned int*) = &CopyRange<unsigned int>;
}
