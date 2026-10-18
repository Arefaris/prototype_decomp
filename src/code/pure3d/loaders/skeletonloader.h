// pure3d::SkeletonLoader (RTTI name; bases content::SimpleChunkHandler, content::ObjectLoader, content::LoadObject,
// core::IRefCount; 8 vftable slots, vftable 0x10E550E4): the loader of the skeleton chunk (0x23000). Its
// constructor is 0x106DE040. The unit is around 0x106DDA40 - 0x106DE950 (file name guessed).
#ifndef PURE3D_LOADERS_SKELETONLOADER_H
#define PURE3D_LOADERS_SKELETONLOADER_H

#include "code/content/chunkhandler.h"

namespace pure3d
{
	class SkeletonLoader : public content::SimpleChunkHandler
	{
	public:
		// The destructor is declared first and not defined here, so that the vftable stays with the engine's own
		// copy of the unit.
		virtual ~SkeletonLoader();

		// 0x106DE090: the skeleton a skeleton chunk describes
		virtual void LoadObject(core::IRefCount** object, content::ObjectName* name, content::ChunkReader* reader,
			content::LoadInventory* inventory);

		// 0x110C6C24: whether the loaded skeletons keep the names of their joints, partitions and limbs
		static bool sKeepNames;
	};
}

#endif
