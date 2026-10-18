// pure3d::ShaderTemplateLoader (RTTI name; bases content::SimpleChunkHandler, content::ObjectLoader,
// content::LoadObject, core::IRefCount; 8 vftable slots, vftable 0x10EAFC50): the loader of the shader template
// chunk. It makes no object; the template it builds goes into the device. The unit is around 0x10B95330 -
// 0x10B96280 (file name guessed).
#ifndef PURE3D_LOADERS_SHADERTEMPLATELOADER_H
#define PURE3D_LOADERS_SHADERTEMPLATELOADER_H

#include "code/content/chunkhandler.h"

namespace pure3d
{
	class ShaderTemplateLoader : public content::SimpleChunkHandler
	{
	public:
		// The destructor is declared first and not defined here, so that the vftable stays with the engine's own
		// copy of the unit.
		virtual ~ShaderTemplateLoader();

		// 0x10B95780: reads the template into the device
		virtual void LoadObject(core::IRefCount** object, content::ObjectName* name, content::ChunkReader* reader,
			content::LoadInventory* inventory);
	};
}

#endif
