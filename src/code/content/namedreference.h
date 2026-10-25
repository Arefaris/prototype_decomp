// The meta types of a member that refers to an inventory object by name (RTTI: content::NamedReferenceMetaTypeGetSetter,
// content::NamedReferenceMetaTypeGetSet and, in the global namespace, NamedReferenceMemberGetSetter<class C, class T>
// derived from the first). The member is read and written through three accessors of its class: the object (which the
// owner may not keep), the name it was found by and a setter that takes both. The meta type classes belong to the
// content library's unit (the constructor is 0x105FF030); only what a class that reflects such a member needs is declared
// here.
#ifndef CONTENT_NAMEDREFERENCE_H
#define CONTENT_NAMEDREFERENCE_H

#include "code/content/loadinventory.h"

namespace content
{
	// Reads and writes a named reference member through accessors (RTTI: 3 slots)
	struct NamedReferenceMetaTypeGetSetter
	{
	public:
		virtual const ObjectName* GetName(const void* object) = 0;
		virtual LoadObject* Get(const void* object) = 0;
		virtual void Set(void* object, LoadObject* value, const ObjectName& name) = 0;
	};

	// The meta type of a named reference reached through accessors (RTTI: 15 slots over ReferenceMetaType; the
	// slots are the content library's)
	class NamedReferenceMetaTypeGetSet : public ReferenceMetaType
	{
	public:
		// 0x105FF030
		NamedReferenceMetaTypeGetSet(LoadInventory::DynamicCasterBase* caster, NamedReferenceMetaTypeGetSetter* getSetter,
			const char* code);

		virtual void Slot12();
		virtual void Slot13();
		virtual void Slot14();

		NamedReferenceMetaTypeGetSetter* getSetter;
	};
}

// A named reference member of class C reached through accessors
template<class C, class T> class NamedReferenceMemberGetSetter : public content::NamedReferenceMetaTypeGetSetter
{
public:
	typedef T* (C::*Getter)() const;
	typedef const content::ObjectName* (C::*NameGetter)() const;
	typedef void (C::*Setter)(T*, const content::ObjectName&);

	NamedReferenceMemberGetSetter(Getter newGetter, NameGetter newNameGetter, Setter newSetter)
	{
		getter = newGetter;
		nameGetter = newNameGetter;
		setter = newSetter;
	}

	virtual const content::ObjectName* GetName(const void* object)
	{
		return (((const C*)object)->*nameGetter)();
	}
	virtual content::LoadObject* Get(const void* object)
	{
		return (((const C*)object)->*getter)();
	}
	virtual void Set(void* object, content::LoadObject* value, const content::ObjectName& name)
	{
		(((C*)object)->*setter)((T*)value, name);
	}

	Getter getter;
	NameGetter nameGetter;
	Setter setter;
};

namespace content
{
	template<class C, class T> NamedReferenceMetaTypeGetSet* GetNamedReferenceMemberMetaType(
		T* (C::*getter)() const, const ObjectName* (C::*nameGetter)() const,
		void (C::*setter)(T*, const ObjectName&), const char* code)
	{
		static NamedReferenceMemberGetSetter<C, T> sGetSetter(getter, nameGetter, setter);
		static LoadInventory::DynamicCaster<T> sCaster;
		static NamedReferenceMetaTypeGetSet sType(&sCaster, &sGetSetter, code);
		return &sType;
	}
}

#endif
