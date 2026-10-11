#include "code/core/heap.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/core/memory/segmentpoolallocator.h"
#include "code/engine/gameobject/gameobjectsystem.h"

namespace engine
{
	// The message router (0x11318090, gameobjecthandle.cpp declares the class); InitListeners is 0x108A5370
	class MessageRouter
	{
	public:
		void InitListeners(MessageListeners* listeners, int count);
	};
	extern MessageRouter* gMessageRouter;

	// GLOBAL: ENGINE 0x112836EC
	// GLOBAL: ENGINE 0x112836F8
	// GLOBAL: ENGINE 0x112836E0
	// (declared extern and mapped in symbols.txt)

	// FUNCTION: ENGINE 0x107EECF0
	bool IsGameObjectSystemReady()
	{
		return gMasterTable != 0;
	}

	// FUNCTION: ENGINE 0x107EED00
	bool SetGameObjectSystemShutdown()
	{
		return gGameObjectSystemShutdown = true;
	}

	// FUNCTION: ENGINE 0x107EED10
	bool IsGameObjectSystemShutdown()
	{
		return gGameObjectSystemShutdown;
	}

	// FUNCTION: ENGINE 0x107EED20
	void InitMessageListeners(MessageListeners* listeners, int count)
	{
		gMessageRouter->InitListeners(listeners, count);
	}

	// FUNCTION: ENGINE 0x107EED40
	void NextGameObjectFrame()
	{
		gGameObjectFrame++;
	}

	// FUNCTION: ENGINE 0x107EED50
	int GetGameObjectFrame()
	{
		return gGameObjectFrame;
	}

	// FUNCTION: ENGINE 0x107EEDE0
	SerializedHandle SerializeHandle(GameObjectHandle handle)
	{
		SerializedHandle saved;
		saved.value = (handle.index << 16) | handle.serial;
		return saved;
	}

	// FUNCTION: ENGINE 0x107EEE50
	void SetGameObjectHeap()
	{
		gGameObjectHeap = core::GetCurrentHeap();
	}

	// FUNCTION: ENGINE 0x107EEE60
	int GetGameObjectHeap()
	{
		return gGameObjectHeap;
	}

	// FUNCTION: ENGINE 0x107EEE70
	GameObjectHandle ReserveHandle()
	{
		return gMasterTable->Reserve();
	}

	// FUNCTION: ENGINE 0x107EEE90
	void UnreserveHandle(GameObjectHandle handle)
	{
		gMasterTable->Unreserve(handle.index);
	}

	// FUNCTION: ENGINE 0x107EEEB0
	bool IsReservedHandle(GameObjectHandle handle)
	{
		if (handle.index != 0xffff)
		{
			return gMasterTable->IsReserved(handle);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107EEED0
	void SetReservedHandle(GameObjectHandle handle)
	{
		gMasterTable->SetReservedHandle(handle);
	}

	// FUNCTION: ENGINE 0x107EEEF0
	void ClearReservedHandle()
	{
		gMasterTable->ClearReservedHandle();
	}

	// FUNCTION: ENGINE 0x107EEF00
	void RegisterGameObject(GameObject* object)
	{
		if (object->index == 0xffff)
		{
			int index = gMasterTable->Allocate(object);
			if (index != 0xffff)
			{
				object->index = index;
			}
		}
	}

	// FUNCTION: ENGINE 0x107EEF30
	void UnregisterGameObject(GameObject* object)
	{
		if (object != 0)
		{
			unsigned short index = object->index;
			if (index != 0xffff)
			{
				object->index = 0xffff;
				gMasterTable->Release(index);
			}
		}
	}

	// FUNCTION: ENGINE 0x107EEF60
	GameObjectHandle GetHandle(GameObject* object)
	{
		if (object != 0 && object->index != 0xffff)
		{
			return GameObjectHandle(object->index);
		}
		return GameObjectHandle();
	}

	// FUNCTION: ENGINE 0x107EF0D0
	void FilteredGameObjectIterator::Skip()
	{
		MasterTable::Entry* end = gMasterTable->entries.end;
		MasterTable::Entry* item = entry;
		while (item != end && !(item->IsValid() && (item->flags & mask)))
		{
			item++;
		}
		entry = item;
	}

	// FUNCTION: ENGINE 0x107EF210
	GameObjectHandle DeserializeHandle(SerializedHandle saved)
	{
		unsigned short index = (unsigned short)(saved.value >> 16);
		if (index != 0xffff && index < (unsigned int)gMasterTable->entries.Size())
		{
			return GameObjectHandle(index, (unsigned short)saved.value);
		}
		return GameObjectHandle();
	}

	// FUNCTION: ENGINE 0x107EF4E0
	GameObjectIterator MasterTable::End()
	{
		return GameObjectIterator(entries.end);
	}

	// FUNCTION: ENGINE 0x107EF520
	GameObjectIterator BeginGameObjects()
	{
		return GameObjectIterator(gMasterTable);
	}

	// FUNCTION: ENGINE 0x107EF550
	GameObjectIterator EndGameObjects()
	{
		return GameObjectIterator(gMasterTable->End());
	}

	// FUNCTION: ENGINE 0x107EF570
	void VisitGameObjects()
	{
		// The loop body is compiled out of this build
		GameObjectIterator it(gMasterTable);
		for (MasterTable::Entry* end = gMasterTable->End().entry; it.entry < end; ++it)
		{
		}
	}

	// FUNCTION: ENGINE 0x107EF5E0
	void BroadcastMessage(Message* message)
	{
		GameObjectIterator it(gMasterTable);
		for (MasterTable::Entry* end = gMasterTable->End().entry; it.entry != end; ++it)
		{
			(*it)->SendMessage(message);
		}
	}

	// FUNCTION: ENGINE 0x107EF660
	void BroadcastBehaviourMessage(Message* message)
	{
		GameObjectIterator it(gMasterTable);
		for (MasterTable::Entry* end = gMasterTable->End().entry; it.entry != end; ++it)
		{
			(*it)->behaviours.HandleMessage(message);
		}
	}

	// FUNCTION: ENGINE 0x107EF850
	int CountGameObjects()
	{
		int count = 0;
		GameObjectIterator it(gMasterTable);
		for (MasterTable::Entry* end = gMasterTable->End().entry; it.entry != end; ++it)
		{
			count++;
		}
		return count;
	}

	// FUNCTION: ENGINE 0x107EED60
	GameObject* CreateGameObject(int key, int heap, UpdateGroup* group)
	{
		GameObject* object;
		{
			core::HeapScope scope(heap);
			object = new GameObject;
		}
		if (group != 0)
		{
			group->Add(key, object);
		}
		return object;
	}

	// FUNCTION: ENGINE 0x107EEE00
	void MoveGameObject(GameObject* object, int key)
	{
		if (object != 0)
		{
			object->AddRef();
			if (gUpdateGroup->Remove(object, true))
			{
				gUpdateGroup->Add(key, object);
			}
			object->Release();
			object->Slot6(key);
		}
	}

	// FUNCTION: ENGINE 0x107EF160
	GameObject* CreateGameObjectInHeap(int key, int heap, int unused)
	{
		core::SegmentPoolAllocator* pool = 0;
		int value;
		if (core::GetHeapAllocator(heap)->GetStat(0xb, &value))
		{
			SetGameObjectHeap();
			pool = static_cast<core::SegmentPoolAllocator*>(core::GetHeapAllocator(heap));
			pool->PushCounter();
			pool->Open();
		}
		GameObject* object = CreateGameObject(key, heap, gUpdateGroup);
		if (pool != 0)
		{
			pool->PopCounter();
		}
		return object;
	}

	// FUNCTION: ENGINE 0x107EF6F0
	GameObject* CreateGameObjectHere(int key, int unused)
	{
		return CreateGameObjectInHeap(key, core::GetCurrentHeap(), unused);
	}

	// FUNCTION: ENGINE 0x107EF710
	void DeferUpdate(GameObjectHandle handle, bool force)
	{
		GameObject* object = handle.Get();
		if (object != 0)
		{
			container::ArrayDynamicHeap<unsigned short>* deferred = gDeferredObjects;
			if (deferred->Find(object->index) == deferred->end)
			{
				if (!force && object->IsReady())
				{
					gUpdateGroup->Remove(object, true);
					return;
				}
				gDeferredObjects->PushBack(object->index);
			}
		}
	}

	// FUNCTION: ENGINE 0x107EF7B0
	void FlushDeferredUpdates()
	{
		unsigned short* end = gDeferredObjects->end;
		for (unsigned short* item = gDeferredObjects->begin; item != end; item++)
		{
			GameObject* object = (GameObject*)gMasterTable->entries[*item].object;
			if (object != 0 && object->IsReady())
			{
				container::ArrayDynamicHeap<unsigned short>* deferred = gDeferredObjects;
				container::Copy(item + 1, deferred->end, item);
				deferred->end--;
				gUpdateGroup->Remove(object, true);
				item--;
				end--;
			}
		}
	}

	// Kept copies of GameObjectIterator's inline members
	// FUNCTION: ENGINE 0x107EF0A0
	// FUNCTION: ENGINE 0x107EF410
	// FUNCTION: ENGINE 0x107EF450
}
