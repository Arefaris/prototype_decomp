// The reflection of an enumeration member that is reached through a getter and a setter (RTTI names:
// content::EnumMetaTypeGetSet, content::EnumMetaTypeGetSetter and the global EnumMemberGetSetter<C, E>). The vftable
// of EnumMetaTypeGetSet is the one of EnumMetaType plus the two accessors in slots 12 and 13.
#ifndef CONTENT_ENUMMETATYPE_H
#define CONTENT_ENUMMETATYPE_H

#include "code/content/metatype.h"

namespace content
{
	struct EnumMetaTypeGetSetter
	{
		EnumMetaTypeGetSetter()
		{
		}
		virtual int Get(const void* object) = 0;
		virtual void Set(void* object, int value) = 0;
	};

	class EnumMetaTypeGetSet : public EnumMetaType
	{
	public:
		EnumMetaTypeGetSet(EnumMetaTypeGetSetter* newGetSetter, const char* name, int unknown, const char* code,
			const EnumValue* values, int count) : EnumMetaType(name, unknown, code, values, count)
		{
			getSetter = newGetSetter;
		}

		// The accessors (0x10004980 / 0x10027F52 are the thunks the vftable holds, another unit)
		virtual int Get(const void* object);
		virtual void Set(void* object, int value);

		EnumMetaTypeGetSetter* getSetter;  // 0x1C
	};
}

// An enumeration member reached through a getter and a setter of class C (RTTI: global namespace)
template<class C, class E> class EnumMemberGetSetter : public content::EnumMetaTypeGetSetter
{
public:
	typedef E (C::*Getter)() const;
	typedef void (C::*Setter)(E);

	EnumMemberGetSetter(Getter newGetter, Setter newSetter)
	{
		getter = newGetter;
		setter = newSetter;
	}

	virtual int Get(const void* object)
	{
		return (((const C*)object)->*getter)();
	}
	virtual void Set(void* object, int value)
	{
		(((C*)object)->*setter)((E)value);
	}

	Getter getter;
	Setter setter;
};

namespace content
{
	// The enumeration's description is asked for every time, only the meta type is made once
	template<class C, class E> MetaType* GetMemberEnumMetaType(E (C::*getter)() const, void (C::*setter)(E))
	{
		static const char* sName;
		static const EnumValue* sValues;
		static int sCount;
		static const char* sCode;
		EnumInfo<E>::Get(&sName, &sValues, &sCount, &sCode);
		static EnumMemberGetSetter<C, E> sGetSetter(getter, setter);
		static EnumMetaTypeGetSet sType(&sGetSetter, sName, 1, sCode, sValues, sCount);
		return &sType;
	}
}

#endif
