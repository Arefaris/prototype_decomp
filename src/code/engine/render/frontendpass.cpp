// The front end render pass (unit 0x108E1230 - 0x108E12E0; no assert path, file name guessed).
#include "code/engine/render/frontendpass.h"
#include "code/core/criticalsection.h"

namespace engine
{
	// Whether the front end is drawn at all (0x111E0F48; name guessed)
	extern bool gFrontEndDrawEnabled;

	// 0x10885E50 (the Scaleform unit): draws the movies of the front end
	void RenderFrontEnd(int mode);

	namespace render
	{
		// FUNCTION: ENGINE 0x108E1230
		FrontEndPass::~FrontEndPass()
		{
		}

		// FUNCTION: ENGINE 0x108E1250
		void FrontEndPass::Render(pure3d::PassContext* context)
		{
			if (gFrontEndDrawEnabled)
			{
				if (lock != 0)
				{
					core::CriticalSectionLeave(drawLock);
					core::CriticalSectionEnter(lock);
					core::CriticalSectionEnter(drawLock);
					RenderFrontEnd(0);
					core::CriticalSectionLeave(lock);
					return;
				}
				RenderFrontEnd(0);
			}
		}

		// FUNCTION: ENGINE 0x108E12C0
		void FrontEndPass::SetLocks(void* first, void* second)
		{
			lock = first;
			drawLock = second;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108E12E0
