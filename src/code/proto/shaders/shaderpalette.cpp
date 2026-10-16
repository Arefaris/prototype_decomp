// proto::ShaderPalette: see the header. The file name (code/proto/shaders/) and the names are guesses.
#include "code/proto/shaders/shaderpalette.h"

namespace proto
{
	// Destroys the elements of an array and frees its storage
	template<class T> inline void DestroyArray(container::ArrayDynamic<T, container::AllocatorNew>& array)
	{
		for (T *last = array.end, *item = array.begin; item != last; item++)
		{
			item->~T();
		}
		array.end = array.begin;
		if (array.begin != 0)
		{
			operator delete[](array.begin);
		}
	}

	// The scalar deleting destructor the compiler writes for the destructor below
	// FUNCTION: ENGINE 0x102A6140

	// FUNCTION: ENGINE 0x102A60B0
	ShaderPalette::~ShaderPalette()
	{
		DestroyArray(data);
		DestroyArray(entries);
	}
}
