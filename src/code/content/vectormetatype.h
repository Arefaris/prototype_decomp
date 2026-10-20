// The reflection of a math::Vector member that is reached through a getter and a setter (RTTI names:
// content::VectorMetaTypeGetSet, content::VectorMetaTypeGetSetter and the global VectorMemberGetSetter<C>). The
// vftable of VectorMetaTypeGetSet is the one of VectorMetaType plus the two accessors in slots 12 and 13.
#ifndef CONTENT_VECTORMETATYPE_H
#define CONTENT_VECTORMETATYPE_H

#include "code/content/metatype.h"
#include "code/math/vector.h"

namespace content
{
	struct VectorMetaTypeGetSetter
	{
		VectorMetaTypeGetSetter()
		{
		}
		virtual const math::Vector* Get(const void* object) = 0;
		virtual void Set(void* object, const math::Vector* value) = 0;
	};

	class VectorMetaTypeGetSet : public VectorMetaType
	{
	public:
		VectorMetaTypeGetSet(VectorMetaTypeGetSetter* newGetSetter, const char* code) : VectorMetaType(code)
		{
			getSetter = newGetSetter;
		}

		// The accessors (0x102F38C0 / 0x105688B0, another unit): read through the getter unless the object lies in
		// the directly addressable range
		virtual const math::Vector* Get(const void* object);
		virtual void Set(void* object, const math::Vector* value);

		VectorMetaTypeGetSetter* getSetter;     // 0x08
	};
}

// A vector member reached through a getter and a setter of class C (RTTI: global namespace)
template<class C> class VectorMemberGetSetter : public content::VectorMetaTypeGetSetter
{
public:
	typedef const math::Vector* (C::*Getter)() const;
	typedef void (C::*Setter)(const math::Vector*);

	VectorMemberGetSetter(Getter newGetter, Setter newSetter)
	{
		getter = newGetter;
		setter = newSetter;
	}

	virtual const math::Vector* Get(const void* object)
	{
		return (((const C*)object)->*getter)();
	}
	virtual void Set(void* object, const math::Vector* value)
	{
		(((C*)object)->*setter)(value);
	}

	Getter getter;
	Setter setter;
};

namespace content
{
	template<class C, int Id> MetaType* GetMemberVectorMetaType(const math::Vector* (C::*getter)() const,
		void (C::*setter)(const math::Vector*), const char* code)
	{
		static VectorMemberGetSetter<C> sGetSetter(getter, setter);
		static VectorMetaTypeGetSet sType(&sGetSetter, code);
		return &sType;
	}
}

#endif
