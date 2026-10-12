// The meta types of string members (names from the RTTI: content::StringMetaType, StringMetaTypeGetSet,
// StringMetaTypeGetSetter and the global StringMemberGetSetter<C>). StringMetaType lives in the content library
// (0x10600FC0 - 0x10601400); StringMetaTypeGetSet adds Get / Set (slots 12 / 13) that go through a getter / setter
// object for members reached through accessors. Member names are guesses.
#ifndef CONTENT_STRINGMETATYPE_H
#define CONTENT_STRINGMETATYPE_H

#include "code/content/metatype.h"

namespace content
{
	class StringMetaType : public MetaType
	{
	public:
		// 0x10600FC0: strings of at most maxLength characters
		StringMetaType(int maxLength, const char* code);

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

		int maxLength;
	};

	struct StringMetaTypeGetSetter
	{
	public:
		StringMetaTypeGetSetter()
		{
		}
		virtual const char* Get(const void* object) = 0;
		virtual void Set(void* object, const char* value) = 0;
	};

	class StringMetaTypeGetSet : public StringMetaType
	{
	public:
		StringMetaTypeGetSet(StringMetaTypeGetSetter* newGetSetter, int maxLength, const char* code)
			: StringMetaType(maxLength, code)
		{
			getSetter = newGetSetter;
		}

		virtual const char* Get(const void* object)
		{
			if (IsDirect(object))
			{
				return StringMetaType::Get(object);
			}
			return getSetter->Get(object);
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

// A string member of class C reached through a getter and a setter (RTTI: global namespace)
template<class C> class StringMemberGetSetter : public content::StringMetaTypeGetSetter
{
public:
	typedef const char* (C::*Getter)() const;
	typedef void (C::*Setter)(const char*);

	StringMemberGetSetter(Getter newGetter, Setter newSetter)
	{
		getter = newGetter;
		setter = newSetter;
	}

	virtual const char* Get(const void* object)
	{
		return (((const C*)object)->*getter)();
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
	// One instance per member (Id tells them apart), strings of up to 0x400 characters
	template<class C, int Id> MetaType* GetStringMemberMetaType(const char* (C::*getter)() const,
		void (C::*setter)(const char*), const char* code)
	{
		static StringMemberGetSetter<C> sGetSetter(getter, setter);
		static StringMetaTypeGetSet sType(&sGetSetter, 0x400, code);
		return &sType;
	}
}

#endif
