// The content library's object store (names from the RTTI: content::LoadObject, content::LoadInventory and its nested
// content::LoadInventory::DynamicCaster<T>). A LoadInventory keeps reference-counted LoadObjects by name; the game
// object system keeps every game object in one (0x112836F4) that it adds to the root inventory (0x11283818). The
// classes live in another unit (0x105FE690 - 0x10603xxx); only what the engine's users need is reconstructed, the
// member names are guesses.
#ifndef CONTENT_LOADINVENTORY_H
#define CONTENT_LOADINVENTORY_H

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

		virtual void AddRef();
		virtual void Release();
	};

	class LoadInventory : public LoadObject
	{
	public:
		// The filter of a lookup: answers the object as T, or null (one virtual slot)
		template<class T> class DynamicCaster
		{
		public:
			virtual core::IRefCount* Cast(core::IRefCount* object)
			{
				return dynamic_cast<T*>(object);
			}
		};

		// 0x106033D0: capacity is the size of the name table (a power of two)
		explicit LoadInventory(unsigned int capacity);

		// Vftable slots 0 / 1 (0x105FE740 / 0x105FE750)
		virtual void AddRef();
		virtual void Release();

		// 0x106032F0 / 0x10603560: adds an object under a name / takes it out again
		void Add(const ObjectName& name, LoadObject* object);
		bool Remove(LoadObject* object, bool unknown);

		int unknown4;
		bool unknown8;
		bool unknown9;
		// The name table (0x28 bytes)
		void* table;
		unsigned char unknown10[0x24 - 0x10];
	};

	// The root inventory (0x11283818)
	extern LoadInventory* gRootInventory;
}

#endif
