#include "code/proto/characterbudget.h"
#include "code/content/loadinventory.h"
#include "code/core/refptr.h"
#include "code/proto/messages/airequestmessages.h"
#include "code/proto/soldierbudgets.h"

#include <stdlib.h>

namespace engine
{
	extern core::Name<core::CaseSensitiveKey> gSpawner;
	extern core::Name<core::CaseSensitiveKey> gSoldier3;
	extern core::Name<core::CaseSensitiveKey> gBlackwatch2;
	extern core::Name<core::CaseSensitiveKey> gCommander3;
	extern core::Name<core::CaseSensitiveKey> gPedMPilotCau;
	extern core::Name<core::CaseSensitiveKey> gCop2;
	extern core::Name<core::CaseSensitiveKey> gTankGunner2;
	extern core::Name<core::CaseSensitiveKey> gTankRamMarine2;
	extern core::Name<core::CaseSensitiveKey> gApcM2Marine2;
	extern core::Name<core::CaseSensitiveKey> gBloodtoxDriller001;
	extern core::Name<core::CaseSensitiveKey> gTankRamThermobaric2;
	extern core::Name<core::CaseSensitiveKey> gHeliGunshipMarineCore2;
	extern core::Name<core::CaseSensitiveKey> gHeliBhMarine2;
	extern core::Name<core::CaseSensitiveKey> gF45Thunder001;
	extern core::Name<core::CaseSensitiveKey> gUav2;
	extern core::Name<core::CaseSensitiveKey> gSupersoldier3;
	extern core::Name<core::CaseSensitiveKey> gInfected13;
	extern core::Name<core::CaseSensitiveKey> gInfected23;
	extern core::Name<core::CaseSensitiveKey> gBrawler2;
	extern core::Name<core::CaseSensitiveKey> gStealth;
	extern core::Name<core::CaseSensitiveKey> gHydra2;
	extern core::Name<core::CaseSensitiveKey> gLeaderHunter2;
	extern core::Name<core::CaseSensitiveKey> gGunTurret;
	extern core::Name<core::CaseSensitiveKey> gSniffer;
	extern core::Name<core::CaseSensitiveKey> gKarenparker;
	extern core::Name<core::CaseSensitiveKey> gBwplainclothes2;
	extern core::Name<core::CaseSensitiveKey> gMissionPed;
	extern core::Name<core::CaseSensitiveKey> gBwscientist;
	extern core::Name<core::CaseSensitiveKey> gDanaMercer;
	extern core::Name<core::CaseSensitiveKey> gFemale2;
	extern core::Name<core::CaseSensitiveKey> gRagland;
}

namespace proto
{
	// 0x103BB410 (another unit): sends the object a SetGameObjectLODAIMsg when its level of detail differs
	bool Unknown103BB410(engine::GameObject* object, int levelOfDetail, bool flag);

	namespace HitEffectManager
	{
		// 0x112562B8: the name of the attribute that holds an object's class name
		extern core::Name<core::CaseSensitiveKey> gClassNameAttributeName;
	}
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

	// FUNCTION: ENGINE 0x10385DA0
	bool SoldierBudgets::Unknown10385DA0(engine::GameObjectHandle handle)
	{
		if (reservedHandle == handle)
		{
			unknown2C = 1.0f;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10385DD0
	bool SoldierBudgets::Unknown10385DD0(engine::GameObjectHandle handle)
	{
		if (reservedHandle == handle)
		{
			reserved = 0;
			reservedHandle.index = 0xffff;
			reservedHandle.serial = 0;
			unknown2C = -1.0f;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10385C00
	void SoldierBudgets::SetObjectLevelOfDetail(engine::GameObject* object, const int* levelOfDetail, bool flag)
	{
		Unknown103BB410(object, *levelOfDetail, flag);
	}

	// FUNCTION: ENGINE 0x10388030
	// NONMATCHING: the engine keeps the result byte in a stack slot and the object in ebp next to a constant 1 in ebx (15.4 %)
#ifdef NONMATCHING
	bool SoldierBudgets::Unknown10388030(engine::GameObjectHandle handle, bool flag)
	{
		bool result = false;
		engine::GameObject* object = handle.Get();
		CharacterBudgetEntry* entry = Find(handle);
		if (entry != entries.end)
		{
			int kind = GetCharacterClassIndex(object);
			if (kind == 1 || kind == 2 || kind == 10)
			{
				return false;
			}
			entry->unknown44 = 2.0f;
			if (entry->unknown34 == 1)
			{
				return true;
			}
			if (flag)
			{
				unknown20 -= entry->policy.weight;
				if (unknown20 < 0)
				{
					return result;
				}
			}
			int levelOfDetail = 1;
			SetObjectLevelOfDetail(entry->handle.Get(), &levelOfDetail, true);
			entry->unknown34 = 1;
			result = true;
		}
		return result;
	}
#endif

	// FUNCTION: ENGINE 0x10388130
	// NONMATCHING: the engine keeps the result in dl, the registers the callee leaves alone (34.5 %)
#ifdef NONMATCHING
	bool SoldierBudgets::Unknown10388130(engine::GameObjectHandle handle)
	{
		if (reserved > 0)
		{
			bool result = Unknown10388030(handle, false);
			if (result)
			{
				reserved--;
				if (reserved == 0)
				{
					Unknown10385DD0(reservedHandle);
				}
			}
			return result;
		}
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x10387FC0
	void SoldierBudgets::LoadPolicies()
	{
		content::LoadInventory* inventory = content::gRootInventory;
		if (inventory != 0)
		{
			CharacterBudgetPolicyList* list = inventory->Find<CharacterBudgetPolicyList>("PolicyList");
			core::RefAssign(policies, list);
		}
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

	// FUNCTION: ENGINE 0x10387800
	int GetCharacterClassIndex(engine::GameObject* object)
	{
		engine::BaseAttribute* attribute = object->FindAttribute(HitEffectManager::gClassNameAttributeName);
		if (attribute != 0 && &((engine::ConstAttribute<core::Name<core::CaseSensitiveKey> >*)attribute)->value != 0)
		{
			const core::Name<core::CaseSensitiveKey>& name = ((engine::ConstAttribute<core::Name<core::CaseSensitiveKey> >*)attribute)->value;
			if (name == engine::gSoldier3 || name == engine::gBlackwatch2 || name == engine::gCommander3 || name == engine::gPedMPilotCau || name == engine::gCop2 || name == engine::gTankGunner2)
			{
				return 0;
			}
			if (name == engine::gTankRamMarine2 || name == engine::gApcM2Marine2 || name == engine::gBloodtoxDriller001 || name == engine::gTankRamThermobaric2)
			{
				return 1;
			}
			if (name == engine::gHeliGunshipMarineCore2 || name == engine::gHeliBhMarine2 || name == engine::gF45Thunder001)
			{
				return 2;
			}
			if (name == engine::gUav2)
			{
				return 3;
			}
			if (name == engine::gSupersoldier3)
			{
				return 4;
			}
			if (name == engine::gInfected13)
			{
				return 5;
			}
			if (name == engine::gInfected23)
			{
				return 6;
			}
			if (name == engine::gBrawler2 || name == engine::gStealth)
			{
				return 7;
			}
			if (name == engine::gHydra2)
			{
				return 8;
			}
			if (name == engine::gLeaderHunter2)
			{
				return 9;
			}
			if (name == engine::gGunTurret || name == engine::gSniffer)
			{
				return 10;
			}
			if (name == engine::gKarenparker || name == engine::gBwplainclothes2 || name == engine::gMissionPed || name == engine::gBwscientist || name == engine::gDanaMercer || name == engine::gFemale2 || name == engine::gRagland)
			{
				return 11;
			}
			return 11;
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x103876A0
	// NONMATCHING: the engine keeps the remaining count in a stack slot and only the list pointer and the offset in registers (72.7 %)
#ifdef NONMATCHING
	void SoldierBudgets::PurgeKissOfDeath()
	{
		int count = entries.Size();
		int offset = 0;
		while (count != 0)
		{
			engine::GameObject* object = ((CharacterBudgetEntry*)((char*)entries.begin + offset))->handle.Get();
			if (object != 0)
			{
				PurgeKissOfDeathAIMsg message;
				object->SendMessage(&message);
			}
			offset += sizeof(CharacterBudgetEntry);
			count--;
		}
	}
#endif

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
template EntryArray::ArrayDynamic(unsigned int, const container::AllocatorNew&);
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
template void core::RefAssign<proto::CharacterBudgetPolicyList>(proto::CharacterBudgetPolicyList*&, proto::CharacterBudgetPolicyList*);
template void core::SafeRelease<proto::CharacterBudgetPolicyList>(proto::CharacterBudgetPolicyList*&);
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
// FUNCTION: ENGINE 0x10386200
// FUNCTION: ENGINE 0x10386240
// FUNCTION: ENGINE 0x103868E0
// FUNCTION: ENGINE 0x103869A0
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
