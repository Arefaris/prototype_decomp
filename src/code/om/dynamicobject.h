// The dynamic object of the om library (RTTI: om::DynamicObject, 0x28 bytes): a list of dynamic properties with the
// name the object is known by and the name of the class it describes, read and written as text and in binary form.
// The dynamic object entity embeds one.
#ifndef OM_DYNAMICOBJECT_H
#define OM_DYNAMICOBJECT_H

#include "code/om/delegate.h"
#include "code/om/dynamicproperty.h"
#include "code/om/name.h"
#include "code/om/textvalue.h"

namespace om
{
	// The node of a doubly linked list (RTTI: om::DlListNode, a base of the dynamic object, eight bytes at offset 8)
	__declspec(align(8)) struct DlListNode
	{
		DlListNode* next;
		DlListNode* previous;
	};

	// The registry of the factories that make the dynamic properties, found by the name of the property's type
	// (0x28 bytes; names guessed)
	class PropertyFactories
	{
	public:
		// 0x105C1370 / 0x105C1390
		PropertyFactories()
		{
		}
		~PropertyFactories()
		{
		}
		// 0x105BA0A0: the factory registered under the name, null when there is none
		FactoryBase<DynamicPropertyBase>* Find(const ClassName& name);
		// 0x105C1660: makes the registry the engine uses; 0x105C1770 deletes it
		static void Create();
		static void Destroy();
		// 0x105C15C0 / 0x105C1220 / 0x105C1290
		static void* operator new(size_t)
		{
			return Allocate(AllocationTag(), sizeof(PropertyFactories), __alignof(PropertyFactories));
		}
		static void operator delete(void* memory)
		{
			Release(memory, sizeof(PropertyFactories), __alignof(PropertyFactories));
		}
		static const char* AllocationTag();

		TreeHead byName;
		TreeHead byType;
	};

	// 0x11276808 (name guessed)
	extern PropertyFactories* gPropertyFactories;

	// The properties of a dynamic object: the links of the properties sit four bytes into the property
	class PropertyList : public GarbageList
	{
	public:
		// 0x105CBE90
		unsigned int Count();
		// 0x105C1600
		DynamicPropertyBase* GetFirst();
		// 0x105C1840: deletes the properties one by one
		void DeleteAll();
	};

	class DynamicObject : public DlListNode
	{
	public:
		// 0x105C13B0
		DynamicObject(ClassName newName);
		// Slot 0 (0x105C1880 is the body, the deleting destructor 0x105C1B30)
		virtual ~DynamicObject();
		// Slot 1 (0x105C1700): takes the property into the list
		virtual void AddProperty(DynamicPropertyBase* property);
		// Slot 2 (0x105C1890): a new property of the type, known by the name
		virtual DynamicPropertyBase* CreateProperty(ClassName propertyName, MetaTypeBase* type);
		// Slot 3 (0x105C17B0): takes the property out of the list and deletes it
		virtual void RemoveProperty(DynamicPropertyBase* property);
		// Slot 4 (0x105C1400): the property known by the name, null when there is none
		virtual DynamicPropertyBase* FindProperty(ClassName propertyName);
		// Slot 5 and 6 (0x105C16D0 / 0x105C16E0)
		virtual DynamicPropertyBase* GetFirstProperty();
		virtual DynamicPropertyBase* GetNextProperty(DynamicPropertyBase* property);
		// Slot 7 (0x105C1460)
		virtual unsigned int GetPropertyCount();
		// Slot 8 and 9 (0x105C1580 / 0x105C15A0)
		virtual ClassName GetName() const;
		virtual void SetName(ClassName newName);
		// Slots 10 to 13 (0x105C1900, 0x105C14E0, 0x105C17E0, 0x105C1470)
		virtual bool ReadText(const TextValue* text);
		virtual void WriteText(TextValue* text);
		virtual bool ReadBinary(BinaryStream* stream);
		virtual bool WriteBinary(BinaryStream* stream);
		OM_ALLOCATION(DynamicObject);

		ClassName name;  // 0x10
		PropertyList properties;  // 0x18
		ClassName className;  // 0x20
	};
}

#endif
