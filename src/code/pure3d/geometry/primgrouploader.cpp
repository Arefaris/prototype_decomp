// pure3d::PrimGroupLoader: the description of a mesh's primitive groups (see primgrouploader.h). The file name and
// the directory are guesses (no assert path survives in the binary).
#include "code/pure3d/geometry/primgrouploader.h"

namespace pure3d
{
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
