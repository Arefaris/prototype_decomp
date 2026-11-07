// code/engine/render/letterboxrenderpass.cpp (file name is a guess, see the header): the letterbox the renderer draws
// the frame's bars with, together with the two debug managers whose trivial constructors this unit is the first to
// need.
#include "code/engine/render/letterboxrenderpass.h"
#include "code/engine/render/async/canvas.h"
#include "code/pure3d/context.h"

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

		// FUNCTION: ENGINE 0x108BCA00
		void Canvas::Unknown108BCA00(bool value)
		{
		}

		// FUNCTION: ENGINE 0x108BCE10
		void Canvas::SetCurrentContext(core::Name<core::CaseSensitiveKey> name)
		{
			pure3d::context->SetCurrentContext(name.GetHash());
		}

		// FUNCTION: ENGINE 0x108BCE40
		void Canvas::Unknown108BCE40(core::Name<core::CaseSensitiveKey> name, bool value)
		{
			if (parameters != 0)
			{
				parameters->SetBool(&name, value);
			}
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

// Kept copies (template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108BC8C0
