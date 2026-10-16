// proto::MidgroundTextureManager: see the header. The file name, the layout and the names are guesses.
#include "code/proto/render/midgroundtexturemanager.h"

namespace proto
{
	// FUNCTION: ENGINE 0x105676F0
	MidgroundTextureManager::~MidgroundTextureManager()
	{
		ReleaseScript();
		gMidgroundTextureManager = 0;
	}
}

// FUNCTION: ENGINE 0x10567920
// The compiler's scalar deleting destructor of proto::MidgroundTextureManager, emitted with the class above: it calls
// the destructor and then operator delete when bit 0 of its argument is set.
//
// ReleaseScript (0x10567670, the same unit: GetScriptManager()->Unregister(this)) is only declared; the engine's copy
// owns the object in esi across the GetScriptManager call, ours spills the object instead (57 %).
