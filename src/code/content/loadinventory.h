// The content library's object store (names from the RTTI: content::LoadObject, content::LoadInventory and its nested
// content::LoadInventory::DynamicCaster<T>). A LoadInventory keeps reference-counted LoadObjects by name; the game
// object system keeps every game object in one (0x112836F4) that it adds to the root inventory (0x11283818). The
// classes live in another unit (0x105FE690 - 0x10603xxx); only what the engine's users need is reconstructed, the
// member names are guesses.
#ifndef CONTENT_LOADINVENTORY_H
#define CONTENT_LOADINVENTORY_H

#include "code/core/criticalsection.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/core/name.h"

namespace content
{
	typedef core::Name<core::CaseSensitiveKey> ObjectName;

	class LoadObject : public core::IRefCount
	{
	public:
		// 0x105FE690: the class's allocation forwards to operator new[]
		static void* operator new(unsigned int size);

		// The vftable (RTTI: 5 slots; slot 2 is the deleting destructor)
		virtual void AddRef();
		virtual void Release();
		virtual void Slot3();
		// True when the object may be released (meaning guessed from the game objects)
		virtual bool IsReady();
	};

	// content::MetaLoadObject (RTTI: 7 slots, the reflected load objects' base)
	class MetaLoadObject : public LoadObject
	{
	public:
		virtual bool Slot5();
		// Takes the name the object is kept under (meaning guessed from the game objects)
		virtual void SetName(const ObjectName& name);
	};

	// The lock of every inventory (a critical section, 0x11276950)
	extern unsigned char gInventoryLock[24];

	class LoadInventory : public LoadObject
	{
	public:
		// The name table (0x28 bytes): count slots of objects and their names; a removed slot points at deleted
		struct Table
		{
			unsigned int count;
			int unknown4;
			int unknown8;
			bool unknownC;
			int unknown10;
			int unknown14;
			int unknown18;
			core::IRefCount** objects;
			ObjectName* names;
			int deleted;

			// The name of object, or the empty name
			ObjectName GetName(LoadObject* object)
			{
				for (unsigned int i = 0; i < count; i++)
				{
					if (objects[i] == object)
					{
						return names[i];
					}
				}
				return ObjectName();
			}
		};

		// Walks the objects of an inventory, holding a reference to it and optionally the inventory lock
		class Iterator
		{
		public:
			// Holding the lock
			explicit Iterator(LoadInventory* newInventory)
			{
				table = newInventory->table;
				inventory = newInventory;
				lock = true;
				newInventory->AddRef();
				core::CriticalSectionEnter(gInventoryLock);
			}
			Iterator(LoadInventory* newInventory, bool newLock)
			{
				table = newInventory->table;
				index = 0;
				inventory = newInventory;
				lock = newLock;
				inventory->AddRef();
				if (lock)
				{
					core::CriticalSectionEnter(gInventoryLock);
				}
			}
			~Iterator()
			{
				if (lock)
				{
					core::CriticalSectionLeave(gInventoryLock);
				}
				inventory->Release();
			}

			// The next used slot's object, null at the end (the engine's calls go to a copy at 0x102D22C0)
			core::IRefCount* NextObject()
			{
				Table* t = table;
				unsigned int i = index;
				do
				{
					i++;
				}
				while (i < t->count && (t->objects[i] == 0 || t->objects[i] == (core::IRefCount*)&t->deleted));
				index = i;
				return i >= t->count ? 0 : t->objects[i];
			}
			// The first / next object that is a T
			template<class T> T* First()
			{
				index = -1;
				core::IRefCount* object = NextObject();
				if (dynamic_cast<T*>(object) != 0)
				{
					return static_cast<T*>(object);
				}
				return Next<T>();
			}
			template<class T> T* Next()
			{
				core::IRefCount* object = NextObject();
				while (object != 0 && dynamic_cast<T*>(object) == 0)
				{
					object = NextObject();
				}
				return static_cast<T*>(object);
			}

			Table* table;
			unsigned int index;
			LoadInventory* inventory;
			bool lock;
		};

		// The filter of a lookup: answers the object as T, or null (one virtual slot)
		class DynamicCasterBase
		{
		public:
			virtual core::IRefCount* Cast(core::IRefCount* object) = 0;
		};

		template<class T> class DynamicCaster : public DynamicCasterBase
		{
		public:
			virtual core::IRefCount* Cast(core::IRefCount* object)
			{
				return dynamic_cast<T*>(object);
			}
		};

		// 0x106033D0: capacity is the size of the name table (a power of two)
		explicit LoadInventory(unsigned int capacity);

		// The vftable (RTTI: 8 slots; 0 / 1 are 0x105FE740 / 0x105FE750)
		virtual void AddRef();
		virtual void Release();
		// Slot 5: the object of name that the caster accepts, searching the inventories inside too when recursive;
		// slot 7: only this inventory (meanings guessed)
		virtual LoadObject* FindObject(DynamicCasterBase* caster, const ObjectName& name, bool recursive);
		virtual void Slot6();
		virtual LoadObject* GetObject(DynamicCasterBase* caster, const ObjectName& name);

		ObjectName GetName(LoadObject* object)
		{
			return table->GetName(object);
		}
		template<class T> T* Find(const ObjectName& name)
		{
			DynamicCaster<T> caster;
			return static_cast<T*>(FindObject(&caster, name, true));
		}
		template<class T> T* Get(const ObjectName& name)
		{
			DynamicCaster<T> caster;
			return static_cast<T*>(GetObject(&caster, name));
		}

		// 0x106032F0 / 0x10603560: adds an object under a name / takes it out again
		void Add(const ObjectName& name, LoadObject* object);
		bool Remove(LoadObject* object, bool unknown);
		// 0x106036C0: takes the object out of the slot of name (lock: take the inventory lock)
		void Remove(const ObjectName& name, LoadObject* object, bool lock);
		// 0x10601C30 / 0x106031D0 (meaning unknown; the setter takes the lock and copies the flag into the table)
		bool GetUnknown8();
		void SetUnknown8(bool value);

		int unknown4;
		bool unknown8;
		bool unknown9;
		Table* table;
		unsigned char unknown10[0x24 - 0x10];
	};

	// The root inventory (0x11283818)
	extern LoadInventory* gRootInventory;
}

#endif
