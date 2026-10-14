// What drawable.cpp needs of the render thread's side: the drawable table's slots (renderglobals.cpp) and the render
// object of a drawable, a pure3d::Drawable (code/pure3d/drawable.h). Only what the async units call is declared;
// all of these are in other units.
#ifndef ENGINE_RENDER_ASYNC_PRIVATE_DRAWABLEIMPL_H
#define ENGINE_RENDER_ASYNC_PRIVATE_DRAWABLEIMPL_H

#include "code/container/arraydynamic.h"
#include "code/core/name.h"
#include "code/engine/render/async/drawable.h"
#include "code/math/matrix.h"
#include "code/math/pddicolour.h"
#include "code/math/vector4.h"
#include "code/pure3d/drawable.h"
#include "code/pure3d/scene.h"

namespace engine
{
	namespace render
	{
		// The render object of a drawable is a pure3d::Drawable; drawable.cpp knows it and its parts by these names
		typedef pure3d::Drawable DrawableImpl;
		typedef pure3d::DrawablePart DrawablePart;
		typedef pure3d::PartRef PartRef;
		typedef pure3d::PartBinding PartBinding;
		typedef pure3d::PartBindingSource PartBindingSource;
		typedef pure3d::BindingParameters BindingParameters;
		typedef pure3d::PartAnimationFlags PartAnimationFlags;
		typedef pure3d::PartAnimationState PartAnimationState;

		// The object a drawable was instanced from (its unit is around 0x10825xxx; called a source drawable by
		// renderglobals.cpp's assert "0 == drawableData->sourceDrawable")
		class SourceDrawable
		{
		public:
			// 0x108258E0: vftable slot 0x17 of the drawable's +0x78 object
			void* GetParameters();

			int unknown0;
			int unknown4;
			DrawableImpl* drawable;
			unsigned char unknownC[0x18];
			unsigned char flags24;
		};

		// A slot of the drawable table (16 bytes)
		struct DrawableData
		{
			DrawableImpl* drawable;
			pure3d::FrameController* unknown4;
			bool unknown8;
			// In the render list
			bool registered;
			// Put in the render list when created
			bool registerOnCreate;
			bool created;
			SourceDrawable* sourceDrawable;
		};

		// The list the render thread draws (0x1130CCC0; 0x10817B10 returns it) is the pure3d scene
		typedef pure3d::Scene RenderList;

		// 0x1128186A: passed to the texture uploader (another unit)
		extern bool gTextureLoadFlag;

		// renderglobals.cpp
		// 0x10818920: the slot of a handle, null when the handle is stale
		DrawableData* GetDrawableData(const Drawable& drawable);
		// 0x10818260
		bool IsValidDrawable(const Drawable& drawable);
		// 0x10817B10
		RenderList* GetRenderList();
		// 0x10817B40: deletes the entity once the render thread is done with it
		void DeferDelete(pure3d::Entity* entity);
		// 0x10818790 / 0x10818850
		Drawable AllocateDrawable(SourceDrawable* source, bool registerOnCreate);
		void FreeDrawable(Drawable drawable, DestroyMode mode);


		// What makes the render object of a drawable (RTTI name engine::render::DrawableCreator, one virtual)
		class DrawableCreator
		{
		public:
			virtual DrawableImpl* Create() = 0;
		};

		// Changes a render object (RTTI name engine::render::DrawableModifier, one virtual; called with null
		// for a drawable that no longer exists)
		class DrawableModifier
		{
		public:
			virtual void Apply(DrawableImpl* drawable) = 0;
		};

		// The particle overrides: 16 parameters of the particle system state and 8 of its generator
		struct EffectOverrides
		{
			float values[24];
		};

		// 34 floats; the copy constructor is an inline member the original left out of line (0x107E85E0)
		struct EffectBiases
		{
			EffectBiases(const EffectBiases& other)
			{
				values[0] = other.values[0];
				values[1] = other.values[1];
				values[2] = other.values[2];
				values[3] = other.values[3];
				values[4] = other.values[4];
				values[5] = other.values[5];
				values[6] = other.values[6];
				values[7] = other.values[7];
				values[8] = other.values[8];
				values[9] = other.values[9];
				values[10] = other.values[10];
				values[11] = other.values[11];
				values[12] = other.values[12];
				values[13] = other.values[13];
				values[14] = other.values[14];
				values[15] = other.values[15];
				values[16] = other.values[16];
				values[17] = other.values[17];
				values[18] = other.values[18];
				values[19] = other.values[19];
				values[20] = other.values[20];
				values[21] = other.values[21];
				values[22] = other.values[22];
				values[23] = other.values[23];
				values[24] = other.values[24];
				values[25] = other.values[25];
				values[26] = other.values[26];
				values[27] = other.values[27];
				values[28] = other.values[28];
				values[29] = other.values[29];
				values[30] = other.values[30];
				values[31] = other.values[31];
				values[32] = other.values[32];
				values[33] = other.values[33];
			}

			float values[34];
		};
	}
}

#endif
