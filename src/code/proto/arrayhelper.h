// The element access of the reflected arrays of proto classes whose elements the engine's helper copies with the count
// form of Insert (RTTI: content::ArrayDynamicHelper<container::ArrayDynamic<T, container::AllocatorNew> >). The helper
// of the generic template in content/metatype.h differs in that Insert; the elements are declared with
// PROTO_ARRAY_HELPER(T) after the element class (and its ArrayEraseInline specialisation, if it needs one).
#ifndef PROTO_ARRAYHELPER_H
#define PROTO_ARRAYHELPER_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/metatype.h"

#define PROTO_ARRAY_HELPER(ElementType) \
namespace content \
{ \
	template<> class ArrayDynamicHelper<container::ArrayDynamic<ElementType, container::AllocatorNew> > \
		: public ArrayDynamicHelperBase \
	{ \
	public: \
		typedef container::ArrayDynamic<ElementType, container::AllocatorNew> A; \
		typedef A::Element T; \
\
		virtual int Size(void* array) \
		{ \
			return ((A*)array)->Size(); \
		} \
		virtual void* Get(void* array, int index) \
		{ \
			return ((A*)array)->begin + index; \
		} \
		virtual void* GetConst(void* array, int index) \
		{ \
			return ((A*)array)->begin + index; \
		} \
		virtual void Insert(void* array, int index, int unused) \
		{ \
			A* a = (A*)array; \
			if (a->Size() >= a->Capacity()) \
			{ \
				a->Reserve(a->Size() + 1); \
			} \
			T* position = a->begin + index; \
			static T sDefault; \
			a->Insert(position, 1, sDefault); \
		} \
		virtual void Erase(void* array, int index, int unused) \
		{ \
			A* a = (A*)array; \
			a->Erase(a->begin + index); \
		} \
		virtual int Capacity(void* array) \
		{ \
			return ((A*)array)->Capacity(); \
		} \
		virtual void Expand(void* array, unsigned int count) \
		{ \
			A* a = (A*)array; \
			if (a->Capacity() == 0) \
			{ \
				a->Allocate(count); \
			} \
			else if (count + a->Size() > a->Capacity()) \
			{ \
				a->Reserve(count + a->Size()); \
			} \
		} \
	}; \
}

#endif
