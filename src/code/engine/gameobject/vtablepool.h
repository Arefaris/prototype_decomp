// engine::DispatchTable and engine::VTablePool (names guessed except InitVTablePool / ShutdownVTablePool, which the
// game object system calls): for every message type the table lists the behaviours of a game object that listen to
// it, and the pool shares one table between all objects whose behaviours listen to the same message masks. Unit
// 0x10897E60 - 0x10898290 (no assert path; the file name is a guess).
#ifndef ENGINE_GAMEOBJECT_VTABLEPOOL_H
#define ENGINE_GAMEOBJECT_VTABLEPOOL_H

#include "code/core/memory/memorypool.h"
#include "code/engine/gameobject/behaviour.h"

namespace engine
{
	// Per message type, the indices of the behaviours listening (0xFF ends the list, 0xFE: none worked out, scan the
	// masks); shared between controllers with the same masks and reference counted
	class DispatchTable
	{
	public:
		// 0x10897F50: lists the behaviours of every message type their masks name
		DispatchTable(const BehaviourController::MessageMask* masks, int count);

		void AddRef()
		{
			refCount++;
		}
		void Release();

		// 0x10897E60: appends the behaviour to the list of a message type (the list takes seven, then it is given up)
		void Add(int messageType, signed char behaviour);
		// 0x10897EB0: whether both tables list the same behaviours
		bool IsSame(const DispatchTable* other);

		signed char entries[63][8];
		int refCount;
	};

	// The hash map of the pool: open addressing over the 64-bit key, holding a table pointer. The engine's code for it is
	// the same as proto::MidgroundMap's and content::LoaderMap's (shared by the linker); the members are declared
	// here only, so the calls reach that code. Layout as proto::MidgroundMap.
	class DispatchMap
	{
	public:
		struct Iterator
		{
			Iterator(DispatchMap* newMap)
			{
				map = newMap;
				key = 0;
				index = 0;
				current = 0;
				step = 0;
			}

			// 0x102DD6F0: the table the key is stored under, null when there is none
			DispatchTable* Find(const unsigned __int64& newKey);

			DispatchMap* map;
			int unknown4;
			unsigned __int64 key;
			int index;
			int current;
			int step;
		};

		// 0x102DE010: a map of at least that many slots (the other numbers are the load limits)
		DispatchMap(unsigned int newCapacity, int a, int b);
		~DispatchMap()
		{
			delete[] buckets;
			delete[] keys;
		}
		// 0x102DDAD0
		void Insert(const unsigned __int64& key, DispatchTable* table);
		// 0x106081B0: forgets every key that holds the table, answers how many there were
		int RemoveValue(DispatchTable* table);

		unsigned int capacity;
		int count;
		int unknown8;
		int unknownC;
		int unknown10;
		int unknown14;
		int unknown18;
		DispatchTable** buckets;  // +0x1C
		unsigned __int64* keys;  // +0x20
		DispatchTable* sentinel;  // +0x24
	};

	class VTablePool
	{
	public:
		// 0x108981F0: room for that many tables
		explicit VTablePool(unsigned int tableCount);
		// 0x10898030 (deleting destructor 0x10898060)
		~VTablePool();
		// 0x10898120 / 0x10898240
		DispatchTable* Find(const BehaviourController::MessageMask* masks, int count);
		void Free(DispatchTable* table);

		DispatchMap map;
		core::MemoryPool pool;  // +0x28
	};

	// 0x11317848
	extern VTablePool* gVTablePool;
	// 0x10898260 / 0x108980B0
	void InitVTablePool(int count);
	void ShutdownVTablePool();
	// 0x10897F10: the key of a list of masks
	unsigned __int64 HashMessageMasks(const BehaviourController::MessageMask* masks, int count);

	inline void DispatchTable::Release()
	{
		refCount--;
		if (refCount <= 0)
		{
			gVTablePool->Free(this);
		}
	}
}

#endif
