// pure3d::NewShaderLoader (RTTI name; bases content::SimpleChunkHandler, content::ObjectLoader,
// content::LoadObject, core::IRefCount; 8 vftable slots, vftable 0x10EAFCB8): the loader of the shader chunk (0x11015),
// which makes a pure3d::Shader out of a shader template and the values of its inputs. A listener can be told when a
// shader falls back to the "error" template. The unit is around 0x10B96200 - 0x10B96990 (file name guessed).
#ifndef PURE3D_LOADERS_NEWSHADERLOADER_H
#define PURE3D_LOADERS_NEWSHADERLOADER_H

#include "code/content/chunkhandler.h"

namespace pure3d
{
	// What a shader loader tells about the shaders that could not be made as asked (RTTI unknown; slot 3 is the
	// report)
	class ShaderLoadListener : public core::IRefCount
	{
	public:
		virtual void Report(const char* shaderName, const char* templateName);
	};

	class NewShaderLoader : public content::SimpleChunkHandler
	{
	public:
		// The destructor is declared first and not defined here, so that the vftable stays with the engine's own
		// copy of the unit.
		virtual ~NewShaderLoader();

		// 0x10B96280: the shader a shader chunk describes
		virtual void LoadObject(core::IRefCount** object, content::ObjectName* name, content::ChunkReader* reader,
			content::LoadInventory* inventory);

		ShaderLoadListener* listener;
	};
}

#endif
