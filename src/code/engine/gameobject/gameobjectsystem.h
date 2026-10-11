// The game object system (unit 0x107EEBC0 - 0x107F0400; no assert path, the file name is a guess): it creates the
// master table and the message router, registers game objects in the table, iterates them and keeps the list of
// objects whose update is deferred. Names are guesses unless noted.
#ifndef ENGINE_GAMEOBJECT_GAMEOBJECTSYSTEM_H
#define ENGINE_GAMEOBJECT_GAMEOBJECTSYSTEM_H

#include "code/engine/gameobject/details/mastertable.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace engine
{
	class Message;
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
		void Skip();
		FilteredGameObjectIterator& operator++()
		{
			entry++;
			Skip();
			return *this;
		}

		MasterTable::Entry* entry;
		unsigned short mask;
	};

	inline GameObjectIterator MasterTable::Begin()
	{
		return GameObjectIterator(entries.Begin());
	}

	// A handle in its saved form: index in the high half, serial in the low half
	struct SerializedHandle
	{
		SerializedHandle()
		{
		}

		unsigned int value;
	};

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
}

#endif
