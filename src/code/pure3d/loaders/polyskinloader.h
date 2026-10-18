// pure3d::PolySkinLoader (RTTI name; bases content::SimpleChunkHandler, content::ObjectLoader, content::LoadObject,
// core::IRefCount; 8 vftable slots, vftable 0x10EAF784): the loader of the skinned geometry chunk (0x10001). Its
// groups are read through a PrimGroupLoader. The unit is around 0x10B90B00 - 0x10B91300 (file name guessed).
#ifndef PURE3D_LOADERS_POLYSKINLOADER_H
#define PURE3D_LOADERS_POLYSKINLOADER_H

#include "code/content/chunkhandler.h"
#include "code/pure3d/geometry/primgrouploader.h"

namespace pure3d
{
	class PolySkinLoader : public content::SimpleChunkHandler
	{
	public:
		// The destructor is declared first and not defined here, so that the vftable stays with the engine's own
		// copy of the unit.
		virtual ~PolySkinLoader();

		// 0x10B90CA0: the drawable a skinned geometry chunk describes
		virtual void LoadObject(core::IRefCount** object, content::ObjectName* name, content::ChunkReader* reader,
			content::LoadInventory* inventory);

		// The loader reads the index of its groups from here (0x10B90B20 / 0x10B90B30) and hands it to the group loader
		bool unknown10;
		int index;
		PrimGroupLoader* groupLoader;

		// 0x11209D84: whether the loaded drawables get a pose of their skeleton (0x10B90B40 / 0x10B90B50 set and get it)
		static bool sCreatePoses;
	};
}

#endif
