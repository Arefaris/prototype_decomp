// The delegates and garbage holders of the om library (RTTI: om::DelegatePropertyBase,
// DelegateProperty<V>, DelegateMetaPropertyBase, DelegateMetaProperty<T>, GarbageBase and Garbage<V>). A delegate
// property binds a reflected property to one object, so that the value can be read and written without naming the
// object again; V is the value type of the property and T the type its accessors pass (V, or a const reference to V).
#ifndef OM_DELEGATE_H
#define OM_DELEGATE_H

#include "code/om/metaproperty.h"
#include "code/om/refcount.h"

namespace om
{
	class DelegatePropertyBase : public RefCount<SingleThreadedRefCount>
	{
	public:
		virtual ~DelegatePropertyBase()
		{
		}
		// Slot 1: the description of the value's type
		virtual MetaTypeBase* GetMetaType() = 0;
	};

	template<class V> class DelegateProperty : public DelegatePropertyBase
	{
	public:
		DelegateProperty()
		{
		}
		virtual ~DelegateProperty()
		{
		}
		virtual MetaTypeBase* GetMetaType()
		{
			return FindMetaType(typeid(V));
		}
		// Slots 2 and 3: the value of the bound object
		virtual V Get() = 0;
		virtual void Set(V value) = 0;
	};

	// The part of a bound property that does not depend on the value type (second base of DelegateMetaProperty)
	class DelegateMetaPropertyBase
	{
	public:
		virtual void SetObject(void* newObject)
		{
		}

		int unknown4;
		int unknown8;
		void* object;  // 0xC
		MetaPropertyBase* property;  // 0x10
	};

	template<class T> class DelegateMetaProperty : public DelegateProperty<typename PropertyValue<T>::Type>,
		public DelegateMetaPropertyBase
	{
	public:
		typedef typename PropertyValue<T>::Type Value;

		DelegateMetaProperty(void* newObject, MetaProperty<T>* newProperty)
		{
			object = newObject;
			property = newProperty;
		}
		virtual void SetObject(void* newObject)
		{
			object = newObject;
		}
		virtual Value Get()
		{
			return static_cast<MetaProperty<T>*>(property)->GetGetter()->Call(object);
		}
		virtual void Set(Value value)
		{
			static_cast<MetaProperty<T>*>(property)->GetSetter()->Call(object, value);
		}
		OM_ALLOCATION(DelegateMetaProperty);
	};

	template<class T> const char* DelegateMetaProperty<T>::AllocationTag()
	{
		return "";
	}

	template<class T> DelegatePropertyBase* MetaProperty<T>::CreateDelegate(void* object)
	{
		return new DelegateMetaProperty<T>(object, this);
	}

	class GarbageBase
	{
	public:
		virtual ~GarbageBase()
		{
		}

		int unknown4;
	};

	// A heap copy of a value that is deleted with the holder
	template<class V> class Garbage : public GarbageBase
	{
	public:
		Garbage(V* newValue) :
			value(newValue)
		{
		}
		virtual ~Garbage()
		{
			delete value;
		}
		OM_ALLOCATION(Garbage);

		V* value;  // 8
	};

	template<class V> const char* Garbage<V>::AllocationTag()
	{
		return "";
	}
}

#endif
