// engine::render::FrontEndPass (RTTI name, vftable 0x10E80764, base pure3d::Pass): the pass that draws the front end
// movies over the frame. The unit sits behind the Direct3D wrappers (0x108E1230 - 0x108E12E0; no assert path, file name
// guessed); the constructor is in another unit. Member names are guesses.
#ifndef ENGINE_RENDER_FRONTENDPASS_H
#define ENGINE_RENDER_FRONTENDPASS_H

#include "code/pure3d/pass.h"

namespace engine
{
	namespace render
	{
		class FrontEndPass : public pure3d::Pass
		{
		public:
			// 0x108E1230 (deleting destructor 0x108E12E0)
			virtual ~FrontEndPass();
			// vftable slot 4 (0x108E1250): draws the front end while the movies run, behind the two locks when it has them
			virtual void Render(pure3d::PassContext* context);

			// 0x108E12C0: the critical sections the drawing is held under
			void SetLocks(void* first, void* second);

			void* lock;  // +0xB0
			void* drawLock;  // +0xB4
		};
	}
}

#endif
