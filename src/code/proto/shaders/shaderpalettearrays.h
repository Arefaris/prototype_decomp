// The element access of the shader palette's arrays for the meta system (RTTI content::ArrayDynamicHelper<
// container::ArrayDynamic<T, container::AllocatorNew> >): the entries use the generic helper, the data the count form of
// Insert, the colour patches a helper that keeps its default element in a function of its own, the patch pointers the
// pointer helper.
#ifndef PROTO_SHADERS_SHADERPALETTEARRAYS_H
#define PROTO_SHADERS_SHADERPALETTEARRAYS_H

#include "code/proto/arrayhelper.h"
#include "code/proto/shaders/shaderpalette.h"

PROTO_ARRAY_HELPER(proto::ShaderPaletteData)

namespace content
{
	template<> class ArrayDynamicHelper<proto::ShaderPaletteData::ColourArray> : public ArrayDynamicHelperBase
	{
	public:
		typedef proto::ShaderPaletteData::ColourArray A;
		typedef A::Element T;

		// 0x102E6D70: the default element in a function of its own (not reconstructed: the engine's copy of the
		// constructor stores one vftable pointer less)
		static T& Default();

		virtual int Size(void* array)
		{
			return ((A*)array)->Size();
		}
		virtual void* Get(void* array, int index)
		{
			return ((A*)array)->begin + index;
		}
		virtual void* GetConst(void* array, int index)
		{
			return ((A*)array)->begin + index;
		}
		virtual void Insert(void* array, int index, int unused)
		{
			A* a = (A*)array;
			if (a->Size() >= a->Capacity())
			{
				a->Reserve(a->Size() + 1);
			}
			T* position = a->begin + index;
			a->Insert(position, 1, Default());
		}
		virtual void Erase(void* array, int index, int unused)
		{
			A* a = (A*)array;
			a->Erase(a->begin + index);
		}
		virtual int Capacity(void* array)
		{
			return ((A*)array)->Capacity();
		}
		virtual void Expand(void* array, unsigned int count)
		{
			A* a = (A*)array;
			if (a->Capacity() == 0)
			{
				a->Allocate(count);
			}
			else if (count + a->Size() > a->Capacity())
			{
				a->Reserve(count + a->Size());
			}
		}
	};
}

#endif
