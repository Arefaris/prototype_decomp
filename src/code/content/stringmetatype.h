// content::StringMetaType, StringMetaTypeGetSet and StringMetaTypeGetSetter (RTTI names) and the global
// StringMemberGetSetter<C>: the meta type of a string member, reached directly (a char array of capacity bytes) or
// through a getter and a setter of class C. StringMetaType's 15 slots are in the content library (0x10E32F2C); slot
// 12 answers the string, slot 13 copies one in. Names other than the classes' are guesses.
#ifndef CONTENT_STRINGMETATYPE_H
#define CONTENT_STRINGMETATYPE_H

#include "code/content/metatype.h"

namespace content
{
	class StringMetaType : public MetaType
	{
	public:
		// 0x10600FC0
		StringMetaType(int newCapacity, const char* code);

		virtual void Slot0();
		virtual void Slot1();
		virtual void Slot2();
		virtual void Slot3();
		virtual void Slot4();
		virtual void Slot6();
		virtual void Slot7();
		virtual void Slot8();
		virtual void Slot9();
		virtual void Slot10();
		virtual void Slot11();
		// 0x10601300 / 0x10601310
		virtual const char* Get(const void* object);
		virtual void Set(void* object, const char* value);
		virtual void Slot14();

		int capacity;
	};

	struct StringMetaTypeGetSetter
	{
	public:
		StringMetaTypeGetSetter()
		{
		}
		virtual const char* Get(void* object) = 0;
		virtual void Set(void* object, const char* value) = 0;
	};

	class StringMetaTypeGetSet : public StringMetaType
	{
	public:
		StringMetaTypeGetSet(StringMetaTypeGetSetter* newGetSetter, int newCapacity, const char* code)
			: StringMetaType(newCapacity, code)
		{
			getSetter = newGetSetter;
		}

		virtual const char* Get(const void* object)
		{
			if (IsDirect(object))
			{
				return StringMetaType::Get(object);
			}
			return getSetter->Get((void*)object);
		}
		virtual void Set(void* object, const char* value)
		{
			if (IsDirect(object))
			{
				StringMetaType::Set(object, value);
				return;
			}
			getSetter->Set(object, value);
		}

		StringMetaTypeGetSetter* getSetter;
	};
}

// A string member reached through a getter and a setter of class C (RTTI: global namespace)
template<class C> class StringMemberGetSetter : public content::StringMetaTypeGetSetter
{
public:
	typedef const char* (C::*Getter)();
	typedef void (C::*Setter)(const char*);

	StringMemberGetSetter(Getter newGetter, Setter newSetter)
	{
		getter = newGetter;
		setter = newSetter;
	}

	virtual const char* Get(void* object)
	{
		return (((C*)object)->*getter)();
	}
	virtual void Set(void* object, const char* value)
	{
		(((C*)object)->*setter)(value);
	}

	Getter getter;
	Setter setter;
};

namespace content
{
	// One instance per member (Id tells them apart), as for the primitive members
	template<class C, int Id> StringMetaTypeGetSet* GetStringMemberMetaType(const char* (C::*getter)(),
		void (C::*setter)(const char*), const char* code)
	{
		static StringMemberGetSetter<C> sGetSetter(getter, setter);
		static StringMetaTypeGetSet sType(&sGetSetter, 0x400, code);
		return &sType;
	}
}

#endif
