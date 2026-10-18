// pure3d::CompositeDrawableLoader (RTTI name; bases content::SimpleChunkHandler, content::ObjectLoader,
// content::LoadObject, core::IRefCount; 8 vftable slots, vftable 0x10EAF8B4): the loader of the composite drawable
// chunk (0x10011), which puts the parts of other drawables together under one skeleton. The unit is around
// 0x10B91300 - 0x10B91CD0 (file name guessed).
#ifndef PURE3D_LOADERS_COMPOSITEDRAWABLELOADER_H
#define PURE3D_LOADERS_COMPOSITEDRAWABLELOADER_H

#include "code/content/chunkhandler.h"

namespace pure3d
{
	class CompositeDrawableLoader : public content::SimpleChunkHandler
	{
	public:
		// The destructor is declared first and not defined here, so that the vftable stays with the engine's own
		// copy of the unit.
		virtual ~CompositeDrawableLoader();

		// 0x10B91410: the drawable a composite drawable chunk describes
		virtual void LoadObject(core::IRefCount** object, content::ObjectName* name, content::ChunkReader* reader,
			content::LoadInventory* inventory);

		// 0x11209E34: whether the loaded drawables get a pose of their skeleton (set by 0x10B91310 / 0x10B91320)
		static bool sCreatePoses;
	};
}

#endif
