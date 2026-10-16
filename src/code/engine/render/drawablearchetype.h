// engine::render::DrawableArchetype (RTTI name; bases content::LoadObject, core::IRefCount): the description of a
// drawable that the content files hold and that Drawable::CreateInstance makes instances of. Only the two accessors the
// midground manager needs; the layout (a pointer to the data at +8) and the names are guesses.
#ifndef ENGINE_RENDER_DRAWABLEARCHETYPE_H
#define ENGINE_RENDER_DRAWABLEARCHETYPE_H

#include "code/content/loadinventory.h"
#include "code/core/name.h"

namespace engine
{
	namespace render
	{
		class DrawableArchetype : public content::LoadObject
		{
		public:
			// 0x108258C0: a flag of the data (bit 3 of its byte at +0x100)
			bool IsFlagged() const;
			// 0x108258B0: the name at +8 of the data
			const core::Name<core::CaseSensitiveKey>* GetName() const;
		};
	}
}

#endif
