// pure3d::PrimGroupLoader: the description of a mesh's primitive groups (see primgrouploader.h). The file name and
// the directory are guesses (no assert path survives in the binary).
#include "code/pure3d/geometry/primgrouploader.h"

#ifdef NONMATCHING
namespace pure3d
{
	// FUNCTION: ENGINE 0x10B8BD30
	// NONMATCHING: the engine's copy keeps the vftable store of the base constructor it inlines (RefCounted's
	// 0x10DA05B0 before the class's own 0x10EAF644). Our compiler removes that store from every derived constructor
	// (checked against the same shape in this unit); the rest of the body is identical, 27.5 %.
	PrimGroupLoader::PrimGroupLoader()
	{
		groups = 0;
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
#endif
