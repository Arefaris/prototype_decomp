// content::MetaObjectTemplate (declared in code/engine/gameobject/gameobjectspawner.h; unit 0x10606A10 - 0x10606BB0):
// the template of a game object, an object of its factory's class that is copied into every new game object.
#include "code/content/metafactory.h"
#include "code/content/metatype.h"
#include "code/core/heap.h"
#include "code/engine/gameobject/gameobjectspawner.h"

namespace content
{
	// 0x10445BE0 (slot 6)
	void MetaObjectTemplate::SetName(const ObjectName& newName)
	{
		name = newName;
	}

	// 0x104452D0 / 0x104452E0 (slots 7 and 8; the engine's copies lie in the unit of the properties class, whose
	// functions of the same code they are)
	void* MetaObjectTemplate::Slot7()
	{
		return object;
	}

	void MetaObjectTemplate::Slot8(void* newObject)
	{
		object = newObject;
	}

	// FUNCTION: ENGINE 0x10606A40
	void MetaObjectTemplate::Slot10(MetaObjectFactoryBase* newFactory)
	{
		factory = newFactory;
	}

	// FUNCTION: ENGINE 0x10606A50
	MetaObjectFactoryBase* MetaObjectTemplate::GetFactory()
	{
		return factory;
	}

	// FUNCTION: ENGINE 0x10606A60
	engine::GameObject* MetaObjectTemplate::Create(int heap, LoadInventory* inventory, const ObjectName& newName, bool flag)
	{
		core::IRefCount* created;
		MetaLoadObject* meta;
		{
			core::HeapScope scope(heap);
			core::GetHeapAllocator(heap);
			created = factory->Create();
			meta = dynamic_cast<MetaLoadObject*>(created);
			if (meta != 0)
			{
				meta->SetName(newName);
			}
			((MetaTypeView*)factory->type)->Copy(created, object, 1);
			if (meta != 0)
			{
				meta->Slot5();
			}
		}
		if (flag)
		{
			core::HeapScope again(heap);
			LoadObject* loaded = dynamic_cast<LoadObject*>(created);
			if (loaded != 0)
			{
				loaded->Slot3((int)inventory);
			}
		}
		return (engine::GameObject*)created;
	}

	// FUNCTION: ENGINE 0x10606B30
	MetaObjectTemplate::~MetaObjectTemplate()
	{
		if (object != 0)
		{
			((MetaTypeView*)factory->type)->Destroy(object);
		}
	}

	// FUNCTION: ENGINE 0x10606B60
	// EQUIVALENT: scheduling, the engine loads the address of the name behind the first vftable store
	MetaObjectTemplate::MetaObjectTemplate() :
		factory(0),
		object(0)
	{
	}
}

// Kept copies (compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10606B90
