// content::MetaLoader, MetaObjectFactoryBase and MetaInstanceCreator: what the content library loads a reflected class
// through, and the library's maps of them (unit 0x105FF6A0 - 0x105FFD60; the file name is guessed).
#include "code/content/metafactory.h"
#include "code/content/metastream.h"
#include "code/core/hash.h"
#include "code/core/heap.h"
#include "code/engine/gameobject/gameobjectspawner.h"

namespace content
{
	// The library's map of loaders by the hash of their name: the same code as proto::MidgroundMap, which the linker
	// merged (0x102DD6F0 / 0x102DDAD0; names guessed)
	class LoaderMap
	{
	public:
		struct Iterator
		{
			explicit Iterator(LoaderMap* newMap)
			{
				map = newMap;
				key = 0;
				index = 0;
				current = 0;
				step = 0;
			}

			// The value the key is stored under, null when the map has no such key
			void* Find(const unsigned __int64& newKey);

			LoaderMap* map;
			int unknown4;
			unsigned __int64 key;
			int index;
			int current;
			int step;
		};

		// Stores the value under the key (the key is copied)
		void Insert(const unsigned __int64& key, void* value);
	};

	// The factories and the creators of the library (0x11276948; names guessed)
	struct LoaderMaps
	{
		LoaderMap* factories;
		LoaderMap* creators;
	};

	extern LoaderMaps* gLoaderMaps;

	// FUNCTION: ENGINE 0x105FF6A0
	MetaLoader::MetaLoader(const char* newName, unsigned short newFlag)
	{
		name = newName;
		flag = newFlag;
	}

	// FUNCTION: ENGINE 0x105FF6C0
	MetaInstanceCreator::MetaInstanceCreator(const char* newName, unsigned short newFlag, ClassMetaType* newType)
	{
		name = newName;
		flag = newFlag;
		type = newType;
	}

	// FUNCTION: ENGINE 0x105FF710
	MetaObjectFactoryBase::MetaObjectFactoryBase(const char* newName, unsigned short newFlag, ClassMetaType* newType)
		: MetaLoader(newName, newFlag)
	{
		type = newType;
	}

	// FUNCTION: ENGINE 0x105FF740
	void* MetaObjectFactoryBase::Slot1(int heap, ReadContext* context, LoadInventory* inventory, const ObjectName* name,
		bool wrapped)
	{
		int previous = core::SetCurrentHeap(heap);
		MetaObjectTemplate* tmpl = 0;
		core::IRefCount* object;
		if (!wrapped)
		{
			object = Create();
		}
		else
		{
			tmpl = new MetaObjectTemplate();
			tmpl->Slot8(((MetaTypeView*)type)->Create());
			tmpl->Slot10(this);
			object = tmpl;
		}
		MetaLoadObject* loadObject = dynamic_cast<MetaLoadObject*>(object);
		if (loadObject != 0)
		{
			loadObject->SetName(*name);
		}
		if (!wrapped)
		{
			((MetaTypeView*)type)->ReadBinary(context, object, (int)inventory, 1);
		}
		else
		{
			((MetaTypeView*)type)->ReadBinary(context, tmpl->Slot7(), (int)inventory, 1);
		}
		loadObject = dynamic_cast<MetaLoadObject*>(object);
		if (loadObject != 0 && !loadObject->Slot5())
		{
			object->AddRef();
			object->Release();
			object = 0;
		}
		core::SetCurrentHeap(previous);
		return object;
	}

	// FUNCTION: ENGINE 0x105FF860
	void* MetaObjectFactoryBase::Slot0(int heap, TextReadStream* reader, LoadInventory* inventory,
		const ObjectName* name, bool wrapped, bool* failed)
	{
		int previous = core::SetCurrentHeap(heap);
		MetaObjectTemplate* tmpl = 0;
		core::IRefCount* object;
		if (!wrapped)
		{
			object = Create();
		}
		else
		{
			tmpl = new MetaObjectTemplate();
			tmpl->Slot8(((MetaTypeView*)type)->Create());
			tmpl->Slot10(this);
			object = tmpl;
		}
		MetaLoadObject* loadObject = dynamic_cast<MetaLoadObject*>(object);
		if (loadObject != 0)
		{
			loadObject->SetName(*name);
		}
		bool read;
		if (!wrapped)
		{
			read = ((MetaTypeView*)type)->ReadText(reader, object, (int)inventory, 1);
		}
		else
		{
			read = ((MetaTypeView*)type)->ReadText(reader, tmpl->Slot7(), (int)inventory, 1);
		}
		if (!read)
		{
			object->AddRef();
			object->Release();
			object = 0;
			*failed = true;
		}
		loadObject = dynamic_cast<MetaLoadObject*>(object);
		if (loadObject != 0 && !loadObject->Slot5())
		{
			object->AddRef();
			object->Release();
			object = 0;
		}
		core::SetCurrentHeap(previous);
		return object;
	}

	// FUNCTION: ENGINE 0x105FFC40
	// EQUIVALENT: scheduling: the engine stores the high word of the key and loads the map before the zero stores of the iterator, ours stores the key after them (67.5 %)
	MetaObjectFactoryBase* FindObjectFactory(const char* name, unsigned short flag)
	{
		unsigned __int64 key = core::Hash64(name, flag);
		LoaderMap::Iterator iterator(gLoaderMaps->factories);
		return (MetaObjectFactoryBase*)iterator.Find(key);
	}

	// FUNCTION: ENGINE 0x105FFCA0
	// EQUIVALENT: scheduling: the engine stores the high word of the key and loads the map before the zero stores of the iterator, ours stores the key after them (70.2 %)
	MetaInstanceCreator* FindInstanceCreator(const char* name, unsigned short flag)
	{
		unsigned __int64 key = core::Hash64(name, flag);
		LoaderMap::Iterator iterator(gLoaderMaps->creators);
		return (MetaInstanceCreator*)iterator.Find(key);
	}

	// FUNCTION: ENGINE 0x105FFD20
	// EQUIVALENT: scheduling: the engine stores the low word of the key after loading the map, ours before it (88.1 %)
	void RegisterObjectFactory(MetaObjectFactoryBase* factory)
	{
		unsigned __int64 key = core::Hash64(factory->name, factory->flag);
		LoaderMap* map = gLoaderMaps->factories;
		map->Insert(key, factory);
	}

	// FUNCTION: ENGINE 0x105FFD60
	// EQUIVALENT: scheduling: the engine stores the low word of the key after loading the map, ours before it (86.7 %)
	void RegisterInstanceCreator(MetaInstanceCreator* creator)
	{
		unsigned __int64 key = core::Hash64(creator->name, creator->flag);
		gLoaderMaps->creators->Insert(key, creator);
	}
}
