// The entity that wraps a dynamic object (RTTI: om::DynamicObjectEntity, 0x48 bytes): the dynamic object sits inside
// it and the entity forwards its reading and writing and its property functions to it.
#ifndef OM_DYNAMICOBJECTENTITY_H
#define OM_DYNAMICOBJECTENTITY_H

#include "code/om/dynamicobject.h"
#include "code/om/entity.h"

namespace om
{
	class DynamicObjectEntity : public Entity
	{
	public:
		// 0x105C1D10
		explicit DynamicObjectEntity(const ClassName& newName);
		// Slot 0 (0x105C1B70 is the body, the deleting destructor 0x105C1D50)
		virtual ~DynamicObjectEntity();
		// Slots 3, 4, 6 and 7 (0x105C1C00 - 0x105C1C30) read and write the object as text and in binary form
		virtual bool Slot3(void* argument);
		virtual void Slot4(void* argument);
		virtual bool Slot6(void* argument);
		virtual bool Slot7(void* argument);
		// Slot 9 (0x105C1E70)
		virtual EntityTypeBase* GetEntityType();
		OM_ENTITY_ALLOCATION(DynamicObjectEntity);

		// The functions of the object that the entity forwards (0x105C1BB0 - 0x105C1BF0, 0x105C1D80, 0x105C1DA0)
		DynamicPropertyBase* GetFirstProperty();
		DynamicPropertyBase* GetNextProperty(DynamicPropertyBase* property);
		unsigned int GetPropertyCount();
		void AddProperty(DynamicPropertyBase* property);
		void RemoveProperty(DynamicPropertyBase* property);
		DynamicPropertyBase* FindProperty(ClassName propertyName);
		DynamicPropertyBase* CreateProperty(ClassName propertyName, MetaTypeBase* type);
		// The property of a name that holds a value of the type, null when there is none (name guessed)
		template<class T> DynamicProperty<T>* FindTypedProperty(ClassName propertyName)
		{
			return object.FindTypedProperty<T>(propertyName);
		}

		DynamicObject object;  // 0x20
	};
}

#endif
