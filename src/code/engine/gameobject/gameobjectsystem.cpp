#include "code/core/heap.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/core/memory/memorypool.h"
#include "code/core/memory/segmentpoolallocator.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/messagerouter.h"

namespace core
{
	// 0x10646C10: allocates one of the eight thread-local slots into *slot and sets it to value in every thread
	bool AllocThreadSlot(int* slot, int value);
	// 0x10646C60: gives the slot back
	bool FreeThreadSlot(int slot);
}

namespace engine
{
	// The game object inventory's name in the root inventory (0x11283700)
	extern content::ObjectName gGameObjectsName;
	// The shared identity transform new game objects start with (0x1128329C)
	extern Attribute<math::Matrix>* gIdentityTransform;
	// The round-robin counter of the behaviours' time slicing (0x1130E030)
	extern unsigned char gTimeSliceCounter;
	// Thread-local slots of the game object code (0x111BC0B4 / 0x111BC0B8 / 0x111C65BC; meaning unknown)
	extern int gThreadSlotA;
	extern int gThreadSlotB;
	extern int gThreadSlotC;
	// The pools of the dynamic attributes and their lists (0x112836E4 / 0x112836E8), the heap ids they are
	// registered as (0x111BC0BC / 0x111BC0C0, -1 before) and the list length (0x11283298)
	extern core::MemoryPool* gAttributePool;
	extern core::MemoryPool* gAttributeListPool;
	extern int gAttributeHeap;
	extern int gAttributeListHeap;
	extern unsigned int gAttributeListLength;

	// 0x10898260: creates the behaviours' "VTablePool" (name guess)
	void InitVTablePool(int count);
	// 0x1086C0F0: registers the go_* script commands (name guess)
	void RegisterGameObjectCommands();
	// 0x108980B0 / 0x10867DD0: the counterparts
	void ShutdownVTablePool();
	void UnregisterGameObjectCommands();

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

	// FUNCTION: ENGINE 0x107EF1D0
	MessageListenerRef GetListeners(MessageListeners* listeners)
	{
		return gMessageRouter->FindList(*listeners);
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
	GameObject* CreateGameObject(const content::ObjectName& name, int heap, content::LoadInventory* inventory)
	{
		GameObject* object;
		{
			core::HeapScope scope(heap);
			object = new GameObject;
		}
		if (inventory != 0)
		{
			inventory->Add(name, object);
		}
		return object;
	}

	// FUNCTION: ENGINE 0x107EEE00
	void RenameGameObject(GameObject* object, const content::ObjectName& name)
	{
		if (object != 0)
		{
			object->AddRef();
			if (gGameObjects->Remove(object, true))
			{
				gGameObjects->Add(name, object);
			}
			object->Release();
			object->SetName(name);
		}
	}

	// FUNCTION: ENGINE 0x107EF160
	GameObject* CreateGameObjectInHeap(const content::ObjectName& name, int heap, int unused)
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
		GameObject* object = CreateGameObject(name, heap, gGameObjects);
		if (pool != 0)
		{
			pool->PopCounter();
		}
		return object;
	}

	// FUNCTION: ENGINE 0x107EF6F0
	GameObject* CreateGameObjectHere(const content::ObjectName& name, int unused)
	{
		return CreateGameObjectInHeap(name, core::GetCurrentHeap(), unused);
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
					gGameObjects->Remove(object, true);
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
				gGameObjects->Remove(object, true);
				item--;
				end--;
			}
		}
	}

	// FUNCTION: ENGINE 0x107EF8C0
	void InvalidateHandle(GameObjectHandle* handle, bool notify)
	{
		if (handle->Get() != 0)
		{
			if (notify)
			{
				gMessageRouter->Invalidate(*handle);
			}
			unsigned short index = handle->index;
			handle->serial = gMasterTable->IncrementSerial(index);
		}
	}

	// FUNCTION: ENGINE 0x107EF920
	void SwapGameObjects(GameObjectHandle first, GameObjectHandle second)
	{
		gMessageRouter->SwapHandles(first, second);
		gMasterTable->Swap(first.index, second.index);
		GameObject* secondObject = second.Get();
		GameObject* firstObject = first.Get();
		container::Swap(firstObject->index, secondObject->index);
	}

	// FUNCTION: ENGINE 0x107EF9B0
	// EQUIVALENT: the engine resolves the handle twice (validity, then the object); our build folds the second
	// lookup into the first
	void MoveHandle(GameObjectHandle* from, GameObjectHandle* to)
	{
		if (from->IsValid())
		{
			GameObject* object = from->Get();
			object->index = gMasterTable->Move(from, to);
		}
	}

	// FUNCTION: ENGINE 0x107EFA20
	void ReplaceHandle(const GameObjectHandle* target, const GameObjectHandle* source)
	{
		GameObject* object = target->Get();
		object->index = gMasterTable->Replace(target, source);
	}

	// The engine's identity matrix copied element by element
	static inline void SetIdentity(math::Matrix& matrix)
	{
		matrix.m[0][0] = math::Matrix::IDENTITY.m[0][0];
		matrix.m[0][1] = math::Matrix::IDENTITY.m[0][1];
		matrix.m[0][2] = math::Matrix::IDENTITY.m[0][2];
		matrix.m[0][3] = math::Matrix::IDENTITY.m[0][3];
		matrix.m[1][0] = math::Matrix::IDENTITY.m[1][0];
		matrix.m[1][1] = math::Matrix::IDENTITY.m[1][1];
		matrix.m[1][2] = math::Matrix::IDENTITY.m[1][2];
		matrix.m[1][3] = math::Matrix::IDENTITY.m[1][3];
		matrix.m[2][0] = math::Matrix::IDENTITY.m[2][0];
		matrix.m[2][1] = math::Matrix::IDENTITY.m[2][1];
		matrix.m[2][2] = math::Matrix::IDENTITY.m[2][2];
		matrix.m[2][3] = math::Matrix::IDENTITY.m[2][3];
		matrix.m[3][0] = math::Matrix::IDENTITY.m[3][0];
		matrix.m[3][1] = math::Matrix::IDENTITY.m[3][1];
		matrix.m[3][2] = math::Matrix::IDENTITY.m[3][2];
		matrix.m[3][3] = math::Matrix::IDENTITY.m[3][3];
	}

	// FUNCTION: ENGINE 0x107EFC20
	bool InitGameObjectSystem(const GameObjectSystemConfig* config)
	{
		core::HeapScope scope(config->heap);
		container::AllocatorCoreAligned<16> allocator;
		allocator.heap = config->heap;
		InitVTablePool(0x100);
		gMasterTable = new MasterTable(config->masterTableUnknown, allocator);
		gMessageRouter = new MessageRouter(allocator);
		gDeferredObjects = new container::ArrayDynamicHeap<unsigned short>(config->deferredCapacity, allocator);
		// A loop whose result is not used (left in by the original)
		unsigned short bit = 1;
		while (bit != 0x400)
		{
			bit <<= 1;
		}
		gGameObjects = new content::LoadInventory(0x800);
		content::gRootInventory->Add(gGameObjectsName, gGameObjects);
		gIdentityTransform = new Attribute<math::Matrix>;
		SetIdentity(gIdentityTransform->Get());
		gTimeSliceCounter = 0;
		RegisterGameObjectCommands();
		core::AllocThreadSlot(&gThreadSlotA, 0);
		core::AllocThreadSlot(&gThreadSlotB, -1);
		core::AllocThreadSlot(&gThreadSlotC, 0);
		core::CreateMemoryPool(&gAttributePool, config->attributeSize, config->attributeCount, config->heap,
			"Dynamic Attributes", 0x10);
		core::RegisterHeap(8, config->heap, gAttributePool);
		gAttributeHeap = 8;
		core::CreateMemoryPool(&gAttributeListPool, config->attributeListLength << 4, config->attributeListCount,
			config->heap, "Dynamic Attribute Lists", 0x10);
		core::RegisterHeap(9, config->heap, gAttributeListPool);
		gAttributeListHeap = 9;
		gAttributeListLength = config->attributeListLength;
		gGameObjectSystemShutdown = false;
		return true;
	}

	// FUNCTION: ENGINE 0x107EFF00
	// EQUIVALENT: the engine keeps the iterator's handle in a register and copies the end iterator each round; ours
	// keeps the iterator in memory
	void SendMessage(Message* message, MessageListeners* listeners)
	{
		MessageListenerRef ref = GetListeners(listeners);
		MessageListenerList* list = ref.list;
		for (HandleIterator it = list != 0 ? list->Begin() : HandleIterator();
			it != (list != 0 ? list->End() : HandleIterator()); ++it)
		{
			GetGameObjectEntries()[it->index].object->SendMessage(message);
		}
	}

	// FUNCTION: ENGINE 0x107EFFC0
	// EQUIVALENT: the engine keeps the iterator's handle in a register and copies the end iterator each round; ours
	// keeps the iterator in memory
	void PostMessage(Message* message, MessageListeners* listeners)
	{
		MessageListenerRef ref = GetListeners(listeners);
		MessageListenerList* list = ref.list;
		for (HandleIterator it = list != 0 ? list->Begin() : HandleIterator();
			it != (list != 0 ? list->End() : HandleIterator()); ++it)
		{
			GetGameObjectEntries()[it->index].object->PostMessage(message);
		}
	}

	// FUNCTION: ENGINE 0x107F0080
	bool ReleaseReadyGameObjects()
	{
		bool released = true;
		bool unknown = gGameObjects->GetUnknown8();
		gGameObjects->SetUnknown8(false);
		{
			content::LoadInventory::Iterator it(gGameObjects);
			for (GameObject* object = it.First<GameObject>(); object != 0; object = it.Next<GameObject>())
			{
				if (object->IsReady())
				{
					gGameObjects->Remove(object, true);
				}
				else
				{
					released = false;
				}
			}
			gGameObjects->SetUnknown8(unknown);
		}
		return released;
	}

	// FUNCTION: ENGINE 0x107F0170
	GameObjectHandle FindGameObject(const content::ObjectName& name, const content::ObjectName& inventoryName)
	{
		content::LoadInventory* inventory = content::gRootInventory->Get<content::LoadInventory>(inventoryName);
		if (inventory != 0)
		{
			GameObject* object = inventory->Find<GameObject>(name);
			if (object != 0)
			{
				return GameObjectHandle(object->index);
			}
		}
		return GameObjectHandle();
	}

	// FUNCTION: ENGINE 0x107F01F0
	GameObjectHandle SearchGameObject(const content::ObjectName& name, const content::ObjectName& inventoryName)
	{
		content::LoadInventory* inventory = content::gRootInventory->Find<content::LoadInventory>(inventoryName);
		if (inventory != 0)
		{
			GameObject* object = inventory->Find<GameObject>(name);
			if (object != 0)
			{
				return GameObjectHandle(object->index);
			}
		}
		return GameObjectHandle();
	}

	// FUNCTION: ENGINE 0x107F0270
	// EQUIVALENT: the engine compares the serial again for Get after IsValid; our build folds the second compare
	content::ObjectName GetGameObjectName(GameObjectHandle handle)
	{
		if (handle.IsValid())
		{
			return gGameObjects->GetName(handle.Get());
		}
		return content::ObjectName();
	}

	// FUNCTION: ENGINE 0x107F02D0
	// EQUIVALENT: the engine keeps the iterator's handle in a register and copies the end iterator each round; ours
	// keeps the iterator in memory
	int CountListeners(MessageListeners* listeners)
	{
		int count = 0;
		MessageListenerRef ref = GetListeners(listeners);
		MessageListenerList* list = ref.list;
		for (HandleIterator it = list != 0 ? list->Begin() : HandleIterator();
			it != (list != 0 ? list->End() : HandleIterator()); ++it)
		{
			count++;
		}
		return count;
	}

	// FUNCTION: ENGINE 0x107F03E0
	bool UpdateGameObjectSystemShutdown()
	{
		if (!ReleaseReadyGameObjects())
		{
			return false;
		}
		gTimeSliceCounter = 0;
		gGameObjectSystemShutdown = false;
		return true;
	}

	// FUNCTION: ENGINE 0x107F0790
	// EQUIVALENT: the engine loads gDeferredObjects before it stores the router's list end; our build stores first
	void ClearGameObjectSystem()
	{
		gMasterTable->entries.Clear();
		gMessageRouter->Clear();
		gDeferredObjects->end = gDeferredObjects->begin;
	}

	// FUNCTION: ENGINE 0x107F0870
	// EQUIVALENT: the engine's inlined deferred list destructor keeps the loaded begin pointer for the free; ours
	// reloads it (a local copy in the destructor fixes this but breaks container::Destroy<MessageListenerList>)
	void ShutdownGameObjectSystem()
	{
		while (gGameObjectSystemShutdown)
		{
			UpdateGameObjectSystemShutdown();
		}
		core::FreeThreadSlot(gThreadSlotA);
		core::FreeThreadSlot(gThreadSlotB);
		core::FreeThreadSlot(gThreadSlotC);
		UnregisterGameObjectCommands();
		ClearGameObjectSystem();
		delete gMasterTable;
		gMasterTable = 0;
		delete gMessageRouter;
		gMessageRouter = 0;
		delete gDeferredObjects;
		content::gRootInventory->Remove(gGameObjectsName, gGameObjects, true);
		gGameObjects = 0;
		delete gIdentityTransform;
		core::UnregisterHeap(8);
		gAttributePool->Release();
		gAttributePool = 0;
		gAttributeHeap = -1;
		core::UnregisterHeap(9);
		gAttributeListPool->Release();
		gAttributeListHeap = -1;
		gAttributeListPool = 0;
		ShutdownVTablePool();
	}

	// Kept copies of inline functions: GameObjectIterator's members, container::Swap<unsigned short> and
	// GameObjectHandle's (index) constructor
	// FUNCTION: ENGINE 0x107EEBE0
	// FUNCTION: ENGINE 0x107EF060
	// FUNCTION: ENGINE 0x107EEC70
	// FUNCTION: ENGINE 0x107EF0A0
	// FUNCTION: ENGINE 0x107EF410
	// FUNCTION: ENGINE 0x107EF450
	// ArrayDynamicHeap<unsigned short>'s destructor and scalar deleting destructor, LoadInventory::Iterator's destructor
	// and First<GameObject>, MessageListenerList's destructors, the container::Destroy copies, ArrayFixed's Clear and
	// destructor, MessageRouter's Clear and destructors, MasterTable's scalar deleting destructor
	// FUNCTION: ENGINE 0x107EFAF0
	// FUNCTION: ENGINE 0x107EFED0
	// FUNCTION: ENGINE 0x107EEDB0
	// FUNCTION: ENGINE 0x107EFB60
	// FUNCTION: ENGINE 0x107F03C0
	// FUNCTION: ENGINE 0x107F0670
	// FUNCTION: ENGINE 0x107F06D0
	// FUNCTION: ENGINE 0x107F0700
	// FUNCTION: ENGINE 0x107F0750
	// FUNCTION: ENGINE 0x107F07E0
	// FUNCTION: ENGINE 0x107F0770
	// FUNCTION: ENGINE 0x107F0800
	// FUNCTION: ENGINE 0x107F0830
	// FUNCTION: ENGINE 0x107F06A0
	// LoadInventory::Table::GetName, LoadInventory::Find<LoadInventory>, Get<LoadInventory> and GetName
	// FUNCTION: ENGINE 0x107EF350
	// FUNCTION: ENGINE 0x107EFBC0
	// FUNCTION: ENGINE 0x107EFBA0
	// FUNCTION: ENGINE 0x107EFC00
	// MessageRouter::FindList
	// FUNCTION: ENGINE 0x107EF110
}
