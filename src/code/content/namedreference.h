// A member that refers to an inventory object by name, reflected through three accessors of its class: the object
// (which the owner may not keep), the name it was found by and a setter that takes both (RTTI, global namespace:
// NamedReferenceMemberGetSetter<class C, class T>, derived from content::NamedReferenceMetaTypeGetSetter, which
// loadinventory.h declares with the meta type).
#ifndef CONTENT_NAMEDREFERENCE_H
#define CONTENT_NAMEDREFERENCE_H

#include "code/content/loadinventory.h"

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
	virtual content::LoadObject* GetObject(const void* object)
	{
		return (((const C*)object)->*getter)();
	}
	virtual void Set(void* object, content::LoadObject* value, const content::ObjectName* name)
	{
		(((C*)object)->*setter)((T*)value, *name);
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
