#include "code/engine/gameobject/vtablepool.h"
#include <new>
#include <string.h>

namespace engine
{
	// GLOBAL: ENGINE 0x11317848
	VTablePool* gVTablePool;

	// FUNCTION: ENGINE 0x10897E60
	// EQUIVALENT: the engine addresses the list as [edx + eax], ours as [eax + edx] (98.5 %)
	void DispatchTable::Add(int messageType, signed char behaviour)
	{
		signed char* row = entries[messageType];
		if (entries[messageType][0] != -2)
		{
			int count = 0;
			if (*row != -1)
			{
				do
				{
					if (count >= 7)
					{
						break;
					}
					count++;
				}
				while (*(row + count) != -1);
				if (count == 7)
				{
					*row = -2;
					return;
				}
			}
			signed char* slot = &entries[messageType][count];
			*slot = behaviour;
			slot[1] = -1;
		}
	}

	// FUNCTION: ENGINE 0x10897EB0
	bool DispatchTable::IsSame(const DispatchTable* other)
	{
		for (int row = 0; row < 63; row++)
		{
			for (int i = 0; i < 8; i++)
			{
				if (entries[row][i] != other->entries[row][i])
				{
					return false;
				}
				if (entries[row][i] < 0)
				{
					break;
				}
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10897F10
	unsigned __int64 HashMessageMasks(const BehaviourController::MessageMask* masks, int count)
	{
		unsigned __int64 key = 0;
		for (int i = 0; i < count; i++)
		{
			key = key * 0x1003F ^ masks[i].bits;
		}
		return key;
	}

	// FUNCTION: ENGINE 0x10897F50
	DispatchTable::DispatchTable(const BehaviourController::MessageMask* masks, int count)
	{
		refCount = 0;
		for (int i = 0; i < 63; i++)
		{
			entries[i][0] = -1;
		}
		int counts[63] = { 0 };
		for (int behaviour = 0; behaviour < count; behaviour++)
		{
			unsigned __int64 bits = masks[behaviour].bits;
			for (int type = 0; bits != 0 && type < 63; type++)
			{
				if ((bits & 1) != 0)
				{
					counts[type]++;
					Add(type, behaviour);
				}
				bits >>= 1;
			}
		}
	}

	// FUNCTION: ENGINE 0x108981F0
	VTablePool::VTablePool(unsigned int tableCount) : map(tableCount * 2, 0x3c, 100)
	{
		pool.Init(0, sizeof(DispatchTable), tableCount, core::GetCurrentHeap(), "VTablePool", 0x10);
	}

	// FUNCTION: ENGINE 0x10898030
	VTablePool::~VTablePool()
	{
	}

	// FUNCTION: ENGINE 0x10898120
	DispatchTable* VTablePool::Find(const BehaviourController::MessageMask* masks, int count)
	{
		if (count < 2)
		{
			return 0;
		}
		unsigned __int64 key = HashMessageMasks(masks, count);
		DispatchMap::Iterator iterator(&map);
		DispatchTable* table = iterator.Find(key);
		if (table == 0)
		{
			void* block = pool.AllocBlock();
			if (block != 0)
			{
				table = new (block) DispatchTable(masks, count);
			}
			else
			{
				table = 0;
			}
			map.Insert(key, table);
		}
		return table;
	}

	// FUNCTION: ENGINE 0x10898240
	void VTablePool::Free(DispatchTable* table)
	{
		map.RemoveValue(table);
		pool.Free(table);
	}

	// FUNCTION: ENGINE 0x10898260
	void InitVTablePool(int count)
	{
		gVTablePool = new VTablePool(count);
	}

	// FUNCTION: ENGINE 0x108980B0
	void ShutdownVTablePool()
	{
		delete gVTablePool;
		gVTablePool = 0;
	}
}
