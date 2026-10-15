// code/engine/motiontrail.cpp (file name is a guess): engine::MotionTrail, the primitive a moving object leaves a
// trail behind, the engine::MotionTrailCreator that makes one out of a drawable, and the engine::MotionTrailState its
// primitive state holds. Only the pieces reconstructed so far are declared here.
#ifndef ENGINE_MOTIONTRAIL_H
#define ENGINE_MOTIONTRAIL_H

#include "code/engine/render/async/private/drawableimpl.h"

namespace engine
{
	// engine::MotionTrail (RTTI name, vftable 0x10E7DD74, eleven slots, a pure3d::Primitive): the strip a moving
	// object leaves behind. Only the four floats the state copies in and out of (+0x34) are placed here; the
	// primitive's own layout and the rest of the class belong to the unit's other functions.
	class MotionTrail
	{
	public:
		// 0x108BD8A0: the six floats at +0x1c (two three-float vectors), copied out to a caller's buffer
		void GetUnknown1C(float* values) const;
		// 0x108BD920 / 0x108BD940: the four floats at +0x34, copied to and from a caller's buffer
		void GetUnknown34(float* values) const;
		void SetUnknown34(const float* values);

		unsigned char unknown0[0x1C];
		float unknown1C[6]; // +0x1C
		float unknown34[4]; // +0x34
	};

	// engine::MotionTrailCreator (RTTI name, vftable 0x10E7DDA4, one slot): what engine::MotionTrail::Create is
	// called with. The member at +4 is not read by anything reconstructed yet.
	class MotionTrailCreator : public render::DrawableCreator
	{
	public:
		MotionTrailCreator();

		int unknown4; // +0x04
	};
}

#endif
