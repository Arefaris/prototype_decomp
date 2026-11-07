// proto::Heightmap (RTTI and reflection names; a load object): a grid of 16-bit heights over an area of the world, with the
// margins around it, the lowest point and the factor that turns a stored height into a world height. Unit 0x10393100 -
// 0x10397700 (no assert path; the file name is a guess); the reflected names are original, the rest is guessed. The
// constructor (0x103954E0) and destructor (0x10395080) build and free a pool and a lookup table and are not
// reconstructed.
#ifndef PROTO_HEIGHTMAP_H
#define PROTO_HEIGHTMAP_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/math/aabb.h"
#include "code/math/vector.h"

namespace container
{
	// The engine's Erase of the height array moves the elements with a loop that keeps the distance in a register
	template<> struct ArrayEraseInline<unsigned short>
	{
		enum
		{
			value = 3
		};
	};
}

namespace proto
{
	class Heightmap : public content::MetaLoadObject
	{
	public:
		typedef container::ArrayDynamic<unsigned short, container::AllocatorNew> HeightArray;

		Heightmap();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// Vftable slot 3 (0x103951D0): ignores the name
		virtual void SetName(const content::ObjectName& name);
		// Vftable slot 5 (0x10393160): works out the factor behind the grid size and the half of the rows
		virtual bool Slot5();

		float gridSize;  // +8
		float inverseGridSize;  // +0xC
		int sizeX;  // +0x10
		int sizeY;  // +0x14
		int marginX;  // +0x18
		int marginY;  // +0x1C
		math::Vector minVec;  // +0x20
		float minHeight;  // +0x2C
		float maxHeight;  // +0x30
		float quantum;  // +0x34
		math::AABB aabb;  // +0x38
		int halfRows;  // +0x50
		HeightArray data;  // +0x54
		unsigned char unknown60[0x190 - 0x60];
	};
}

#endif
