// engine::render::EngineWrappedDrawableHelper (RTTI name; base pure3d::WrappedDrawableHelper): the hook the engine
// installs on the pure3d context so that the drawables the loaders make are handed out as drawable archetypes. Unit
// 0x108604C0 - 0x10860520 (no assert path; the file name is a guess).
#ifndef ENGINE_RENDER_WRAPPEDDRAWABLEHELPER_H
#define ENGINE_RENDER_WRAPPEDDRAWABLEHELPER_H

#include "code/pure3d/context.h"

namespace engine
{
	namespace render
	{
		class EngineWrappedDrawableHelper : public pure3d::WrappedDrawableHelper
		{
		public:
			// vftable slot 0 (0x108604D0): the archetype that wraps the drawable
			virtual core::IRefCount* Wrap(core::IRefCount* drawable);
			// vftable slot 1 (0x10861700): the drawable of the archetype of that name
			virtual pure3d::Drawable* FindDrawable(content::LoadInventory* inventory, const content::ObjectName& name);
		};
	}
}

#endif
