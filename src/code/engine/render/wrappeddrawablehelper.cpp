// engine::render::EngineWrappedDrawableHelper: see the header.
#include "code/content/loadinventory.h"
#include "code/engine/render/drawablearchetype.h"
#include "code/engine/render/wrappeddrawablehelper.h"

namespace engine
{
	namespace render
	{
		// FUNCTION: ENGINE 0x108604D0
		core::IRefCount* EngineWrappedDrawableHelper::Wrap(core::IRefCount* drawable)
		{
			return new DrawableArchetype(drawable);
		}

		// FUNCTION: ENGINE 0x10861700
		pure3d::Drawable* EngineWrappedDrawableHelper::FindDrawable(content::LoadInventory* inventory, const content::ObjectName& name)
		{
			DrawableArchetype* archetype = inventory->Find<DrawableArchetype>(name);
			if (archetype != 0)
			{
				return archetype->drawable;
			}
			return 0;
		}
	}
}
