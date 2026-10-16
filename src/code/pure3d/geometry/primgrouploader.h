// pure3d::PrimGroupLoader (RTTI name; base pure3d::RefCounted, 3 vftable slots): what a mesh's "prim group" chunk
// turns into, the description of the primitive groups the mesh's geometry is cut into. It is not a loader in the
// content sense (its base is the plain reference-counted class) and the unit around it is 0x10B8BD30 - 0x10B8C800.
// The member names are guesses; the layout is what the constructor and the destructor write.
#ifndef PURE3D_GEOMETRY_PRIMGROUPLOADER_H
#define PURE3D_GEOMETRY_PRIMGROUPLOADER_H

#include "code/pure3d/entity.h"

namespace pure3d
{
	// The groups themselves (released as one reference-counted object through core::SafeRelease; name guessed)
	class PrimGroupList;

	class PrimGroupLoader : public RefCounted
	{
	public:
		// 0x10B8BD30 / 0x10B8C030. The destructor is declared first and not defined here, so that the vftable stays
		// with the engine's own copy of the unit.
		PrimGroupLoader();
		~PrimGroupLoader();

		PrimGroupList* groups;
		int unknownC;
		bool unknown10;
		bool unknown11;
		bool unknown12;
		int unknown14;
		int unknown18;
		int unknown1C;
		int unknown20;
		int unknown24;
		int unknown28;
	};
}

#endif
