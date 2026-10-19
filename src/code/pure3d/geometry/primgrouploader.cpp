// pure3d::PrimGroupLoader: the description of a mesh's primitive groups (see primgrouploader.h). The file name and
// the directory are guesses (no assert path survives in the binary).
#include "code/pure3d/geometry/primgrouploader.h"
#include "code/pure3d/loaders/drawableloaders.h"

namespace pure3d
{
	// The shader of that name in the inventory, none when there is none (name guess)
	inline Shader* FindShader(content::LoadInventory* inventory, const char* name)
	{
		content::LoadInventory::DynamicCaster<Shader> caster;
		return (Shader*)inventory->FindObject(&caster, content::ObjectName(name, 1), true);
	}

	// FUNCTION: ENGINE 0x10B8F1C0
	bool PrimGroupLoader::ReadGroup(content::ChunkReader* reader, content::LoadInventory* inventory)
	{
		if (reader->GetChunkId() != 0x10020)
		{
			return false;
		}
		ReadWord(reader);
		char shaderName[0x100];
		{
			unsigned char byte;
			reader->Read(&byte, 1, 1, 1);
			unsigned int length = byte;
			reader->Read(shaderName, length, 1, 1);
			shaderName[length] = 0;
		}
		core::SafeRelease(shader);
		shader = FindShader(inventory, shaderName);
		// A group whose shader is missing draws with the error shader
		Shader* found = shader;
		if (found == 0)
		{
			found = new Shader("error");
			shader = found;
		}
		found->AddRef();
		unknownC = ReadWord(reader);
		unknown1C = unknown18 & ReadWord(reader);
		unknown20 = ReadWord(reader);
		unknown24 = ReadWord(reader);
		unknown28 = ReadWord(reader);
		unknown10 = ReadWord(reader) != 0;
		unknown11 = ReadWord(reader) != 0;
		unknown12 = ReadWord(reader) != 0;
		unknown14 = ReadWord(reader);
		unknown1C |= 0x2000;
		return true;
	}

	// FUNCTION: ENGINE 0x10B90A70
	void PrimGroupLoader::MakePrimitive(void* object, content::ChunkReader* reader, content::LoadInventory* inventory,
		bool skin, bool gpu)
	{
		if (ReadGroup(reader, inventory))
		{
			if (skin)
			{
				if (gpu)
				{
					BuildGpuSkin(object, reader, inventory);
					core::SafeRelease(shader);
					return;
				}
				BuildSkin(object, reader, inventory);
				core::SafeRelease(shader);
				return;
			}
			BuildMesh(object, reader, inventory);
			core::SafeRelease(shader);
		}
	}
}

namespace pure3d
{
	// FUNCTION: ENGINE 0x10B8BD30
	PrimGroupLoader::PrimGroupLoader()
	{
		shader = 0;
		unknownC = 0;
		unknown10 = false;
		unknown11 = true;
		unknown12 = false;
		unknown14 = 0;
		unknown18 = -1;
		unknown1C = -1;
		unknown20 = 0;
		unknown24 = 0;
		unknown28 = 0;
	}
}
