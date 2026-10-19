// pure3d::RefCounted and pure3d::Entity (RTTI names; the bases of DeferredDeletionProxy are "pure3d::Entity;
// pure3d::RefCounted; core::IRefCount"). RefCounted keeps an interlocked reference count after the interface pointer
// and allocates through operator new[] / delete (0x106E2930 / 0x106E2910); Entity adds a name. Only what the engine's
// render units need so far; all of it is in other units (pure3d).
#ifndef PURE3D_ENTITY_H
#define PURE3D_ENTITY_H

#include "code/core/memory/imemoryallocator.h"
#include "code/core/name.h"

// The compiler barrier (the full <intrin.h> would also change the register conventions of the unit-local functions)
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

namespace pure3d
{
	class RefCounted : public core::IRefCount
	{
	public:
		// The inlined count initialisation also ends the scheduling region there: the derived constructors load their
		// constants (the second shared register) only after the count store, as the engine's do
		RefCounted()
		{
			mRefCount = 0;
			_ReadWriteBarrier();
		}
		// 0x106E2930 / 0x106E2910
		static void* operator new(unsigned int size);
		static void operator delete(void* block);

		// 0x106E2A00 / 0x106E2A10 (Release deletes the object when the count drops below 1)
		virtual void AddRef();
		virtual void Release();

		// Reference-counted pointer helpers (instantiated in the units that use them first): Assign takes a
		// reference to the new object, releases the old one and stores the new one; Release releases and clears
		template<class T> static void Assign(T*& pointer, T* object);
		template<class T> static void Release(T*& pointer);

		volatile int mRefCount;
	};

	class Entity : public RefCounted
	{
	public:
		// 0x1072D4B0 / 0x1072D4E0
		Entity();
		virtual ~Entity();
		// 0x1072D4F0: assigns the name
		void SetName(const core::Name<core::CaseSensitiveKey>& name);
		// 0x1072D520: the name of the given text
		void SetNameText(const char* text);
		// 0x1072D500: copies the name of another entity (nothing for a null one)
		void SetNameFrom(const Entity* other);
		// 0x1072D530: the name's 64-bit hash
		void SetName(unsigned __int64 name);

		core::Name<core::CaseSensitiveKey> mName;
	};
}

#endif
