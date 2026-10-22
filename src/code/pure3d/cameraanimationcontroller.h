// pure3d::CameraAnimationController (RTTI name; bases pure3d::BlendFrameController / AnimationFrameController /
// FrameController / Entity / RefCounted / core::IRefCount; 0x120 bytes, constructor 0x107B43C0, 31 vftable slots):
// plays a camera animation. Only the slots the cameras call are declared (as ordinary virtual members in vftable
// order); the rest of the class is in other units. Method names are guesses.
#ifndef PURE3D_CAMERAANIMATIONCONTROLLER_H
#define PURE3D_CAMERAANIMATIONCONTROLLER_H

#include "code/pure3d/entity.h"

namespace pure3d
{
	class Animation;
	class Camera;

	class CameraAnimationController : public Entity
	{
	public:
		// 0x107B43C0
		CameraAnimationController();

		virtual void Slot3();
		// vftable slot 4 (0x107775C0): advances by a time in milliseconds
		virtual void Advance(float time, bool flag);
		virtual void Slot5();
		// vftable slot 6 (0x10777050)
		virtual void SetFrame(float frame);
		virtual void Slot7();
		virtual void Slot8();
		virtual void Slot9();
		// vftable slots 10 - 12 (0x107777B0, 0x10777830, 0x10777860)
		virtual void SetStartFrame(float frame);
		virtual float GetFrame();
		virtual void SetFrameRange(float first, float last);
		virtual void Slot13();
		// vftable slot 14 (0x10777940)
		virtual void SetCycleMode(int mode);
		virtual void Slot15();
		// vftable slot 16 (0x107779D0)
		virtual void SetLoop(int loop);
		virtual void Slot17();
		virtual void Slot18();
		virtual void Slot19();
		// vftable slot 20 (0x10777A90): the animation has finished
		virtual bool IsDone();
		virtual void Slot21();
		// vftable slot 22 (0x107780E0)
		virtual void SetAnimation(Animation* animation, float first, float last);

		// 0x107B5170: the camera the animation drives
		void SetCamera(Camera* camera);
		// 0x107B4330: whether the animation has played to its end between the previous and the current frame (name
		// and parameters guessed)
		bool IsFinished(float previousFrame, float frame);

		unsigned char unknown10[0x110];
	};
}

#endif
