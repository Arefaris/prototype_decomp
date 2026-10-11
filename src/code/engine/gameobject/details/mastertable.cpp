#include "code/core/debug.h"
#include "code/engine/gameobject/details/mastertable.h"

#define MASTERTABLE_FILE "..\\..\\..\\code\\engine\\gameobject\\details\\mastertable.cpp"

namespace engine
{
	// Kept copies of inline functions (Entry and ArrayFixed members, container helpers, GameObjectHandle's
	// (index, serial) constructor); their symbols are in symbols.txt
	// FUNCTION: ENGINE 0x107E1D20
	// FUNCTION: ENGINE 0x107E1D40
	// FUNCTION: ENGINE 0x107E1D50
	// FUNCTION: ENGINE 0x107E1D60
	// FUNCTION: ENGINE 0x107E1D70
	// FUNCTION: ENGINE 0x107E1D80
	// FUNCTION: ENGINE 0x107E1DA0
	// FUNCTION: ENGINE 0x107E1DC0
	// FUNCTION: ENGINE 0x107E1DD0
	// FUNCTION: ENGINE 0x107E1DF0
	// FUNCTION: ENGINE 0x107E1E00
	// FUNCTION: ENGINE 0x107E1E10
	// FUNCTION: ENGINE 0x107E1E30
	// FUNCTION: ENGINE 0x107E1E40
	// FUNCTION: ENGINE 0x107E1E60
	// FUNCTION: ENGINE 0x107E1EC0
	// FUNCTION: ENGINE 0x107E1ED0
	// FUNCTION: ENGINE 0x107E1EE0
	// FUNCTION: ENGINE 0x107E1EF0
	// FUNCTION: ENGINE 0x107E1F10
	// FUNCTION: ENGINE 0x107E1F40
	// FUNCTION: ENGINE 0x107E2180

	// FUNCTION: ENGINE 0x107E1E90
	void MasterTable::ClearReservedHandle()
	{
		sReservedHandle = GameObjectHandle();
		sHasReservedHandle = false;
	}

	// FUNCTION: ENGINE 0x107E1F90
	unsigned short MasterTable::IncrementSerial(unsigned short index)
	{
		Entry& entry = entries[index];
		entry.serial++;
		return entry.serial;
	}

	// FUNCTION: ENGINE 0x107E1FB0
	void MasterTable::Release(unsigned short index)
	{
		Entry& entry = entries[index];
		entry.count = 0;
		++entry.serial;
		entry.ClearObject();
		if (!entry.IsReserved())
		{
			entry.object = freeList;
			entry.used = 0;
			freeList = &entry;
		}
	}

	// FUNCTION: ENGINE 0x107E2000
	void MasterTable::Swap(unsigned short a, unsigned short b)
	{
		Entry& first = entries[a];
		Entry& second = entries[b];
		first.Swap(second);
	}

	// FUNCTION: ENGINE 0x107E2050
	void MasterTable::Unreserve(unsigned short index)
	{
		Entry& entry = entries[index];
		if (entry.IsReserved())
		{
			entry.Unreserve();
			if (!entry.IsValid())
			{
				entry.SetNext(freeList);
				freeList = &entry;
			}
		}
		else
		{
			OLD_ASSERT_AT(MASTERTABLE_FILE, 0xc7, false, "false", "");
		}
	}

	// FUNCTION: ENGINE 0x107E20E0
	bool MasterTable::IsReserved(GameObjectHandle handle)
	{
		Entry& entry = entries[handle.index];
		return entry.IsReserved() && handle.serial + 1 == entry.serial;
	}

	// FUNCTION: ENGINE 0x107E2120
	void MasterTable::SetFlags(unsigned short index, unsigned short mask)
	{
		entries[index].SetFlags(mask);
	}

	// FUNCTION: ENGINE 0x107E2140
	void MasterTable::ClearFlags(unsigned short index, int mask)
	{
		entries[index].ClearFlags(mask);
	}

	// FUNCTION: ENGINE 0x107E2160
	void MasterTable::SetReservedHandle(GameObjectHandle handle)
	{
		sReservedHandle = handle;
		sHasReservedHandle = true;
	}

	// FUNCTION: ENGINE 0x107E21D0
	// EQUIVALENT: the engine copies the reserved handle into eax and zero-extends the index into esi; our build keeps
	// the copy in esi
	unsigned short MasterTable::Allocate(void* object)
	{
		if (sHasReservedHandle)
		{
			GameObjectHandle reserved = sReservedHandle;
			unsigned short index = reserved.index;
			entries[index].Set(object, sReservedHandle.serial);
			ClearReservedHandle();
			return index;
		}
		if (freeList != 0)
		{
			Entry* entry = freeList;
			freeList = (Entry*)entry->object;
			entry->SetObject(object);
			return entry - entries.Begin();
		}
		if (!entries.PushBack(Entry(object)))
		{
			return 0xffff;
		}
		return entries.Size() - 1;
	}

	// FUNCTION: ENGINE 0x107E22A0
	GameObjectHandle MasterTable::Reserve()
	{
		unsigned short index = Allocate(0);
		Entry& entry = entries[index];
		// The handle carries the serial one behind the entry's (see IsReserved)
		unsigned short serial = entry.NextSerial();
		++entry.serial;
		entry.Reserve();
		entry.ClearObject();
		return GameObjectHandle(index, serial);
	}

	// FUNCTION: ENGINE 0x107E2300
	// EQUIVALENT: register choice (ebx / esi / edi swapped) and the count copy is merged into one xor / and / xor insert
	unsigned short MasterTable::Move(const GameObjectHandle* from, GameObjectHandle* to)
	{
		unsigned short oldIndex = from->index;
		Entry& oldEntry = entries[oldIndex];
		unsigned short newIndex = Allocate(oldEntry.object);
		if (newIndex != 0xffff)
		{
			Entry& newEntry = entries[newIndex];
			GameObjectHandle handle(newIndex, newEntry.serial);
			*to = handle;
			newEntry.SetCount(oldEntry.GetCount());
		}
		Release(oldIndex);
		return newIndex;
	}

	// FUNCTION: ENGINE 0x107E2380
	// EQUIVALENT: register choice and the count copy is merged into one xor / and / xor insert
	unsigned short MasterTable::Replace(const GameObjectHandle* target, const GameObjectHandle* source)
	{
		unsigned short index = target->index;
		Entry& entry = entries[index];
		entry.Set(source->Get(), target->serial);
		entry.SetCount(entries[source->index].GetCount());
		Release(source->index);
		return index;
	}
}
