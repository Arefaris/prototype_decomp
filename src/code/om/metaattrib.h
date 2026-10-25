// The attribute reflection of the om library (RTTI: om::MetaAttribBase and the instances MetaAttrib<V>): a member of
// a reflected class that is read and written directly (at an offset inside the object), where properties go through
// accessor methods. V is the type of the member; the text and binary forms are the ones of the value type.
#ifndef OM_METAATTRIB_H
#define OM_METAATTRIB_H

#include "code/core/hash.h"
#include "code/om/allocation.h"
#include "code/om/metaproperty.h"
#include "code/om/metatype.h"
#include "code/om/string.h"
#include "code/om/tree.h"

namespace om
{
	class MetaClassBase;

	class MetaAttribBase
	{
	public:
		// 0x10AADD80: keeps the offset and the name and enters the attribute in the tree of its class
		MetaAttribBase(MetaClassBase* owner, const ClassName& newName, unsigned int newOffset);
		// Slot 0 (the deleting destructor is 0x108C8E20)
		virtual ~MetaAttribBase()
		{
		}
		virtual bool ReadText(const TextValue* text, void* object) = 0;
		virtual void WriteText(TextValue* text, const void* object) = 0;
		virtual bool ReadBinary(BinaryStream* stream, void* object) = 0;
		virtual bool WriteBinary(BinaryStream* stream, const void* object) = 0;
		// Slot 5 (0x108C8E10): nothing
		virtual void Slot5(void* unknown)
		{
		}

		TreeNode node;  // 8: the vftable pointer takes 8 bytes
		unsigned int offset;  // 0x18
		int unknown1C;
		ClassName name;  // 0x20
	};

	// The forms of the value (looked up by the value's type: the functions of the namespace, or the arrays' own)
	template<class V> inline bool AttributeReadText(const TextValue* text, V* value)
	{
		return ReadText(text, value);
	}
	template<class V> inline void AttributeWriteText(TextValue* text, const V& value)
	{
		WriteText(text, value);
	}
	template<class V> inline bool AttributeReadBinary(BinaryStream* stream, V* value)
	{
		return ReadBinary(stream, value);
	}
	template<class V> inline bool AttributeWriteBinary(BinaryStream* stream, const V& value)
	{
		return WriteBinary(stream, value);
	}

	template<class V> class MetaAttrib : public MetaAttribBase
	{
	public:
		MetaAttrib(MetaClassBase* owner, const ClassName& newName, unsigned int newOffset) :
			MetaAttribBase(owner, newName, newOffset)
		{
		}
		virtual bool ReadText(const TextValue* text, void* object)
		{
			return AttributeReadText(text, reinterpret_cast<V*>(offset + static_cast<char*>(object)));
		}
		virtual void WriteText(TextValue* text, const void* object)
		{
			AttributeWriteText(text, *reinterpret_cast<const V*>(offset + static_cast<const char*>(object)));
		}
		virtual bool ReadBinary(BinaryStream* stream, void* object)
		{
			return AttributeReadBinary(stream, reinterpret_cast<V*>(offset + static_cast<char*>(object)));
		}
		virtual bool WriteBinary(BinaryStream* stream, const void* object)
		{
			return AttributeWriteBinary(stream, *reinterpret_cast<const V*>(offset + static_cast<const char*>(object)));
		}
		// The registration helper of the class's reflection: the attribute named by the text, at the offset (the
		// caller also passes the size of the member, which the helper does not use)
		static MetaAttrib* Create(MetaClassBase* owner, const char* text, unsigned int newOffset, unsigned int size);
		OM_ALLOCATION(MetaAttrib);
	};

	template<class V> const char* MetaAttrib<V>::AllocationTag()
	{
		return "";
	}

	template<class V> MetaAttrib<V>* MetaAttrib<V>::Create(MetaClassBase* owner, const char* text, unsigned int newOffset, unsigned int size)
	{
		return new MetaAttrib(owner, ClassName(core::Hash64(String(text, true).GetText(), 0)), newOffset);
	}
}

#endif
