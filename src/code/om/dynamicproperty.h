// The dynamic properties of the om library (RTTI: om::DynamicPropertyBase, om::DynamicProperty<T>, the commands
// om::Command0<R>, om::Command1<R, A>, om::CommandMember0Const<C, B, R>, om::CommandMember1<C, B, R, A>, the delegate
// om::CommandDelegate<V> and the factories om::Factory<B, D>): a value that is held by an object of its own with
// the name it is known by, read and written as text and in binary form, and bound to other code through a
// delegate that runs one command to read the value and another to write it.
#ifndef OM_DYNAMICPROPERTY_H
#define OM_DYNAMICPROPERTY_H

#include "code/om/allocation.h"
#include "code/om/delegate.h"
#include "code/om/metaenum.h"
#include "code/om/metaproperty.h"
#include "code/om/metatype.h"
#include "code/om/name.h"
#include "code/om/textvalue.h"

namespace om
{
	// The commands: a call that is kept as an object (the first holds none of its arguments, the second takes one)
	template<class R> class Command0
	{
	public:
		Command0()
		{
		}
		virtual ~Command0()
		{
		}
		// Slot 1: runs the command
		virtual R Call() = 0;
		// Slot 2: a copy of the command
		virtual Command0* Clone() = 0;
	};

	template<class R, class A> class Command1
	{
	public:
		Command1()
		{
		}
		virtual ~Command1()
		{
		}
		// Slot 1: runs the command with the argument
		virtual R Call(A value) = 0;
	};

	// A const member function of B that is run on a C
	template<class C, class B, class R> class CommandMember0Const : public Command0<R>
	{
	public:
		typedef R (B::*Function)() const;

		CommandMember0Const(C* newObject, Function newFunction) :
			object(newObject),
			function(newFunction)
		{
		}
		virtual ~CommandMember0Const()
		{
		}
		virtual R Call()
		{
			return (object->*function)();
		}
		virtual Command0<R>* Clone()
		{
			return new CommandMember0Const(object, function);
		}
		static Command0<R>* Create(C* object, Function function);
		OM_ALLOCATION(CommandMember0Const);

		C* object;  // 4
		Function function;  // 8
	};

	template<class C, class B, class R> const char* CommandMember0Const<C, B, R>::AllocationTag()
	{
		return "";
	}

	template<class C, class B, class R> Command0<R>* CommandMember0Const<C, B, R>::Create(C* object, Function function)
	{
		return new CommandMember0Const(object, function);
	}

	// A member function of B with one argument that is run on a C
	template<class C, class B, class R, class A> class CommandMember1 : public Command1<R, A>
	{
	public:
		typedef R (B::*Function)(A);

		CommandMember1(C* newObject, Function newFunction) :
			object(newObject),
			function(newFunction)
		{
		}
		virtual ~CommandMember1()
		{
		}
		virtual R Call(A value)
		{
			return (object->*function)(value);
		}
		static Command1<R, A>* Create(C* object, Function function);
		OM_ALLOCATION(CommandMember1);

		C* object;  // 4
		Function function;  // 8
	};

	template<class C, class B, class R, class A> const char* CommandMember1<C, B, R, A>::AllocationTag()
	{
		return "";
	}

	template<class C, class B, class R, class A> Command1<R, A>* CommandMember1<C, B, R, A>::Create(C* object, Function function)
	{
		return new CommandMember1(object, function);
	}

	// The holder of a command that deletes it with the holder (name guessed)
	template<class T> class Owned
	{
	public:
		Owned(T* newPointer) :
			pointer(newPointer)
		{
		}
		~Owned()
		{
			if (pointer != 0)
			{
				delete pointer;
			}
		}

		T* pointer;
	};

	// A delegate that reads its value with one command and writes it with another
	template<class V> class CommandDelegate : public DelegateProperty<V>
	{
	public:
		CommandDelegate(Command0<V>* newGetter, Command1<void, V>* newSetter) :
			getter(newGetter),
			setter(newSetter)
		{
		}
		virtual MetaTypeBase* GetMetaType()
		{
			MetaTypeBase*& cache = MetaTypeCache<V>::type;
			if (cache == 0)
			{
				cache = FindMetaType(typeid(V));
			}
			return cache;
		}
		virtual V Get()
		{
			return getter.pointer->Call();
		}
		virtual void Set(V value)
		{
			setter.pointer->Call(value);
		}
		OM_ALLOCATION(CommandDelegate);

		Owned<Command0<V> > getter;  // 8
		Owned<Command1<void, V> > setter;  // 0xC
	};

	template<class V> const char* CommandDelegate<V>::AllocationTag()
	{
		return "";
	}

	// The forms of the values in text and binary form that the property classes use
	bool ReadText(const TextValue* text, char* value);
	void WriteText(TextValue* text, char value);
	bool ReadBinary(BinaryStream* stream, char* value);
	bool WriteBinary(BinaryStream* stream, char value);
	bool ReadText(const TextValue* text, unsigned char* value);
	void WriteText(TextValue* text, unsigned char value);
	bool ReadBinary(BinaryStream* stream, unsigned char* value);
	bool WriteBinary(BinaryStream* stream, unsigned char value);
	bool ReadText(const TextValue* text, short* value);
	void WriteText(TextValue* text, short value);
	bool ReadBinary(BinaryStream* stream, short* value);
	bool WriteBinary(BinaryStream* stream, short value);
	bool ReadText(const TextValue* text, unsigned short* value);
	void WriteText(TextValue* text, unsigned short value);
	bool ReadBinary(BinaryStream* stream, unsigned short* value);
	bool WriteBinary(BinaryStream* stream, unsigned short value);
	bool ReadText(const TextValue* text, int* value);
	void WriteText(TextValue* text, int value);
	// The binary forms of an int are the enumerations' integer forms (0x105B7EB0 / 0x105B7ED0)
	bool ReadBinary(BinaryStream* stream, int* value);
	bool WriteBinary(BinaryStream* stream, int value);

	// The engine's text reader of the 64-bit numbers is not expanded in the property that reads one
	template<> __declspec(noinline) bool ReadText<__int64>(const TextValue* text, __int64* value);

	// The base of the dynamic properties: all slots are pure
	class DynamicPropertyBase
	{
	public:
		virtual ~DynamicPropertyBase()
		{
		}
		int unknown4;
		// Slot 1: takes the value of another property of the same type
		virtual void SetFrom(DynamicPropertyBase* other) = 0;
		// Slot 2: takes the value a pointer refers to
		virtual void SetFromPointer(const void* value) = 0;
		// Slot 3: copies the value to the place a pointer refers to
		virtual void GetValue(void* value) const = 0;
		virtual const void* GetValuePointer() const = 0;
		virtual void* GetValuePointer() = 0;
		// Slot 6 and 7: writes the value to a delegate, takes the value of a delegate
		virtual void WriteToDelegate(DelegatePropertyBase* delegate) = 0;
		virtual void ReadFromDelegate(DelegatePropertyBase* delegate) = 0;
		// Slot 8: takes the value a pointer refers to (the second argument is not read)
		virtual void SetFromPointer2(const void* value, unsigned int unused) = 0;
		// Slot 9: the description of the value's type
		virtual MetaTypeBase* GetMetaType() const = 0;
		virtual void SetName(ClassName newName) = 0;
		virtual ClassName GetName() const = 0;
		virtual DelegatePropertyBase* CreateDelegate() = 0;
		virtual bool ReadText(const TextValue* parent) = 0;
		virtual void WriteText(TextValue* parent) = 0;
		virtual bool ReadBinary(BinaryStream* stream) = 0;
		virtual bool WriteBinary(BinaryStream* stream) = 0;
	};

	// The engine sets the value of a new property to zero for the unsigned int property only
	template<class T> inline void InitializeValue(T& value)
	{
	}
	template<> inline void InitializeValue<unsigned int>(unsigned int& value)
	{
		value = 0;
	}

	template<class T> class DynamicProperty : public DynamicPropertyBase
	{
	public:
		typedef CommandMember0Const<DynamicProperty, DynamicProperty, T> GetCommand;
		typedef CommandMember1<DynamicProperty, DynamicProperty, void, T> SetCommand;

		DynamicProperty() :
			type(FindMetaType(typeid(T))),
			name(0)
		{
			InitializeValue(value);
		}
		virtual ~DynamicProperty();
		virtual void SetFrom(DynamicPropertyBase* other);
		virtual void SetFromPointer(const void* newValue);
		virtual void GetValue(void* result) const;
		virtual const void* GetValuePointer() const;
		virtual void* GetValuePointer();
		virtual void WriteToDelegate(DelegatePropertyBase* delegate);
		virtual void ReadFromDelegate(DelegatePropertyBase* delegate);
		virtual void SetFromPointer2(const void* newValue, unsigned int unused);
		virtual MetaTypeBase* GetMetaType() const;
		virtual void SetName(ClassName newName);
		virtual ClassName GetName() const;
		virtual DelegatePropertyBase* CreateDelegate();
		virtual bool ReadText(const TextValue* parent);
		virtual void WriteText(TextValue* parent);
		virtual bool ReadBinary(BinaryStream* stream);
		virtual bool WriteBinary(BinaryStream* stream);

		T GetValue() const;
		void Set(T newValue);
		OM_ALLOCATION(DynamicProperty);

		T value;  // 8
		MetaTypeBase* type;
		ClassName name;
		unsigned __int64 unknown;
	};

	// The factories that make the dynamic properties (RTTI: om::FactoryBase<B>, om::Factory<B, D>): registered objects that
	// make an object of a type on request
	template<class B> class FactoryBase
	{
	public:
		FactoryBase()
		{
		}
		virtual ~FactoryBase();
		// Slot 1: makes the object (the argument is not read)
		virtual B* Create(void* unknown) = 0;
		// Slot 2: the type of what it makes
		virtual const type_info* GetType() = 0;

		unsigned __int64 unknown[5];  // 8
	};

	template<class B> FactoryBase<B>::~FactoryBase()
	{
	}

	template<class B, class D> class Factory : public FactoryBase<B>
	{
	public:
		virtual ~Factory()
		{
		}
		virtual B* Create(void* unknown)
		{
			return new D();
		}
		virtual const type_info* GetType()
		{
			return &typeid(D);
		}
		OM_ALLOCATION(Factory);
	};

	template<class B, class D> const char* Factory<B, D>::AllocationTag()
	{
		return "";
	}

	template<class T> const char* DynamicProperty<T>::AllocationTag()
	{
		return "";
	}

	template<class T> DynamicProperty<T>::~DynamicProperty()
	{
	}

	template<class T> T DynamicProperty<T>::GetValue() const
	{
		return value;
	}

	template<class T> void DynamicProperty<T>::Set(T newValue)
	{
		value = newValue;
	}

	template<class T> void DynamicProperty<T>::SetFrom(DynamicPropertyBase* other)
	{
		Set(static_cast<DynamicProperty*>(other)->GetValue());
	}

	template<class T> void DynamicProperty<T>::SetFromPointer(const void* newValue)
	{
		Set(*static_cast<const T*>(newValue));
	}

	template<class T> void DynamicProperty<T>::GetValue(void* result) const
	{
		*static_cast<T*>(result) = value;
	}

	template<class T> const void* DynamicProperty<T>::GetValuePointer() const
	{
		return &value;
	}

	template<class T> void* DynamicProperty<T>::GetValuePointer()
	{
		return &value;
	}

	template<class T> void DynamicProperty<T>::WriteToDelegate(DelegatePropertyBase* delegate)
	{
		static_cast<DelegateProperty<T>*>(delegate)->Set(value);
	}

	template<class T> void DynamicProperty<T>::ReadFromDelegate(DelegatePropertyBase* delegate)
	{
		Set(static_cast<DelegateProperty<T>*>(delegate)->Get());
	}

	template<class T> void DynamicProperty<T>::SetFromPointer2(const void* newValue, unsigned int unused)
	{
		value = *static_cast<const T*>(newValue);
	}

	template<class T> MetaTypeBase* DynamicProperty<T>::GetMetaType() const
	{
		return type;
	}

	template<class T> void DynamicProperty<T>::SetName(ClassName newName)
	{
		name = newName;
	}

	template<class T> ClassName DynamicProperty<T>::GetName() const
	{
		return name;
	}

	template<class T> DelegatePropertyBase* DynamicProperty<T>::CreateDelegate()
	{
		return new CommandDelegate<T>(GetCommand::Create(this, &DynamicProperty::GetValue), SetCommand::Create(this, &DynamicProperty::Set));
	}

	template<class T> bool DynamicProperty<T>::ReadText(const TextValue* parent)
	{
		const TextValue* nameNode = parent->FindChild("Name");
		const TextValue* valueNode = parent->FindChild("Value");
		if (nameNode != 0)
		{
			ClassName key;
			bool ok = om::ReadText(nameNode, &key) ? true : false;
			SetName(ClassName(key.key));
			if (valueNode != 0)
			{
				om::ReadText(valueNode, &value);
				return ok;
			}
		}
		return false;
	}

	template<class T> void DynamicProperty<T>::WriteText(TextValue* parent)
	{
		TextNode* property = new TextNode(parent, String::Wrap("Property"));
		TextNode* typeNode = new TextNode(property, String::Wrap("Type"));
		TextNode* nameNode = new TextNode(property, String::Wrap("Name"));
		TextNode* valueNode = new TextNode(property, String::Wrap("Value"));
		om::WriteText(typeNode, FindMetaType(typeid(T))->GetName());
		om::WriteText(nameNode, name);
		om::WriteText(valueNode, value);
	}

	template<class T> bool DynamicProperty<T>::ReadBinary(BinaryStream* stream)
	{
		if (om::ReadBinary(stream, &name))
		{
			if (om::ReadBinary(stream, &value))
			{
				return true;
			}
		}
		return false;
	}

	template<class T> bool DynamicProperty<T>::WriteBinary(BinaryStream* stream)
	{
		if (om::WriteBinary(stream, FindMetaType(typeid(T))->GetName()))
		{
			if (om::WriteBinary(stream, name))
			{
				if (om::WriteBinary(stream, value))
				{
					return true;
				}
			}
		}
		return false;
	}
}

#endif
