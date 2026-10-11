// The game object system (unit 0x107EEBC0 - 0x107F0400; no assert path, the file name is a guess): it creates the
// master table and the message router, registers game objects in the table, iterates them and keeps the list of
// objects whose update is deferred. Names are guesses unless noted.
#ifndef ENGINE_GAMEOBJECT_GAMEOBJECTSYSTEM_H
#define ENGINE_GAMEOBJECT_GAMEOBJECTSYSTEM_H

#include "code/engine/gameobject/details/mastertable.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"

#include "code/core/heap.h"

namespace container
{
	// The allocator of a heap chosen at run time, 16-byte aligned (RTTI names AllocatorCoreAligned<16>)
	template<int Align> struct AllocatorCoreAligned
	{
		int heap;
	};

	// Copies [first, last) to dest (front to back)
	template<class T> inline T* Copy(T* first, T* last, T* dest)
	{
		for (; first != last; ++first, ++dest)
		{
			*dest = *first;
		}
		return dest;
	}

	// A growable array over such an allocator: begin / end / capacity, then the allocator's heap (names guessed)
	template<class T> class ArrayDynamicHeap
	{
	public:
		ArrayDynamicHeap(unsigned int count, const AllocatorCoreAligned<16>& allocator)
		{
			heap = allocator.heap;
			if (count != 0)
			{
				begin = (T*)core::HeapAllocAligned(heap, count * sizeof(T), 16);
				if (begin != 0)
				{
					capacity = begin + count;
					end = begin;
					return;
				}
			}
			else
			{
				begin = 0;
			}
			end = 0;
			capacity = 0;
		}
		~ArrayDynamicHeap()
		{
			end = begin;
			if (begin != 0)
			{
				core::HeapFreeAligned(heap, begin);
			}
		}
		bool Allocate(unsigned int count);
		void Clear();
		T* Find(const T& value)
		{
			T* item = begin;
			while (item != end && *item != value)
			{
				item++;
			}
			return item;
		}
		bool PushBack(const T& value)
		{
			if (end < capacity)
			{
				T* item = end++;
				if (item != 0)
				{
					*item = value;
				}
				return true;
			}
			return false;
		}
		void Erase(T* item)
		{
			Copy(item + 1, end, item);
			end--;
		}

		T* begin;
		T* end;
		T* capacity;
		int heap;
	};

	template<class T> bool ArrayDynamicHeap<T>::Allocate(unsigned int count)
	{
		if (count != 0)
		{
			begin = (T*)core::HeapAllocAligned(heap, count * sizeof(T), 16);
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

	template<class T> void ArrayDynamicHeap<T>::Clear()
	{
		end = begin;
		if (begin != 0)
		{
			core::HeapFreeAligned(heap, begin);
		}
	}
}

namespace engine
{
	class Message;

	// The group game objects are updated in (another unit, 0x1060xxxx; names guessed)
	class UpdateGroup
	{
	public:
		// 0x106032F0 / 0x10603560
		void Add(int key, void* object);
		bool Remove(void* object, bool unknown);
	};

	// The update group (0x112836F4) and the master table indices of the objects whose update is deferred (0x112836F0)
	extern UpdateGroup* gUpdateGroup;
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
	GameObject* CreateGameObject(int key, int heap, UpdateGroup* group);
	void MoveGameObject(GameObject* object, int key);
	GameObject* CreateGameObjectInHeap(int key, int heap, int unused);
	GameObject* CreateGameObjectHere(int key, int unused);
	void DeferUpdate(GameObjectHandle handle, bool force);
	void FlushDeferredUpdates();
}

#endif
