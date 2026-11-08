// engine::render::DrawableArchetype (RTTI name, vftable 0x10E6E394; bases content::LoadObject, core::IRefCount): the
// description of a drawable that the content files hold and that Drawable::CreateInstance makes instances of. It wraps
// the drawable the loader made (at +8) and keeps what its instances need to know: the box around it, in the drawable's
// own space, whether it cycles, whether it has a frame controller and how long that plays. Unit 0x10825890 -
// 0x10825AD0 (no assert path; the file name is a guess); the names other than the class's are guesses.
#ifndef ENGINE_RENDER_DRAWABLEARCHETYPE_H
#define ENGINE_RENDER_DRAWABLEARCHETYPE_H

#include "code/content/loadinventory.h"
#include "code/core/name.h"
#include "code/math/aabb.h"

namespace pure3d
{
	class Drawable;
	struct DrawableSegment;
	class Pose;
}

namespace engine
{
	namespace render
	{
		class DrawableArchetype : public content::LoadObject
		{
		public:
			// 0x108259B0 (not reconstructed): wraps the drawable a loader made
			explicit DrawableArchetype(core::IRefCount* newDrawable);
			// 0x108258C0: a flag of the data (bit 3 of its byte at +0x100)
			bool IsFlagged() const;
			// 0x108258B0: the name at +8 of the data
			const core::Name<core::CaseSensitiveKey>* GetName() const;
			// 0x108258E0: vftable slot 0x17 of the drawable's +0x78 object (not reconstructed)
			void* GetParameters();
			// 0x10825930
			const math::AABB* GetBounds() const;
			// 0x10825960: a pose of the drawable, made from its pose or its skeleton (null when it has neither)
			pure3d::Pose* CreatePoseInstance();
			// 0x108258D0 / 0x10825910 / 0x10825920
			bool HasFrameController() const;
			bool IsCyclic() const;
			float GetLength() const;
			// 0x10825940 / 0x10825950 / 0x10825AD0
			pure3d::DrawableSegment* GetSegment(unsigned short segment);
			void GetSegmentParts(unsigned short segment, unsigned int* first, unsigned int* count);
			int GetSegmentCount();

			pure3d::Drawable* drawable;  // +8
			math::AABB bounds;           // +0xC
			// +0x24: the flags (bit 2 is cleared when the drawable is freed, bit 3 set when an instance shares the source)
			union
			{
				unsigned char flags24;
				struct
				{
					unsigned char cyclic : 1;
					unsigned char hasFrameController : 1;
					unsigned char unknown24Bit2 : 1;
					unsigned char unknown24Bit3 : 1;
					unsigned char unknown24Bits : 4;
				};
			};
			float length;                // +0x28
		};
	}
}

#endif
