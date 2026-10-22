// The entities of the om library (RTTI: om::Entity, om::EntityTypeBase and om::EntityType<T>): reference counted objects
// with a name that are created by the entity type of their class; every entity type registers itself under its class
// name and its type_info. Only what the entity types of audio::Mix, music::Cue and om::DynamicObjectEntity need is
// described so far.
#ifndef OM_ENTITY_H
#define OM_ENTITY_H

#include "code/om/allocation.h"
#include "code/om/metatype.h"
#include "code/om/name.h"
#include "code/om/metaclass.h"
#include "code/om/refcount.h"
#include "code/om/string.h"
#include "code/core/hash.h"
#include <typeinfo>

// The engine's typeid(...).name() calls the library's _name_internal_method; this toolchain's header declares name() as an
// export of its own, which the import library does not have
#pragma comment(linker, "/alternatename:__imp_?name@type_info@@QBEPBDPAU__type_info_node@@@Z=__imp_?_name_internal_method@type_info@@QBEPBDPAU__type_info_node@@@Z")

namespace om
{
	class Entity : public RefCount<ThreadSafeRefCount>
	{
	public:
		// 0x105B5210
		explicit Entity(const ClassName& newName);

		ClassName name;  // 8
	};

	// 0x105B5B60: puts a new entity into the registry of the entities (name guessed)
	void RegisterEntity(Entity* entity);

	// The description of an entity class (RTTI: om::EntityTypeBase); the registries are keyed by name and by type_info
	class EntityTypeBase
	{
	public:
		// 0x105B5590
		EntityTypeBase(const char* newName, unsigned int newSize, unsigned int newAlignment, const type_info* newType,
			bool newFlag);
		// 0x105B55E0 is the body; the deleting destructor 0x105B59F0
		virtual ~EntityTypeBase();
		// Slot 1: a new entity of the class (counted once, in the registry)
		virtual void CreateEntity(Entity** entity, const ClassName& name) = 0;
		// Slot 2: the reflection of the class
		virtual MetaTypeBase* GetMetaType() = 0;
		// Slot 3 (0x105B4AD0): reads an entity from a stream
		virtual void ReadEntity(const void* stream, const ClassName& name, void* result);
		// Slot 4
		virtual void CreateUnregisteredEntity(Entity** entity, const ClassName& name) = 0;

		const char* name;  // 4
		unsigned int size;  // 8
		unsigned int alignment;  // 0xC
		bool flag;  // 0x10
		const type_info* type;  // 0x14
		bool registered;  // 0x18
		TreeNode nodeByName;  // 0x1C
		char unknown2C[0x10];
		TreeNode nodeByType;  // 0x3C
	};

	// The new and delete of an entity class: the allocation is tagged with the name of the class
#define OM_ENTITY_ALLOCATION(Type) \
	static void* operator new(size_t) \
	{ \
		return om::Allocate(typeid(Type).name(), sizeof(Type), __alignof(Type)); \
	} \
	static void operator delete(void* memory) \
	{ \
		om::Release(memory, sizeof(Type), __alignof(Type)); \
	}

	// The entity type of the class T (RTTI: om::EntityType<T>, 0x4C bytes): T has a constructor taking the name
	template<class T> class EntityType : public EntityTypeBase
	{
	public:
		EntityType(const char* newName, unsigned int newSize, unsigned int newAlignment, bool newFlag);
		virtual ~EntityType();
		virtual void CreateEntity(Entity** entity, const ClassName& name);
		virtual MetaTypeBase* GetMetaType();
		virtual void CreateUnregisteredEntity(Entity** entity, const ClassName& name);
		// Slot 5 does the same as slot 4
		virtual void CreateUnregisteredEntity2(Entity** entity, const ClassName& name);
		OM_ALLOCATION(EntityType);

		// Lets go of the reflection of T that the instances share
		static void ReleaseMetaType();
		// Creates the entity type of the class (new EntityType(name, sizeof(T), alignment, true))
		static void Register(const char* newName, bool newFlag);
	};

	template<class T> EntityType<T>::EntityType(const char* newName, unsigned int newSize, unsigned int newAlignment,
		bool newFlag) :
		EntityTypeBase(newName, newSize, newAlignment, &typeid(T), newFlag)
	{
		String text(newName, true);
		ClassName className(core::Hash64(text.GetText(), 0));
		MetaClass<T>::Create(className, 0);
	}

	template<class T> EntityType<T>::~EntityType()
	{
		ReleaseMetaType();
	}

	template<class T> const char* EntityType<T>::AllocationTag()
	{
		return "";
	}

	template<class T> MetaTypeBase* EntityType<T>::GetMetaType()
	{
		MetaTypeBase*& cache = MetaTypeCache<T>::type;
		if (cache == 0)
		{
			cache = FindMetaType(typeid(T));
		}
		return cache;
	}

	template<class T> void EntityType<T>::CreateEntity(Entity** entity, const ClassName& name)
	{
		T* created = new T(name);
		*entity = created;
		ThreadSafeRefCount::AddRef(&created->count);
		RegisterEntity(*entity);
	}

	template<class T> void EntityType<T>::CreateUnregisteredEntity(Entity** entity, const ClassName& name)
	{
		T* created = new T(name);
		*entity = created;
		ThreadSafeRefCount::AddRef(&created->count);
	}

	template<class T> void EntityType<T>::CreateUnregisteredEntity2(Entity** entity, const ClassName& name)
	{
		T* created = new T(name);
		*entity = created;
		ThreadSafeRefCount::AddRef(&created->count);
	}

	template<class T> inline void EntityType<T>::ReleaseMetaType()
	{
		MetaTypeBase*& cache = MetaTypeCache<T>::type;
		if (cache == 0)
		{
			cache = FindMetaType(typeid(T));
		}
		MetaTypeBase* type = cache;
		if (ThreadSafeRefCount::Release(&cache->count) == 0 && type != 0)
		{
			delete type;
		}
		cache = 0;
	}

	template<class T> void EntityType<T>::Register(const char* newName, bool newFlag)
	{
		new EntityType(newName, sizeof(T), __alignof(T), newFlag);
	}
}

#endif
