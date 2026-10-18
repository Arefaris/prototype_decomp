// pure3d::ShaderLoader (RTTI name; bases content::SimpleChunkHandler, content::ObjectLoader, content::LoadObject,
// core::IRefCount; 8 vftable slots, vftable 0x10E5894C): the loader of the old shader chunk (0x11000), whose inputs
// are named by four-character codes. It keeps a table of the names the codes stand for. The unit is around
// 0x10706020 - 0x10707260 (file name guessed).
#ifndef PURE3D_LOADERS_SHADERLOADER_H
#define PURE3D_LOADERS_SHADERLOADER_H

#include "code/container/map.h"
#include "code/content/chunkhandler.h"

namespace pure3d
{
	class ShaderLoader : public content::SimpleChunkHandler
	{
	public:
		// The destructor is declared first and not defined here, so that the vftable stays with the engine's own
		// copy of the unit.
		virtual ~ShaderLoader();

		// 0x10706960: the shader a shader chunk describes
		virtual void LoadObject(core::IRefCount** object, content::ObjectName* name, content::ChunkReader* reader,
			content::LoadInventory* inventory);

		// The nodes of the name table come from the global array new and delete
		struct InputNameAllocator
		{
			static void* Alloc(unsigned int size)
			{
				return operator new[](size);
			}
			static void Free(void* block)
			{
				operator delete[](block);
			}
		};

		// The names of the inputs by code (a map at +0x10)
		struct InputNames : public container::Map<unsigned int, const char*, InputNameAllocator>
		{
			// 0x107065F0: the name of a code (the entry is made when there is none)
			const char** At(const unsigned int* code);
		};

		// 0x107065C0: whether the code has a name (the type of the shader is not looked at)
		bool HasName(unsigned int code, const char* type);

		InputNames names;
	};
}

#endif
