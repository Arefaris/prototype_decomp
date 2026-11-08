// proto::NPCInstance (RTTI name, one vftable slot): the instance of a pedestrian the render behaviour shows: the drawable
// made from the type it is of, the level of detail and the visibility. It is embedded in proto::NPCRenderBehaviour.
// Unit 0x10479270 - 0x1047A130 (no assert path; the file name is a guess). Member names are guesses; the construction,
// the destruction and the small accessors are reconstructed, the creation of the drawable is left to the engine.
#ifndef PROTO_NPCINSTANCE_H
#define PROTO_NPCINSTANCE_H

#include "code/engine/render/async/drawable.h"
#include "code/math/matrix.h"
#include "code/proto/npctype.h"

namespace engine
{
	class GameObject;
}

namespace proto
{
	class NPCInstance
	{
	public:
		// 0x10479270
		NPCInstance();
		// 0x10479550 (the deleting destructor is 0x104798C0)
		virtual ~NPCInstance();

		// 0x104792C0: shows or hides the drawable
		void SetRegistered(bool registered);
		// 0x104792F0: the level of detail
		int GetLod() const;
		// 0x10479300
		int GetUnknown10() const;
		// 0x10479310
		NPCType* GetType() const;
		// 0x10479320: gives the drawable up
		void DestroyDrawable();
		// 0x10479360 / 0x10479370 / 0x10479380
		void SetObject(engine::GameObject* newObject);
		void SetLod(int newLod);
		void SetUnknown10(char newValue);
		// 0x10479400: the shader palette of the render type
		ShaderPalette* GetShaderPalette() const;
		// 0x10479420: the animation the instance shows
		NPCAnimation* GetAnimation() const;
		// 0x104793A0: gives the drawable the pose of that animation
		void SetPoseFromAnimation();
		// 0x10479390: what the instance is drawn as (the type or one of its drawables)
		NPCRender* GetRender() const;
		// 0x10479620: makes the drawable of the type and shows it (left to the engine; name guess)
		void Create(bool show);
		// 0x104795C0: takes the render type and picks one of the entries of its shader palette; left to the engine
		void SetRender(NPCRender* newRender);
		// 0x10479460 / 0x104794A0
		void SetScale(float newScale);
		void SetTransform(const math::Matrix& transform);

		engine::render::Drawable drawable;  // +4
		engine::GameObject* object;  // +8
		int lod;  // +0xC
		char unknown10;
		bool unknown11;
		bool registered;  // +0x12
		float scale;  // +0x14
		NPCType* type;  // +0x18
		NPCRender* render;  // +0x1C
		int paletteIndex;  // +0x20
	};
}

#endif
