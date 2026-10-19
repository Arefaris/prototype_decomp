// pure3d::VertexStream<T> (name guess; a template without virtual functions leaves no RTTI): one stream of a locked
// vertex buffer, found by its semantic name in the lock's declaration. The layout is what the stream's set-up
// (0x106EBB40 and its copies) writes: whether the declaration has the stream, the stream's offset in a vertex, the
// cursor the loaders write through (the first vertex's element to begin with), the first element, the end and the
// stride.
//
// The engine has one copy of the constructor and of the set-up per element type (no identical code folding): 0x106EC110
// / 0x106EBB40 for math::Vector, 0x106EC140 / 0x106EBBA0 for math::Vector4, 0x1072F950 / 0x1072F820 for the
// four-byte elements (colours, texture coordinates), and the prim group loader's own unit has the copies for its packed
// elements. Which type each copy was made for is a guess; only the code is known.
//
// The half floats of the packed streams: math::Vector from three halves (0x106E2B40) and four halves from a vector
// (0x10B8AF10), names guessed.
#ifndef PURE3D_VERTEXSTREAM_H
#define PURE3D_VERTEXSTREAM_H

#include "code/core/name.h"
#include "code/math/vector.h"
#include "code/pure3d/pddi/vertexdeclaration.h"

namespace pure3d
{
	template<class T> class VertexStream
	{
	public:
		// Sets the stream up over the lock (out of line, defined below the class: the engine calls its copies)
		VertexStream(dxVertexDeclaration* lock, core::Name<core::CaseInsensitiveKey32> name);
		// Looks the stream up in the lock's declaration and points the stream at its first element
		void Init(dxVertexDeclaration* lock, core::Name<core::CaseInsensitiveKey32> name);
		// Moves the cursor on to the next vertex's element
		void Next()
		{
			current = (T*)((char*)current + stride);
		}

		bool enabled;
		int offset;
		// The element the loaders write next (they walk the stream with it) and the first one
		T* current;
		T* start;
		T* end;
		int stride;
	};

	template<class T> VertexStream<T>::VertexStream(dxVertexDeclaration* lock,
		core::Name<core::CaseInsensitiveKey32> name)
	{
		Init(lock, name);
	}

	template<class T> void VertexStream<T>::Init(dxVertexDeclaration* lock,
		core::Name<core::CaseInsensitiveKey32> name)
	{
		int index = lock->FindElement(name);
		enabled = index >= 0;
		offset = enabled ? lock->elements[index].value : 0;
		stride = enabled ? lock->elements[index].unknown9 : 0;
		current = (T*)(lock->unknown108 + offset);
		start = current;
		end = (T*)((char*)current + lock->unknown0 * stride);
	}

	// Three half floats (a packed position, normal or offset)
	struct Half3
	{
		Half3()
		{
		}
		// Copied half by half
		Half3(const Half3& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
		}
		// 0x106E2B40
		math::Vector ToVector() const;

		unsigned short x;
		unsigned short y;
		unsigned short z;
	};

	// Four half floats (a packed normal or tangent)
	__declspec(align(8)) struct Half4
	{
		// 0x10B8AF10: the halves of a vector (the fourth is a constant)
		void Set(const math::Vector& vector);

		unsigned short x;
		unsigned short y;
		unsigned short z;
		unsigned short w;
	};

	// Two half floats (packed texture coordinates)
	struct Half2
	{
		unsigned short u;
		unsigned short v;
	};
}

#endif
