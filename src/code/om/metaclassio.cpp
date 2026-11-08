// The binary forms of a reflected class (0x105B6E10, 0x105B6EE0; the unit's file name is a guess): the class's parent
// first, then the attributes, then the properties that are stored.
#include "code/om/metaattrib.h"
#include "code/om/metaclass.h"
#include "code/om/metaproperty.h"

namespace om
{
	// FUNCTION: ENGINE 0x105B6850
	MetaAttribBase* MetaClassBase::GetFirstAttribute()
	{
		TreeNode* node = attributes.First();
		return node != 0 ? reinterpret_cast<MetaAttribBase*>(reinterpret_cast<char*>(node) - 8) : 0;
	}

	// FUNCTION: ENGINE 0x105B6870
	MetaAttribBase* MetaClassBase::GetNextAttribute(MetaAttribBase* attribute)
	{
		TreeNode* node = attributes.Next(attribute != 0 ? &attribute->node : 0);
		return node != 0 ? reinterpret_cast<MetaAttribBase*>(reinterpret_cast<char*>(node) - 8) : 0;
	}

	// FUNCTION: ENGINE 0x105B68A0
	MetaPropertyBase* MetaClassBase::GetFirstProperty()
	{
		TreeNode* node = properties.First();
		return node != 0 ? reinterpret_cast<MetaPropertyBase*>(reinterpret_cast<char*>(node) - 8) : 0;
	}

	// FUNCTION: ENGINE 0x105B68C0
	MetaPropertyBase* MetaClassBase::GetNextProperty(MetaPropertyBase* property)
	{
		TreeNode* node = properties.Next(property != 0 ? &property->node : 0);
		return node != 0 ? reinterpret_cast<MetaPropertyBase*>(reinterpret_cast<char*>(node) - 8) : 0;
	}

	// FUNCTION: ENGINE 0x105B6E10
	// NONMATCHING: the engine does not thread the jump over the null case of a tree node's owner and keeps ebx for the true result (24.5 %)
#ifdef NONMATCHING
	bool MetaClassBase::ReadBinary(BinaryStream* stream, void* value)
	{
		if (parent != 0 && !parent->ReadBinary(stream, value))
		{
			return false;
		}
		TreeNode* node = attributes.First();
		MetaAttribBase* attribute = node != 0 ? (MetaAttribBase*)((char*)node - 8) : 0;
		while (attribute != 0)
		{
			if (!attribute->ReadBinary(stream, value))
			{
				return false;
			}
			node = attributes.Next(&attribute->node);
			attribute = node != 0 ? (MetaAttribBase*)((char*)node - 8) : 0;
		}
		node = properties.First();
		MetaPropertyBase* property = node != 0 ? (MetaPropertyBase*)((char*)node - 8) : 0;
		while (property != 0)
		{
			if ((property->flags & 1) != 0 && !property->SetBinary(stream, value))
			{
				return false;
			}
			node = properties.Next(&property->node);
			property = node != 0 ? (MetaPropertyBase*)((char*)node - 8) : 0;
		}
		return true;
	}
#endif

	// FUNCTION: ENGINE 0x105B6EE0
	// NONMATCHING: the engine does not thread the jump over the null case of a tree node's owner and keeps ebx for the true result (24.5 %)
#ifdef NONMATCHING
	bool MetaClassBase::WriteBinary(BinaryStream* stream, const void* value)
	{
		if (parent != 0 && !parent->WriteBinary(stream, value))
		{
			return false;
		}
		TreeNode* node = attributes.First();
		MetaAttribBase* attribute = node != 0 ? (MetaAttribBase*)((char*)node - 8) : 0;
		while (attribute != 0)
		{
			if (!attribute->WriteBinary(stream, value))
			{
				return false;
			}
			node = attributes.Next(&attribute->node);
			attribute = node != 0 ? (MetaAttribBase*)((char*)node - 8) : 0;
		}
		node = properties.First();
		MetaPropertyBase* property = node != 0 ? (MetaPropertyBase*)((char*)node - 8) : 0;
		while (property != 0)
		{
			if ((property->flags & 1) != 0 && !property->GetBinary(stream, (void*)value))
			{
				return false;
			}
			node = properties.Next(&property->node);
			property = node != 0 ? (MetaPropertyBase*)((char*)node - 8) : 0;
		}
		return true;
	}
#endif
}
