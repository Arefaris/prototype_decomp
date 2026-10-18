// pure3d::GeometryLoader (RTTI name; bases content::SimpleChunkHandler, content::ObjectLoader, content::LoadObject,
// core::IRefCount; 8 vftable slots, vftable 0x10EB0314): the loader of the geometry chunk (0x10000), which makes a
// drawable of static meshes. Its groups are read through a PrimGroupLoader. The unit is around 0x10B9C2D0 -
// 0x10B9CA80 (file name guessed).
#ifndef PURE3D_LOADERS_GEOMETRYLOADER_H
#define PURE3D_LOADERS_GEOMETRYLOADER_H

#include "code/content/chunkhandler.h"
#include "code/pure3d/geometry/primgrouploader.h"

namespace pure3d
{
	class GeometryLoader : public content::SimpleChunkHandler
	{
	public:
		// The destructor is declared first and not defined here, so that the vftable stays with the engine's own
		// copy of the unit.
		virtual ~GeometryLoader();

		// 0x10B9C3E0: the drawable a geometry chunk describes
		virtual void LoadObject(core::IRefCount** object, content::ObjectName* name, content::ChunkReader* reader,
			content::LoadInventory* inventory);

		// The index the loader hands to its group loader (0x10B9C2E0 / 0x10B9C300 get and set the flag, 0x10B9C2F0 /
		// 0x10B9C2D0 the index)
		bool unknown10;
		int index;
		PrimGroupLoader* groupLoader;
	};
}

#endif
