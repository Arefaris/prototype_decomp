// proto::HUD (RTTI name; a pure3d primitive of a screen element of the heads-up display) and its per-element state
// proto::HUDState (the opacity, placement, colour and the mode of the element), and proto::LaserSight (a primitive that
// draws the laser of a weapon sight) with its state proto::LaserSightState (the two ends of the beam and its colour).
// Unit 0x102D7B00 - 0x102D91B0 (the drawing, slot 3 of both primitives, and HUDState::Update are not reconstructed; no
// assert path names the unit, the file name is a guess). Layouts are partial and the names are guesses.
#ifndef PROTO_RENDER_HUD_H
#define PROTO_RENDER_HUD_H

#include "code/math/vector.h"
#include "code/math/vector2.h"
#include "code/math/vector4.h"
#include "code/pure3d/primitive.h"

namespace proto
{
	class HUDState : public pure3d::PrimitiveState
	{
	public:
		// 0x102D7BB0
		HUDState(pure3d::Primitive* newPrimitive, const math::Vector2* newPosition, const math::Vector2* newSize,
			float newParameter, int newMode);
		// 0x102D7C50 (the deleting destructor is 0x102D8110)
		HUDState(const HUDState& other);
		// slot 3 (0x102D7CD0): new and copy
		virtual pure3d::PrimitiveState* Unknown3();
		// slot 4 (0x102D7D00): the fades and pulses of the element
		virtual void Update(float dt);
		// slot 5 (0x102D7FF0)
		virtual void Unknown5();
		// slot 6 (0x102D8000): whether the element is invisible
		virtual bool Unknown6();
		// slot 7 (0x102D8020)
		virtual void GetBoundingBox(math::AABB* box);
		// 0x102D8060: the mode; without one the second weight is the alpha of the colour
		void SetMode(int newMode);

		unsigned char unknown10[0xC];
		float opacity;  // +0x1C
		math::Vector2 position;  // +0x20
		math::Vector2 size;  // +0x28
		float parameter;  // +0x30
		float unknown34;
		unsigned int colour;  // +0x38
		int mode;  // +0x3C
		float time;  // +0x40
	};

	class HUD : public pure3d::Primitive
	{
	public:
		// 0x102D8520
		explicit HUD(pure3d::Shader* shader);
		// 0x102D8090 (the deleting destructor is 0x102D8140)
		virtual ~HUD();
		virtual void Draw(const core::Name<core::CaseInsensitiveKey32>* shader, pure3d::PrimitiveState* state,
			const math::Matrix* world, const pure3d::PrimStreamParameters* parameters, pure3d::PartBinding* binding);
		// slot 5 (0x102D80B0): everything
		virtual void GetBoundingBox(math::AABB* box);
		// slot 6 (0x102D84F0)
		virtual void GetCentre(math::Vector* centre);
		// slot 7 (0x102D80A0): nothing to batch
		virtual bool FillBatch(void* batch, pure3d::PrimitiveState* state, bool* unknown);
		// slot 8 (0x102D8100)
		virtual int Unknown8();

		static int sCount;  // 0x1125E030

		int id;  // +0x1C
	};

	class LaserSightState : public pure3d::PrimitiveState
	{
	public:
		// 0x102D85B0
		LaserSightState(pure3d::Primitive* newPrimitive, const math::Vector* newStart, const math::Vector* newEnd,
			float newParameter, const math::Vector4* newColour);
		// 0x102D8650 (the deleting destructor is 0x102D87F0)
		LaserSightState(const LaserSightState& other);
		// slot 3 (0x102D86D0): new and copy
		virtual pure3d::PrimitiveState* Unknown3();
		// slot 4 (0x102D8700)
		virtual void Update(float dt);
		// slot 5 (0x102D8710)
		virtual void Unknown5();
		// slot 6 (0x102D8720)
		virtual bool Unknown6();
		// slot 7 (0x102D8730): everything
		virtual void GetBoundingBox(math::AABB* box);

		unsigned char unknown10[0xC];
		math::Vector start;  // +0x1C
		math::Vector end;  // +0x28
		math::Vector4 colour;  // +0x34
		float parameter;  // +0x44
	};

	class LaserSight : public pure3d::Primitive
	{
	public:
		// 0x102D9020
		explicit LaserSight(pure3d::Shader* shader);
		// 0x102D8780 (the deleting destructor is 0x102D8820)
		virtual ~LaserSight();
		virtual void Draw(const core::Name<core::CaseInsensitiveKey32>* shader, pure3d::PrimitiveState* state,
			const math::Matrix* world, const pure3d::PrimStreamParameters* parameters, pure3d::PartBinding* binding);
		// slot 5 (0x102D87A0): everything
		virtual void GetBoundingBox(math::AABB* box);
		// slot 6 (0x102D8FF0)
		virtual void GetCentre(math::Vector* centre);
		// slot 7 (0x102D8790): nothing to batch
		virtual bool FillBatch(void* batch, pure3d::PrimitiveState* state, bool* unknown);
	};
}

#endif
