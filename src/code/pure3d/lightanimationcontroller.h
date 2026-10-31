// pure3d::LightAnimationController (RTTI name; bases BlendFrameController, AnimationFrameController, FrameController,
// Entity, RefCounted, core::IRefCount; 0x118 bytes, 31 vftable slots): plays a light animation (colour, position,
// direction, attenuation, cone and enable channels) on a light. Names are guesses.
#ifndef PURE3D_LIGHTANIMATIONCONTROLLER_H
#define PURE3D_LIGHTANIMATIONCONTROLLER_H

#include "code/pure3d/framecontroller.h"
#include "code/pure3d/light.h"

namespace pure3d
{
	class LightAnimationController : public BlendFrameController
	{
	public:
		// 0x107B2ED0 / 0x107B39A0 (the copy takes the same light)
		LightAnimationController();
		LightAnimationController(const LightAnimationController& other);
		// Slot 2 (the body is 0x107B2F60, the deleting destructor 0x107B3980)
		virtual ~LightAnimationController();

		// Slot 3 (0x107B3A10): the light is the target when it is one
		virtual void SetTarget(Entity* target);
		// Slot 24 (0x107B2F00): a light animation
		virtual bool IsSupported(Animation* animation);
		// Slots 26 and 27 (0x107B2FD0, 0x107B3320): lay the values of the animation (of the first entry, of all of them
		// by their weights) over the light
		virtual void Unknown26();
		virtual void Unknown27();
		// Slot 29 (0x107B2EF0): true
		virtual bool Unknown29();
		// Slot 30 (0x107B39E0)
		virtual LightAnimationController* Clone();

		// 0x107B2F30 / 0x107B2F80: the light the controller drives; the controller takes a reference to it and keeps
		// its type
		Light* GetLight();
		void SetLight(Light* newLight);

		unsigned char unknown10C[4];
		int lightType;   // +0x110
		Light* light;    // +0x114
	};
}

#endif
