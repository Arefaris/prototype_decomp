// proto::BloodSplatter (RTTI name; a pure3d primitive of the blood that spatters on the screen) and its per-splash state
// proto::BloodSplatterState (the placement, the fade-in, hold and fade-out times and the time left). Unit 0x102CBF50 -
// 0x102CCBB0 (the drawing, slot 3 at 0x102CC3C0, is not reconstructed; no assert path names the unit, the file name is a
// guess). Layouts are partial and the names are guesses.
#ifndef PROTO_RENDER_BLOODSPLATTER_H
#define PROTO_RENDER_BLOODSPLATTER_H

#include "code/math/vector2.h"
#include "code/pure3d/primitive.h"

namespace proto
{
	class BloodSplatterState : public pure3d::PrimitiveState
	{
	public:
		// 0x102CBF50: a splash at a place with its size, at an angle, that fades in, holds and fades out
		BloodSplatterState(pure3d::Primitive* newPrimitive, const math::Vector2* newPosition,
			const math::Vector2* newSize, float newAngle, float newFadeIn, float newHold, float newFadeOut);
		// 0x102CC000
		BloodSplatterState(const BloodSplatterState& other);
		// the deleting destructor is 0x102CC320
		// 0x102CC070 (new and copy)
		virtual pure3d::PrimitiveState* Unknown3();
		// 0x102CC350: the time left runs down in thousandths
		virtual void Update(float dt);
		// slot 7 (0x102CC0D0): an empty box around the origin, inflated
		virtual void GetBoundingBox(math::AABB* box);
		// 0x102CC160: how much of the splash is left, in [0, 1]
		float GetRemainingShare();

		unsigned char unknown10[0xC];
		math::Vector2 position;  // +0x1C
		math::Vector2 size;  // +0x24
		float angle;  // +0x2C
		float hold;  // +0x30
		float fadeOut;  // +0x34
		float remaining;  // +0x38
		float fadeIn;  // +0x3C
	};

	class BloodSplatter : public pure3d::Primitive
	{
	public:
		// 0x102CC940
		explicit BloodSplatter(pure3d::Shader* shader);
		// 0x102CC1D0 (the deleting destructor is 0x102CC390)
		virtual ~BloodSplatter();
		virtual void Draw(const core::Name<core::CaseInsensitiveKey32>* shader, pure3d::PrimitiveState* state,
			const math::Matrix* world, const pure3d::PrimStreamParameters* parameters, pure3d::PartBinding* binding);
		// slot 5 (0x102CC210): everything
		virtual void GetBoundingBox(math::AABB* box);
		// slot 6 (0x102CC8D0)
		virtual void GetCentre(math::Vector* centre);
		// slot 7 (0x102CC200): nothing to batch
		virtual bool FillBatch(void* batch, pure3d::PrimitiveState* state, bool* unknown);
		// slots 8 - 10 (0x102CC290, 0x102CC1E0, 0x102CC1F0)
		virtual int Unknown8();
		virtual int GetUnknown9();
		virtual void SetUnknown10(int value);

		static int sCount;  // 0x1125DCD4

		int id;  // +0x1C
	};
}

#endif
