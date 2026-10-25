// The content library's loader of an om entity (RTTI: om::AtgContentEntityLoader<T>, om::AtgContentEntityLoaderBase,
// om::AtgContentEntity<T> and om::AtgContentEntityBase, with content::ObjectLoader2 below the loader): the loader
// finds the entity type of T by its type_info and wraps the entities it reads in a load object that keeps one
// reference to the entity. The bases are in the library's unit (0x10AAC1D0 - 0x10AAD1xx); the templates' members are
// the engine's copies, one set per class.
#ifndef OM_ATGCONTENT_H
#define OM_ATGCONTENT_H

#include "code/content/loadinventory.h"
#include "code/om/entity.h"
#include <typeinfo>

namespace content
{
	// RTTI: content::ObjectLoader2 (a load object that loads objects; slot 5 is the loading)
	class ObjectLoader2 : public LoadObject
	{
	public:
		virtual void Load(void* object, void* name, void* source, void* unknown, void* inventory) = 0;
	};
}

namespace om
{
	// A counted reference to an entity (let go of with the object that holds it)
	struct EntityReference
	{
		~EntityReference()
		{
			if (entity != 0)
			{
				Entity* held = entity;
				entity = 0;
				if (ThreadSafeRefCount::Release(&held->count) == 0)
				{
					delete held;
				}
			}
		}

		Entity* entity;
	};

	// The load object that holds an entity (the entity is counted once for it); the destructors are implicit
	class AtgContentEntityBase : public content::LoadObject
	{
	public:
		// 0x10AAC670: counts the entity
		explicit AtgContentEntityBase(Entity* newEntity);
		// 0x10AAC220 / 0x10AAC200
		virtual void Slot3(int unused);
		virtual bool IsReady();
		OM_ALLOCATION(AtgContentEntityBase);

		EntityReference reference;  // 8
	};

	template<class T> class AtgContentEntity : public AtgContentEntityBase
	{
	public:
		explicit AtgContentEntity(Entity* newEntity) : AtgContentEntityBase(newEntity)
		{
		}
		OM_ALLOCATION(AtgContentEntity);
	};

	template<class T> const char* AtgContentEntity<T>::AllocationTag()
	{
		return "";
	}

	// The loader for one entity class
	class AtgContentEntityLoaderBase : public content::ObjectLoader2
	{
	public:
		// 0x10AAC3D0
		explicit AtgContentEntityLoaderBase(EntityTypeBase* newType);
		// 0x10AAC4C0: reads the entity from the chunk and wraps it
		virtual void Load(void* object, void* name, void* source, void* unknown, void* inventory);
		// Slot 6: wraps an entity of the class in a load object
		virtual AtgContentEntityBase* CreateContent(Entity* entity) = 0;

		EntityTypeBase* entityType;  // 8
	};

	template<class T> class AtgContentEntityLoader : public AtgContentEntityLoaderBase
	{
	public:
		AtgContentEntityLoader() : AtgContentEntityLoaderBase(FindEntityType(typeid(T)))
		{
		}
		virtual AtgContentEntityBase* CreateContent(Entity* entity)
		{
			return new AtgContentEntity<T>(entity);
		}
		OM_ALLOCATION(AtgContentEntityLoader);
	};

	template<class T> const char* AtgContentEntityLoader<T>::AllocationTag()
	{
		return "";
	}
}

#endif
