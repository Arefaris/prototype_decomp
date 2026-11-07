#include "code/proto/characterbudget.h"
#include "code/proto/messages/airequestmessages.h"
#include "code/proto/soldierbudgets.h"

#include <stdlib.h>

namespace engine
{
	extern core::Name<core::CaseSensitiveKey> gSpawner;
}

namespace proto
{
	// FUNCTION: ENGINE 0x10386930
	CharacterBudgetEntry::CharacterBudgetEntry(engine::GameObjectHandle newHandle, int unused)
		: handle(newHandle), unknown4(true), distance(1.0e12f), unknown34(0), unknown38(0), levelOfDetail(4),
		unknown41(false), unknown44(-1.0f), unknown48(-1.0f)
	{
	}

	// FUNCTION: ENGINE 0x10386EF0
	CharacterBudgetEntry::CharacterBudgetEntry(const CharacterBudgetEntry& other)
		: handle(other.handle), unknown4(other.unknown4), unknown5(other.unknown5), policy(other.policy),
		distance(other.distance), unknown34(other.unknown34), unknown38(other.unknown38), unknown3C(other.unknown3C),
		levelOfDetail(other.levelOfDetail), unknown41(other.unknown41), unknown44(other.unknown44),
		unknown48(other.unknown48), unknown4C(other.unknown4C)
	{
	}

	// FUNCTION: ENGINE 0x10386A00
	CharacterBudgetEntry& CharacterBudgetEntry::operator=(const CharacterBudgetEntry& other)
	{
		handle = other.handle;
		unknown4 = other.unknown4;
		unknown5 = other.unknown5;
		policy = other.policy;
		distance = other.distance;
		unknown34 = other.unknown34;
		unknown38 = other.unknown38;
		unknown3C = other.unknown3C;
		levelOfDetail = other.levelOfDetail;
		unknown41 = other.unknown41;
		unknown44 = other.unknown44;
		unknown48 = other.unknown48;
		unknown4C = other.unknown4C;
		return *this;
	}

	// FUNCTION: ENGINE 0x10385910
	bool CharacterBudgetEntry::IsBefore(const CharacterBudgetEntry& other) const
	{
		if (levelOfDetail != other.levelOfDetail)
		{
			return levelOfDetail < other.levelOfDetail;
		}
		if (levelOfDetail == 2 && unknown44 != other.unknown44)
		{
			return unknown44 > other.unknown44;
		}
		if (policy.priority == other.policy.priority)
		{
			if (distance == other.distance)
			{
				return handle.index < other.handle.index;
			}
			return distance < other.distance;

		}
		return policy.priority > other.policy.priority;
	}

	// FUNCTION: ENGINE 0x10386540
	CharacterBudgetEntry* SoldierBudgets::Find(engine::GameObjectHandle handle)
	{
		for (CharacterBudgetEntry* entry = entries.begin; entry != entries.end; entry++)
		{
			if (entry->handle == handle)
			{
				return entry;
			}
		}
		return entries.end;
	}

	// FUNCTION: ENGINE 0x10386570
	const CharacterBudgetEntry* SoldierBudgets::Find(engine::GameObjectHandle handle) const
	{
		for (const CharacterBudgetEntry* entry = entries.begin; entry != entries.end; entry++)
		{
			if (entry->handle == handle)
			{
				return entry;
			}
		}
		return entries.end;
	}

	// FUNCTION: ENGINE 0x103865A0
	bool SoldierBudgets::SetUnlimitedDistances(engine::GameObjectHandle handle, bool unlimited)
	{
		bool result = false;
		CharacterBudgetEntry* entry = Find(handle);
		if (entry != entries.end)
		{
			result = true;
			if (unlimited)
			{
				entry->policy.freezeDistanceSquared = 1.0e12f;
				entry->policy.despawnDistanceSquared = 1.0e12f;
			}
			else
			{
				entry->policy.freezeDistanceSquared = gDefaultFreezeDistanceSquared;
				entry->policy.despawnDistanceSquared = gDefaultDespawnDistanceSquared;
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10386620
	bool SoldierBudgets::SetPolicy(engine::GameObjectHandle handle, const CharacterBudgetPolicy& policy)
	{
		bool result = false;
		CharacterBudgetEntry* entry = Find(handle);
		if (entry != entries.end)
		{
			result = true;
			entry->policy = policy;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10386690
	CharacterBudgetPolicy* SoldierBudgets::GetPolicy(engine::GameObjectHandle handle)
	{
		CharacterBudgetPolicy* result = 0;
		CharacterBudgetEntry* entry = Find(handle);
		if (entry != entries.end)
		{
			result = &entry->policy;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x103866F0
	// NONMATCHING: the engine expands SetPolicy in place and keeps the list in esi and the index in ebx (27.3 %)
#ifdef NONMATCHING
	bool SoldierBudgets::SetPolicyByName(engine::GameObjectHandle handle, core::Name<core::CaseSensitiveKey> className)
	{
		int count = policies->policies.Size();
		int i = 0;
		if (0 < count)
		{
			CharacterBudgetPolicy* policy = policies->policies.begin;
			while (!(className == policy->className))
			{
				i++;
				policy++;
				if (count <= i)
				{
					return false;
				}
			}
			if (policy != 0)
			{
				return SetPolicy(handle, *policy);
			}
		}
		return false;
	}

#endif

	// FUNCTION: ENGINE 0x103867D0
	bool SoldierBudgets::SetDespawnDistanceSquared(engine::GameObjectHandle handle, const float* value)
	{
		bool result = false;
		CharacterBudgetEntry* entry = Find(handle);
		if (entry != entries.end)
		{
			float newValue = *value;
			result = true;
			entry->policy.despawnDistanceSquared = newValue;
		}
		return result;

	}

	// FUNCTION: ENGINE 0x103866C0
	bool SoldierBudgets::Unknown103866C0(engine::GameObjectHandle handle) const
	{
		bool result = false;
		const CharacterBudgetEntry* entry = Find(handle);
		if (entry != entries.end)
		{
			result = entry->unknown38 <= 0;

		}
		return result;
	}

	// FUNCTION: ENGINE 0x10386810
	bool SoldierBudgets::Unknown10386810(int type, engine::GameObjectHandle handle)
	{
		if (reserved == 0 || reservedHandle == handle)
		{
			if ((int)entries.Size() + 10 + type < maxEntries)
			{
				reserved = type;
				reservedHandle = handle;
				unknown2C = 1.0f;
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10387530
	void SoldierBudgets::ResetUnknown48(engine::GameObjectHandle handle)
	{
		CharacterBudgetEntry* entry = Find(handle);
		if (entry != entries.end)
		{
			entry->unknown48 = 1.0f;
		}
	}

	// FUNCTION: ENGINE 0x10387620
	bool SoldierBudgets::SetUnknown4(engine::GameObject* object, bool value)
	{
		bool result = false;
		if (object != 0)
		{
			for (CharacterBudgetEntry* entry = entries.begin; entry != entries.end; entry++)
			{
				if (entry->handle.IsValid() && object == entry->handle.Get())
				{
					entry->unknown4 = value;
					result = true;
					break;
				}
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10387760
	engine::GameObject* SoldierBudgets::GetSpawner(engine::GameObject* object)
	{
		engine::GameObject* result = 0;
		engine::BaseAttribute* attribute = object->FindAttribute(engine::gSpawner);
		if (attribute != 0 && &((engine::ConstAttribute<engine::GameObjectHandle>*)attribute)->value != 0)
		{
			result = ((engine::ConstAttribute<engine::GameObjectHandle>*)attribute)->value.Get();
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10387B40
	void SoldierBudgets::Sort()
	{
		SortCharacterBudgetEntries(entries.begin, entries.end);
	}

	// FUNCTION: ENGINE 0x103862F0
	int CompareCharacterBudgetEntries(const void* first, const void* second)
	{
		const CharacterBudgetEntry* a = (const CharacterBudgetEntry*)first;
		const CharacterBudgetEntry* b = (const CharacterBudgetEntry*)second;
		if (a->IsBefore(*b))
		{
			return -1;
		}
		return b->IsBefore(*a) ? 1 : 0;
	}

	// FUNCTION: ENGINE 0x10386C70
	void SortCharacterBudgetEntries(CharacterBudgetEntry* begin, CharacterBudgetEntry* end)
	{
		qsort(begin, end - begin, sizeof(CharacterBudgetEntry), CompareCharacterBudgetEntries);
	}

	// FUNCTION: ENGINE 0x10388D50
	CharacterBudgetEntry* SoldierBudgets::RemoveEntry(engine::GameObjectHandle handle)
	{
		CharacterBudgetEntry* entry = entries.begin;
		if (entry == entries.end)
		{
			return entry;
		}
		while (entry != entries.end)
		{
			if (entry->handle == handle)
			{
				entries.end--;
				if (entry < entries.end)
				{
					return &(*entry = *entries.end);
				}
				return entry;
			}
			entry++;
		}
		return entry;
	}


	// FUNCTION: ENGINE 0x10388EC0
	void SoldierBudgets::RemoveDeadEntries()
	{
		CharacterBudgetEntry* entry = entries.begin;
		while (entry != entries.end)
		{
			if (entry->handle.IsValid())
			{
				entry++;
			}
			else
			{
				entries.EraseSwap(entry);
			}
		}
		SortCharacterBudgetEntries(entries.begin, entries.end);
	}

	// FUNCTION: ENGINE 0x10388F40
	bool SoldierBudgets::ReturnSpawnedObjects(int count)
	{
		int index = entries.Size() - 1;
		if (count > 0)
		{
			do
			{
				if (index < 0)
				{
					break;
				}
				CharacterBudgetEntry* entry = &entries[index];
				if (entry->handle.IsValid())
				{
					engine::GameObject* spawner = GetSpawner(entry->handle.Get());
					if (spawner != 0)
					{
						ReturnObjectSpawnMessage message(1);
						spawner->SendMessage(&message);
						entries[index].handle.DeferUpdate(false);
						entries.Erase(&entries[index]);
						count--;
					}
				}
				index--;
			}
			while (count > 0);
		}
		return count == 0;
	}

	// FUNCTION: ENGINE 0x103892E0
	bool SoldierBudgets::MakeRoom(bool returnSpawns)
	{
		bool result = true;
		if ((int)entries.Size() >= maxEntries)
		{
			RemoveDeadEntries();
			if ((int)entries.Size() >= maxEntries)
			{
				if (returnSpawns)
				{
					result = ReturnSpawnedObjects(5);
				}
				else
				{
					result = false;
				}
			}
		}
		return result;
	}
}

namespace
{
	typedef container::ArrayDynamic<proto::CharacterBudgetEntry, container::AllocatorNew> EntryArray;
}

template EntryArray::ArrayDynamic();
template EntryArray::ArrayDynamic(unsigned int);
template EntryArray::ArrayDynamic(const EntryArray&);
template EntryArray& EntryArray::operator=(const EntryArray&);
template EntryArray::~ArrayDynamic();
template proto::CharacterBudgetEntry* EntryArray::Begin();
template proto::CharacterBudgetEntry* EntryArray::End();
template unsigned int EntryArray::Size() const;
template unsigned int EntryArray::Capacity() const;
template proto::CharacterBudgetEntry& EntryArray::operator[](int);
template const proto::CharacterBudgetEntry& EntryArray::operator[](int) const;
template bool EntryArray::Create(unsigned int);
template void EntryArray::Allocate(unsigned int);
template void EntryArray::Clear();
template bool EntryArray::PushBack(const proto::CharacterBudgetEntry&);
template void EntryArray::Free();
template proto::CharacterBudgetEntry* EntryArray::EraseSwap(proto::CharacterBudgetEntry*);
template proto::CharacterBudgetEntry* EntryArray::Grow();
template proto::CharacterBudgetEntry* EntryArray::Erase(proto::CharacterBudgetEntry*);
template void EntryArray::ShiftUp(proto::CharacterBudgetEntry*, int);
template void EntryArray::Erase(proto::CharacterBudgetEntry*, proto::CharacterBudgetEntry*);
template void EntryArray::Resize(unsigned int, const proto::CharacterBudgetEntry&);
template void EntryArray::Reserve(int);
template proto::CharacterBudgetEntry* EntryArray::Insert(proto::CharacterBudgetEntry*, unsigned int,
	const proto::CharacterBudgetEntry&);
template proto::CharacterBudgetEntry* EntryArray::Insert(proto::CharacterBudgetEntry*, const proto::CharacterBudgetEntry&);


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10385FD0
// FUNCTION: ENGINE 0x10385FF0
// FUNCTION: ENGINE 0x10386010
// FUNCTION: ENGINE 0x10386030
// FUNCTION: ENGINE 0x10386050
// FUNCTION: ENGINE 0x10386130
// FUNCTION: ENGINE 0x103868E0
// FUNCTION: ENGINE 0x10386C30
// FUNCTION: ENGINE 0x10386CB0
// FUNCTION: ENGINE 0x10387100
// FUNCTION: ENGINE 0x10387D20
// FUNCTION: ENGINE 0x10387D40
// FUNCTION: ENGINE 0x10388640
// FUNCTION: ENGINE 0x103886F0
// FUNCTION: ENGINE 0x10388AE0
// FUNCTION: ENGINE 0x10388B10
// FUNCTION: ENGINE 0x10388B40
// FUNCTION: ENGINE 0x103890A0
