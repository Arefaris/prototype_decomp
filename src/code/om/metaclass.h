// The class reflection of the om library (RTTI: om::MetaClassBase, MetaClass<T>): the description of a reflected
// class with its properties, methods and attributes, registered under the class's name and its type_info. Slots 1 to
// 4 (text and binary forms) are the base's; the instances add the type (slot 7) and answer 5 and 6 with nothing.
#ifndef OM_METACLASS_H
#define OM_METACLASS_H

#include "code/om/allocation.h"
#include "code/om/metatype.h"

namespace om
{
	class MetaClassBase : public MetaTypeBase
	{
	public:
		// 0x105C0D80
		MetaClassBase(const ClassName& newName, const type_info* newType, MetaClassBase* newParent);
		// Slot 0 (0x105C0C60, the deleting destructor is 0x105C0DE0)
		virtual ~MetaClassBase();
		virtual bool ReadText(const TextValue* text, void* value);
		virtual void WriteText(TextValue* text, const void* value);
		virtual bool ReadBinary(BinaryStream* stream, void* value);
		virtual bool WriteBinary(BinaryStream* stream, const void* value);

		TreeHead attributes;  // 0x38
		TreeHead methods;  // 0x4C
		TreeHead properties;  // 0x60
		MetaClassBase* parent;  // 0x74
		TreeNode nodeByNameRegistry;  // 0x78
		TreeNode nodeByTypeRegistry;  // 0x88
	};

	template<class T> class MetaClass : public MetaClassBase
	{
	public:
		MetaClass(const ClassName& newName, MetaClassBase* newParent) :
			MetaClassBase(newName, &typeid(T), newParent)
		{
		}
		virtual int Slot5()
		{
			return 0;
		}
		virtual void Slot6(void* unknown)
		{
		}
		// Slot 7: the type
		virtual const type_info* GetType()
		{
			return &typeid(T);
		}
		// Makes the description of the class when there is none yet, and counts one more user of it
		static void Create(const ClassName& name, MetaClassBase* parent)
		{
			MetaTypeBase* type = FindMetaType(typeid(T));
			if (type == 0)
			{
				type = new MetaClass(name, parent);
			}
			ThreadSafeRefCount::AddRef(&type->count);
		}
		OM_ALLOCATION(MetaClass);
	};

	template<class T> const char* MetaClass<T>::AllocationTag()
	{
		return "";
	}
}

#endif
