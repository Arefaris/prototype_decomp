// pure3d::ParticleController (RTTI name; bases SimpleFrameController, AnimationFrameController, FrameController): the
// controller that advances a particle system state by the time of the frame. Member and slot names are guesses.
#ifndef PURE3D_EFFECTS_PARTICLECONTROLLER_H
#define PURE3D_EFFECTS_PARTICLECONTROLLER_H

#include "code/pure3d/primitive.h"

namespace pure3d
{
	class ParticleController : public SimpleFrameController
	{
	public:
		// Slot 3 (0x1074D280), 5 (0x1074D250): do nothing
		virtual void SetTarget(Entity* target);
		virtual void Unknown5();
		// Slots 8 / 9 (0x1074D3B0 / 0x1074D3C0): two of the controller's settings
		virtual float Unknown8();
		virtual float Unknown9();
		// Slot 24 (0x1074D270): false; slot 25 (0x1074D260): true
		virtual bool IsSupported(Animation* animation);
		virtual bool Unknown25();
		// 0x1074D3A0: the time the last step covered, in the units the update works in
		float GetUnknown1074D3A0();

		unsigned char unknown40[4];
		bool unknown44;
		float unknown48;
		float unknown4C;
		float unknown50;
	};
}

#endif
