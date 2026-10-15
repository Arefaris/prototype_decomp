// code/engine/render/letterboxrenderpass.cpp (file name is a guess: the unit is the one between
// render/async/private/deferreddeletion.cpp and engine/online/onlinemanager.cpp, and the only name the block carries
// is the pass string "LetterboxRenderPass"): engine::render::LetterboxRenderPass and the classes of the letterbox
// the unit is built around, plus the two debug managers whose trivial constructors it is the first to emit.
#ifndef ENGINE_RENDER_LETTERBOXRENDERPASS_H
#define ENGINE_RENDER_LETTERBOXRENDERPASS_H

#include "code/debugoverlay/debugselectionmanager.h"
#include "code/engine/display.h"
#include "code/pure3d/pass.h"

namespace engine
{
	namespace render
	{
		// engine::render::Letterbox (name guess): the frame's bars. It holds the pool the rendering parameters of the
		// effect are interpolated out of, the two fade helpers that darken the bars and the pass that draws them, and
		// the byte at +0x16 switches the whole effect on.
		class Letterbox
		{
		public:
			// 0x108BC810
			void SetEnabled(bool enabled);
			// 0x108BCB30: the aspect ratio the bars are laid out from (the display's)
			float GetAspectRatio() const;

			unsigned char unknown0[0x16];
			bool mEnabled; // +0x16
		};

		// engine::render::LetterboxRenderPass (RTTI name, vftable 0x10E7DC14, 0xb0 bytes): the pass that draws the
		// letterbox bars over the frame. It adds no virtual slot to pure3d::Pass and is built by the factory
		// 0x108BD0D0 out of a pass the context already holds.
		class LetterboxRenderPass : public pure3d::Pass
		{
		public:
			LetterboxRenderPass(const pure3d::Pass& pass);
		};
	}
}

#endif
