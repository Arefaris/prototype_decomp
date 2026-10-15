// code/engine/render/letterboxrenderpass.cpp (file name is a guess, see the header): the letterbox the renderer draws
// the frame's bars with, together with the two debug managers whose trivial constructors this unit is the first to
// need.
#include "code/engine/render/letterboxrenderpass.h"

namespace engine
{
	namespace render
	{
		// FUNCTION: ENGINE 0x108BC810
		void Letterbox::SetEnabled(bool enabled)
		{
			mEnabled = enabled;
		}

		// FUNCTION: ENGINE 0x108BCB30
		float Letterbox::GetAspectRatio() const
		{
			return gDisplay->GetAspectRatio();
		}
	}
}

namespace debugoverlay
{
	// FUNCTION: ENGINE 0x108BCDE0
	DebugSelectionManager::DebugSelectionManager()
	{
	}
}
