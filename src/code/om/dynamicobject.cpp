// The om library's dynamic object (0x105C13B0 - 0x105C1B30).
#include "code/core/hash.h"
#include "code/om/dynamicobject.h"
#include "code/om/metaenum.h"

namespace om
{
	// FUNCTION: ENGINE 0x105C1290
	const char* PropertyFactories::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105C1660
	void PropertyFactories::Create()
	{
		gPropertyFactories = new PropertyFactories;
	}

	// FUNCTION: ENGINE 0x105C1770
	void PropertyFactories::Destroy()
	{
		delete gPropertyFactories;
		gPropertyFactories = 0;
	}

	// FUNCTION: ENGINE 0x105C13B0
	DynamicObject::DynamicObject(ClassName newName) :
		name(newName),
		className(0)
	{
	}

	// FUNCTION: ENGINE 0x105C1600
	DynamicPropertyBase* PropertyList::GetFirst()
	{
		if (head != 0)
		{
			return reinterpret_cast<DynamicPropertyBase*>(reinterpret_cast<char*>(head) - 4);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105C1840
	void PropertyList::DeleteAll()
	{
		DynamicPropertyBase* property = GetFirst();
		while (property != 0)
		{
			Remove(property != 0 ? &property->link : 0);
			if (property != 0)
			{
				delete property;
			}
			property = GetFirst();
		}
	}

	// FUNCTION: ENGINE 0x105C1880
	DynamicObject::~DynamicObject()
	{
		properties.DeleteAll();
	}

	// FUNCTION: ENGINE 0x105C1700
	void DynamicObject::AddProperty(DynamicPropertyBase* property)
	{
		FindProperty(property->GetName());
		GarbageLink* link = property == 0 ? 0 : &property->link;
		properties.Append(link);
	}

	// FUNCTION: ENGINE 0x105C17B0
	void DynamicObject::RemoveProperty(DynamicPropertyBase* property)
	{
		properties.Remove(property != 0 ? &property->link : 0);
		if (property != 0)
		{
			delete property;
		}
	}

	// FUNCTION: ENGINE 0x105C1400
	DynamicPropertyBase* DynamicObject::FindProperty(ClassName propertyName)
	{
		DynamicPropertyBase* property = GetFirstProperty();
		while (property != 0)
		{
			ClassName current = property->GetName();
			if (current.key == propertyName.key)
			{
				return property;
			}
			property = GetNextProperty(property);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105C16D0
	DynamicPropertyBase* DynamicObject::GetFirstProperty()
	{
		if (properties.head != 0)
		{
			return reinterpret_cast<DynamicPropertyBase*>(reinterpret_cast<char*>(properties.head) - 4);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105C16E0
	DynamicPropertyBase* DynamicObject::GetNextProperty(DynamicPropertyBase* property)
	{
		GarbageLink* link = property != 0 ? &property->link : 0;
		if (link->next != 0)
		{
			return reinterpret_cast<DynamicPropertyBase*>(reinterpret_cast<char*>(link->next) - 4);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105C1580
	ClassName DynamicObject::GetName() const
	{
		return name;
	}

	// FUNCTION: ENGINE 0x105C15A0
	void DynamicObject::SetName(ClassName newName)
	{
		name = newName;
	}

	// FUNCTION: ENGINE 0x105C1890
	DynamicPropertyBase* DynamicObject::CreateProperty(ClassName propertyName, MetaTypeBase* type)
	{
		PropertyFactories* factories = gPropertyFactories;
		DynamicPropertyBase* property = factories->Find(type->GetName())->Create(0);
		property->SetName(propertyName);
		FindProperty(propertyName);
		GarbageLink* link = property == 0 ? 0 : &property->link;
		properties.Append(link);
		return property;
	}

	// FUNCTION: ENGINE 0x105C1460
	unsigned int DynamicObject::GetPropertyCount()
	{
		return properties.Count();
	}

	// FUNCTION: ENGINE 0x105C1470
	bool DynamicObject::WriteBinary(BinaryStream* stream)
	{
		bool result = WriteInt(stream, properties.Count()) != 0;
		DynamicPropertyBase* property = GetFirstProperty();
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

	// FUNCTION: ENGINE 0x105C14E0
	void DynamicObject::WriteText(TextValue* text)
	{
		TextValue* node = new TextNode(text, String::Wrap("Properties"));
		DynamicPropertyBase* property = GetFirstProperty();
		while (property != 0)
		{
			property->WriteText(node);
			property = GetNextProperty(property);
		}
	}

	// FUNCTION: ENGINE 0x105C17E0
	bool DynamicObject::ReadBinary(BinaryStream* stream)
	{
		unsigned int count;
		if (om::ReadBinary(stream, &className))
		{
			om::ReadBinary(stream, &count);
		}
		if (count > 0)
		{
			String text;
			om::ReadBinary(stream, &text);
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105C1900
	// NONMATCHING: the engine keeps the keys of the first two lookups in the frame in the other order (65.6 %)
#ifdef NONMATCHING
	bool DynamicObject::ReadText(const TextValue* text)
	{
		bool result = true;
		TextValue* propertiesNode = text->FindChild("Properties");
		TextValue* classNameNode = text->FindChild("ClassName");
		if (classNameNode != 0)
		{
			om::ReadText(classNameNode, &className);
		}
		if (propertiesNode == 0)
		{
			return true;
		}
		TextValue* node = propertiesNode->FindChild("Property");
		while (node != 0 && node->text == String::Wrap("Property"))
		{
			TextValue* typeNode = node->FindChild("Type");
			if (typeNode != 0)
			{
				TextValue* first = typeNode->children.First();
				String typeName(first == 0 ? String::Wrap("") : first->text);
				const char* characters = typeName.data;
				if (characters == gEmptyStringData)
				{
					characters = "";
				}
				ClassName key(core::Hash64(characters, 0));
				FactoryBase<DynamicPropertyBase>* factory = gPropertyFactories->Find(key);
				if (factory != 0)
				{
					DynamicPropertyBase* property = factory->Create(0);
					if (result && property->ReadText(node))
					{
						result = true;
					}
					else
					{
						result = false;
					}
					properties.Append(property != 0 ? &property->link : 0);
				}
			}
			node = node->parent->children.Next(node);
		}
		return true;
	}
#endif
}
