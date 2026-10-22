// The property reflection of the om library (RTTI: om::MetaPropertyBase and the instances MetaProperty<T>): a
// reflected value of a class that is read and written through a getter and a setter command. T is the type the
// accessors pass: the value itself for numbers and booleans, a const reference for classes and enumerations.
// Slots 2 and 3 convert the value from and to text, 4 and 5 read and write it in binary form, 6 makes the
// delegate that binds the property to an object.
#ifndef OM_METAPROPERTY_H
#define OM_METAPROPERTY_H

#include "code/om/allocation.h"
#include "code/om/metamethod.h"
#include "code/om/metatype.h"

namespace om
{
	// The accessors a property calls: the object and the value in, or the object in and the value out (slot 2)
	class PropertyAccessor
	{
	public:
		virtual ~PropertyAccessor();
		virtual void Slot1() = 0;
	};

	template<class T> class PropertySetter : public PropertyAccessor
	{
	public:
		virtual void Invoke(void* object, T value) = 0;
	};

	template<class T> class PropertyGetter : public PropertyAccessor
	{
	public:
		virtual T Invoke(void* object) = 0;
	};

	// The value a parameter type stands for (the type itself, or what a const reference refers to)
	template<class T> struct PropertyValue
	{
		typedef T Type;
	};
	template<class T> struct PropertyValue<const T&>
	{
		typedef T Type;
	};

	class DelegatePropertyBase;

	class MetaPropertyBase
	{
	public:
		// 0x105E43D0: keeps the arguments and enters the property in the tree of its class
		MetaPropertyBase(MetaTypeBase* newValueType, MetaClassBase* newOwner, const ClassName& newName, PropertyAccessor* newSetter,
			PropertyAccessor* newGetter, unsigned int newFlags);
		virtual ~MetaPropertyBase()
		{
		}
		// Slot 1: the type of the value
		virtual const type_info* GetValueType() = 0;
		virtual bool SetText(const TextValue* text, void* object) = 0;
		virtual void GetText(TextValue* text, void* object) = 0;
		virtual bool SetBinary(BinaryStream* stream, void* object) = 0;
		virtual void GetBinary(BinaryStream* stream, void* object) = 0;
		virtual DelegatePropertyBase* CreateDelegate(void* object) = 0;

		TreeNode node;  // 8
		ClassName name;  // 0x18
		PropertyAccessor* setter;  // 0x20
		PropertyAccessor* getter;  // 0x24
		MetaTypeBase* valueType;  // 0x28
		MetaClassBase* owner;  // 0x2C
		unsigned int flags;  // 0x30
	};

	// The text and binary forms of the values the properties of the engine use (another unit, names guessed)
	bool ReadText(const TextValue* text, unsigned int* value);
	void WriteText(TextValue* text, unsigned int value);
	bool ReadBinary(BinaryStream* stream, unsigned int* value);
	void WriteBinary(BinaryStream* stream, unsigned int value);
	bool ReadText(const TextValue* text, float* value);
	void WriteText(TextValue* text, float value);
	bool ReadBinary(BinaryStream* stream, float* value);
	void WriteBinary(BinaryStream* stream, float value);
	bool ReadText(const TextValue* text, bool* value);
	void WriteText(TextValue* text, bool value);
	// A boolean is a byte in the stream, read and written in place
	inline bool ReadBinary(BinaryStream* stream, bool* value)
	{
		unsigned char byte;
		bool ok = stream->buffer->Read(&byte, 1);
		*value = byte != 0;
		return ok;
	}
	inline void WriteBinary(BinaryStream* stream, bool value)
	{
		unsigned char byte = value;
		stream->buffer->Write(&byte, 1);
	}

	// Names are written as text by their own description only, never by a fallback
	bool ReadText(const TextValue* text, ClassName* value);
	inline void WriteText(TextValue* text, const ClassName& value)
	{
	}
	bool ReadBinary(BinaryStream* stream, ClassName* value);
	void WriteBinary(BinaryStream* stream, const ClassName& value);

	template<class T> class MetaProperty : public MetaPropertyBase
	{
	public:
		typedef typename PropertyValue<T>::Type Value;

		MetaProperty(MetaTypeBase* newValueType, MetaClassBase* newOwner, const ClassName& newName, PropertySetter<T>* newSetter,
			PropertyGetter<T>* newGetter, unsigned int newFlags) :
			MetaPropertyBase(newValueType, newOwner, newName, newSetter, newGetter, newFlags)
		{
		}
		virtual ~MetaProperty()
		{
		}
		virtual const type_info* GetValueType()
		{
			return &typeid(Value);
		}
		virtual bool SetText(const TextValue* text, void* object);
		virtual void GetText(TextValue* text, void* object);
		virtual bool SetBinary(BinaryStream* stream, void* object);
		virtual void GetBinary(BinaryStream* stream, void* object);
		virtual DelegatePropertyBase* CreateDelegate(void* object);

		PropertySetter<T>* GetSetter()
		{
			return static_cast<PropertySetter<T>*>(setter);
		}
		PropertyGetter<T>* GetGetter()
		{
			return static_cast<PropertyGetter<T>*>(getter);
		}
		// The registration helper of the class's reflection
		static void Create(MetaClassBase* owner, const ClassName& name, PropertySetter<T>* setter, PropertyGetter<T>* getter,
			unsigned int flags)
		{
			new MetaProperty(FindMetaType(typeid(Value)), owner, name, setter, getter, flags);
		}
		OM_ALLOCATION(MetaProperty);
	};

	template<class T> const char* MetaProperty<T>::AllocationTag()
	{
		return "";
	}

	template<class T> bool MetaProperty<T>::SetText(const TextValue* text, void* object)
	{
		MetaTypeBase*& type = MetaTypeCache<Value>::type;
		if (type == 0)
		{
			type = FindMetaType(typeid(Value));
		}
		bool ok;
		if (type == 0)
		{
			Value value;
			ok = ReadText(text, &value);
			if (ok)
			{
				GetSetter()->Invoke(object, value);
			}
		}
		else
		{
			Value value;
			ok = type->ReadText(text, &value);
			if (ok)
			{
				GetSetter()->Invoke(object, value);
			}
		}
		return ok;
	}

	template<class T> void MetaProperty<T>::GetText(TextValue* text, void* object)
	{
		MetaTypeBase*& cache = MetaTypeCache<Value>::type;
		if (cache == 0)
		{
			cache = FindMetaType(typeid(Value));
		}
		MetaTypeBase* type = cache;
		if (type == 0)
		{
			WriteText(text, GetGetter()->Invoke(object));
		}
		else
		{
			Value value = GetGetter()->Invoke(object);
			type->WriteText(text, &value);
		}
	}

	template<class T> bool MetaProperty<T>::SetBinary(BinaryStream* stream, void* object)
	{
		Value value;
		bool ok = ReadBinary(stream, &value);
		if (ok)
		{
			GetSetter()->Invoke(object, value);
		}
		return ok;
	}

	template<class T> void MetaProperty<T>::GetBinary(BinaryStream* stream, void* object)
	{
		WriteBinary(stream, GetGetter()->Invoke(object));
	}
}

#endif
