// The patch of the mgraph library (0x105B9380 - 0x105BA570) and the reflection and entity type that the om library's
// templates make for it.
#include "code/mgraph/patch.h"
#include "code/mgraph/graph.h"
#include "code/om/metaproperty.h"
#include "code/om/metaenum.h"
#include "code/om/dynamicobject.h"
#include "code/om/metaclass.h"
#include "code/om/reflection.h"

namespace mgraph
{
#ifdef NONMATCHING
	// Reads the name of a property and, when a length follows, passes over the data of the property that many bytes
	// on (the engine's copy of it, 0x105B9600, is called by other units)
	static inline bool ReadPropertyHeader(om::BinaryStream* stream, unsigned __int64* key, bool* skipped)
	{
		*skipped = false;
		om::StreamBuffer* keyBuffer = stream->buffer;
		if (keyBuffer->Read(key, 8))
		{
			unsigned char hasLength;
			om::StreamBuffer* flagBuffer = stream->buffer;
			bool read = flagBuffer->Read(&hasLength, 1);
			bool skip = hasLength != 0;
			if (skip)
			{
				unsigned int length;
				unsigned int position;
				om::ReadBinary(stream, &length);
				stream->buffer->stream->GetPosition(&position);
				stream->buffer->stream->Seek(position + length + 1);
			}
		}
		return true;
	}
#endif

	// FUNCTION: ENGINE 0x105B9540
	Patch::Patch(const om::ClassName& newName) :
		DynamicObjectEntity(newName),
		graphName(),
		isSingleton(false)
	{
	}

	// FUNCTION: ENGINE 0x105B9380
	Patch::~Patch()
	{
	}

	// FUNCTION: ENGINE 0x105B9740
	Graph* FindGraph(const om::ClassName& graphName)
	{
		om::Entity* entity = om::FindEntityByName(graphName);
		while (entity != 0)
		{
			if (entity->name.key != graphName.key)
			{
				return 0;
			}
			Graph* graph = dynamic_cast<Graph*>(entity);
			if (graph != 0)
			{
				return graph;
			}
			entity = om::GetNextEntity(entity);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105BA0B0
	void Patch::SetGraphName(om::ClassName newGraphName)
	{
		UpdateFromGraph(FindGraph(newGraphName));
		graphName = newGraphName;
	}

	// FUNCTION: ENGINE 0x105B9CD0
	bool Patch::Slot7(void* argument)
	{
		om::BinaryStream* stream = static_cast<om::BinaryStream*>(argument);
		bool result;
		if (om::WriteBinary(stream, GetGraphName()))
		{
			bool singleton = isSingleton ? true : false;
			om::StreamBuffer* buffer = stream->buffer;
			result = buffer->Write(&singleton, 1) && om::WriteBinary(stream, GetPropertyCount());
		}
		else
		{
			result = false;
		}
		om::DynamicPropertyBase* property = GetFirstProperty();
		while (property != 0)
		{
			if (result && property->WriteBinary(stream))
			{
				result = true;
			}
			else
			{
				result = false;
			}
			property = GetNextProperty(property);
		}
		return result;
	}

	// FUNCTION: ENGINE 0x105B9D70
	bool Patch::Slot8(void* argument)
	{
		Graph* graph = FindGraph(graphName);
		if (graph != 0)
		{
			UpdateFromGraph(graph);
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105B9860
	void Patch::Slot4(void* argument)
	{
		om::TextValue* text = static_cast<om::TextValue*>(argument);
		new om::TextNode(text, om::String::Wrap("GraphName"));
		om::TextNode* singletonNode = new om::TextNode(text, om::String::Wrap("IsSingleton"));
		om::WriteText(singletonNode, isSingleton);
		om::TextValue* node = new om::TextNode(text, om::String::Wrap("Properties"));
		om::DynamicPropertyBase* property = GetFirstProperty();
		while (property != 0)
		{
			property->WriteText(node);
			property = GetNextProperty(property);
		}
	}

	// FUNCTION: ENGINE 0x105BA370
	// NONMATCHING: the engine loads the stream buffer before pushing the arguments of the second read and tests its flag through a bool (40.7 %)
#ifdef NONMATCHING
	bool Patch::Slot6(void* argument)
	{
		om::BinaryStream* stream = static_cast<om::BinaryStream*>(argument);
		bool result;
		unsigned int count;
		if (om::ReadBinary(stream, &graphName))
		{
			unsigned char singleton;
			om::StreamBuffer* buffer = stream->buffer;
			bool read = buffer->Read(&singleton, 1);
			isSingleton = singleton != 0;
			result = read && om::ReadBinary(stream, &count);
		}
		else
		{
			result = false;
		}
		for (unsigned int i = 0; i < count; i++)
		{
			unsigned __int64 key;
			bool skipped;
			ReadPropertyHeader(stream, &key, &skipped);
			om::ClassName propertyName(key);
			om::FactoryBase<om::DynamicPropertyBase>* factory = om::gPropertyFactories->Find(propertyName);
			if (factory == 0)
			{
				return false;
			}
			om::DynamicPropertyBase* property = factory->Create(0);
			if (result && property->ReadBinary(stream))
			{
				result = true;
			}
			else
			{
				result = false;
			}
			om::DynamicPropertyBase* existing = FindProperty(property->GetName());
			if (existing != 0)
			{
				existing->SetFrom(property);
				delete property;
			}
			else
			{
				AddProperty(property);
			}
		}
		return result;
	}
#endif

	// FUNCTION: ENGINE 0x105B93B0
	const om::ClassName& Patch::GetGraphName() const
	{
		return graphName;
	}

	// FUNCTION: ENGINE 0x105B93C0
	bool Patch::GetIsSingleton() const
	{
		return isSingleton;
	}

	// FUNCTION: ENGINE 0x105B93D0
	void Patch::SetIsSingleton(bool newIsSingleton)
	{
		isSingleton = newIsSingleton;
	}

	// FUNCTION: ENGINE 0x105B9820
	om::EntityTypeBase* Patch::GetEntityType()
	{
		return om::FindEntityType(typeid(Patch));
	}
}

namespace om
{
	// FUNCTION: ENGINE 0x105B93E0
	template MetaClass<mgraph::Patch>::MetaClass(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105B9410
	template const type_info* MetaClass<mgraph::Patch>::GetType();
	// FUNCTION: ENGINE 0x105B9440
	template MetaClass<mgraph::Patch>::~MetaClass();
	// FUNCTION: ENGINE 0x105B9450
	template void MetaClass<mgraph::Patch>::operator delete(void*);
	// FUNCTION: ENGINE 0x105B94E0
	template const char* MetaClass<mgraph::Patch>::AllocationTag();
	// FUNCTION: ENGINE 0x105B96A0
	template int MetaClass<mgraph::Patch>::Slot5();
	// FUNCTION: ENGINE 0x105B96B0
	template void MetaClass<mgraph::Patch>::Slot6(void*);
	// FUNCTION: ENGINE 0x105B96C0
	template void* MetaClass<mgraph::Patch>::operator new(size_t);

	// FUNCTION: ENGINE 0x105B99C0
	template void MetaClass<mgraph::Patch>::Create(const ClassName&, MetaClassBase*);

	// FUNCTION: ENGINE 0x105B94C0
	template const char* EntityType<mgraph::Patch>::AllocationTag();
	// FUNCTION: ENGINE 0x105B9680
	template void* EntityType<mgraph::Patch>::operator new(size_t);
	// FUNCTION: ENGINE 0x105B9DA0
	template EntityType<mgraph::Patch>::EntityType(const char*, unsigned int, unsigned int, int);
	// FUNCTION: ENGINE 0x105B9E50
	template void EntityType<mgraph::Patch>::operator delete(void*);
	// FUNCTION: ENGINE 0x105B9E90
	template MetaTypeBase* EntityType<mgraph::Patch>::GetMetaType();
	// FUNCTION: ENGINE 0x105B9EB0
	template void EntityType<mgraph::Patch>::CreateEntity(Entity**, const ClassName&);
	// FUNCTION: ENGINE 0x105B9F00
	template void EntityType<mgraph::Patch>::CreateUnregisteredEntity(Entity**, const ClassName&);
	// FUNCTION: ENGINE 0x105B9F60
	template void EntityType<mgraph::Patch>::CreateUnregisteredEntity2(Entity**, const ClassName&);
	// FUNCTION: ENGINE 0x105B9FC0
	// NONMATCHING: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
#ifdef NONMATCHING
	template void EntityType<mgraph::Patch>::ReleaseMetaType();
#endif
	// FUNCTION: ENGINE 0x105BA010
	template EntityType<mgraph::Patch>::~EntityType();
	// FUNCTION: ENGINE 0x105BA4F0
	template void EntityType<mgraph::Patch>::Register(const char*, int);
}
