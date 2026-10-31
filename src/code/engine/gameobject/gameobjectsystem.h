// The game object system (unit 0x107EEBC0 - 0x107F09D0; no assert path, the file name is a guess): it creates the
// master table and the message router, registers game objects in the table, iterates them and keeps the list of
// objects whose update is deferred. Names are guesses unless noted.
#ifndef ENGINE_GAMEOBJECT_GAMEOBJECTSYSTEM_H
#define ENGINE_GAMEOBJECT_GAMEOBJECTSYSTEM_H

#include "code/engine/updatecontext.h"
#include "code/engine/gameobject/details/mastertable.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"

#include "code/container/arraydynamic.h"
#include "code/core/heap.h"

namespace engine
{
	struct Message;

	// The inventory of every game object (0x112836F4) and the master table indices of the objects whose update is
	// deferred (0x112836F0)
	extern content::LoadInventory* gGameObjects;
	extern container::ArrayDynamicHeap<unsigned short>* gDeferredObjects;
	class MessageListeners;

	// The valid entries of the master table, in table order
	class GameObjectIterator
	{
	public:
		explicit GameObjectIterator(MasterTable::Entry* first)
		{
			entry = first;
			SkipInvalid();
		}
		// The first valid entry of table
		explicit GameObjectIterator(MasterTable* table)
		{
			MasterTable::Entry* end = table->entries.end;
			MasterTable::Entry* item = table->entries.Begin();
			while (item != end && !item->IsValid())
			{
				item++;
			}
			entry = item;
		}
		GameObjectIterator(const GameObjectIterator& other)
		{
			entry = other.entry;
		}
		void SkipInvalid()
		{
			MasterTable::Entry* end = gMasterTable->entries.end;
			MasterTable::Entry* item = entry;
			while (item != end && !item->IsValid())
			{
				item++;
			}
			entry = item;
		}
		GameObjectIterator& operator++()
		{
			entry++;
			SkipInvalid();
			return *this;
		}
		GameObject* operator*() const
		{
			return (GameObject*)entry->object;
		}
		bool operator!=(const GameObjectIterator& other) const
		{
			return entry != other.entry;
		}

		MasterTable::Entry* entry;
	};

	// The valid entries whose flags intersect a mask
	class FilteredGameObjectIterator
	{
	public:
		FilteredGameObjectIterator(MasterTable::Entry* first, unsigned short newMask)
		{
			mask = newMask;
			entry = first;
			Skip();
		}
		FilteredGameObjectIterator(const GameObjectIterator& first, unsigned short newMask)
		{
			entry = first.entry;
			mask = newMask;
			Skip();
		}
		void Skip()
		{
			MasterTable::Entry* end = gMasterTable->entries.end;
			MasterTable::Entry* item = entry;
			while (item != end && !(item->IsValid() && (item->flags & mask)))
			{
				item++;
			}
			entry = item;
		}
		FilteredGameObjectIterator& operator++()
		{
			entry++;
			Skip();
			return *this;
		}
		bool operator<(const FilteredGameObjectIterator& other) const
		{
			return entry < other.entry;
		}

		MasterTable::Entry* entry;
		unsigned short mask;
	};

	inline GameObjectIterator MasterTable::Begin()
	{
		return GameObjectIterator(entries.Begin());
	}

	// A handle in its saved form: index in the high half, serial in the low half. It is the type the scripts pass
	// as a game object (RTTI type descriptor engine::LuaGOH); the script functions that take one by value leave the
	// slot of the argument alone, which a class derived from it would not
	// A class in the engine's RTTI (.?AVLuaGOH@engine@@): the script wrappers pass typeid(LuaGOH) to
	// Function::GetTypeCode, which compares type_info addresses
	class LuaGOH
	{
	public:
		LuaGOH()
		{
		}

		unsigned int value;
	};
	typedef LuaGOH SerializedHandle;

	// The game object system's state
	extern bool gGameObjectSystemShutdown;
	extern int gGameObjectFrame;
	extern int gGameObjectHeap;

	bool IsGameObjectSystemReady();
	bool SetGameObjectSystemShutdown();
	bool IsGameObjectSystemShutdown();
	void NextGameObjectFrame();
	int GetGameObjectFrame();
	void SetGameObjectHeap();
	int GetGameObjectHeap();
	GameObjectHandle ReserveHandle();
	void UnreserveHandle(GameObjectHandle handle);
	bool IsReservedHandle(GameObjectHandle handle);
	void SetReservedHandle(GameObjectHandle handle);
	void ClearReservedHandle();
	void RegisterGameObject(GameObject* object);
	void UnregisterGameObject(GameObject* object);
	GameObjectHandle GetHandle(GameObject* object);
	SerializedHandle SerializeHandle(GameObjectHandle handle);
	GameObjectHandle DeserializeHandle(SerializedHandle saved);
	GameObjectIterator BeginGameObjects();
	GameObjectIterator EndGameObjects();
	void VisitGameObjects();
	void BroadcastMessage(Message* message);
	void BroadcastBehaviourMessage(Message* message);
	int CountGameObjects();
	GameObject* CreateGameObject(const content::ObjectName& name, int heap, content::LoadInventory* inventory);
	void RenameGameObject(GameObject* object, const content::ObjectName& name);
	GameObject* CreateGameObjectInHeap(const content::ObjectName& name, int heap, int unused);
	GameObject* CreateGameObjectHere(const content::ObjectName& name, int unused);
	void DeferUpdate(GameObjectHandle handle, bool force);
	void FlushDeferredUpdates();
	void InvalidateHandle(GameObjectHandle* handle, bool notify);
	void SwapGameObjects(GameObjectHandle first, GameObjectHandle second);
	void MoveHandle(GameObjectHandle* from, GameObjectHandle* to);
	void ReplaceHandle(const GameObjectHandle* target, const GameObjectHandle* source);

	// The sizes InitGameObjectSystem sets the system up with (names guessed)
	struct GameObjectSystemConfig
	{
		int heap;
		int masterTableUnknown;
		unsigned int deferredCapacity;
		unsigned int attributeSize;
		unsigned int attributeListLength;
		unsigned int attributeCount;
		unsigned int attributeListCount;
	};

	bool InitGameObjectSystem(const GameObjectSystemConfig* config);
	// Delivers message to every subscriber of the channel at once, through GameObject::SendMessage / PostMessage
	void SendMessage(Message* message, MessageListeners* listeners);
	void PostMessage(Message* message, MessageListeners* listeners);
	int CountListeners(MessageListeners* listeners);
	bool ReleaseReadyGameObjects();
	// The game object of name in the inventory of inventoryName in the root inventory (Search also looks inside the
	// inventories; names guessed)
	GameObjectHandle FindGameObject(const content::ObjectName& name, const content::ObjectName& inventoryName);
	GameObjectHandle SearchGameObject(const content::ObjectName& name, const content::ObjectName& inventoryName);
	content::ObjectName GetGameObjectName(GameObjectHandle handle);
	bool UpdateGameObjectSystemShutdown();

	// Updates the behaviours of the objects in the passes of mask: first the objects of pass 0, then pass by pass
	// the deferred ones (name guess)
	void UpdateGameObjects(UpdateContext context, unsigned short mask);
	void ClearGameObjectSystem();
	void ShutdownGameObjectSystem();
}

#endif
