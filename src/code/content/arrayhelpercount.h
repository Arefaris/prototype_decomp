// The element access of a container::ArrayDynamic<T, AllocatorNew> for its meta type, in the form some of the engine's
// units hold: the insertion makes room with the count version of Insert (the generic form in metatype.h inserts the single
// element). A unit declares the form of its array with the macro, in namespace content.
#ifndef CONTENT_ARRAYHELPERCOUNT_H
#define CONTENT_ARRAYHELPERCOUNT_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/metatype.h"

#define CONTENT_ARRAY_HELPER_COUNT_INSERT(ARRAY) \
	template<> class ArrayDynamicHelper<ARRAY> : public ArrayDynamicHelperBase \
	{ \
	public: \
		typedef ARRAY A; \
		typedef A::Element T; \
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
	}

#endif
